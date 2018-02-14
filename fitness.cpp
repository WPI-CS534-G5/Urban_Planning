
#include "fitness.h"

int costBuild(struct Params GA_Params,int i){
  int score=0;
  if(GA_Params.InitialMap[i]<10){
    score -= GA_Params.InitialMap[i];
  }
  return score;
}

int fitBuild(struct Params GA_Params, struct individual Individual, int i,int building, int distance, int points){
  int score=0;
  int possition = 0;
  for(int j=0;j< GA_Params.iNroIndustrialPlaces; j++){
    possition += Individual.gene[j];
    if(possition> GA_Params.iNroRowsField*GA_Params.iNroColField){
      possition -= GA_Params.iNroRowsField*GA_Params.iNroColField;
    }
    if((i!=possition)&&(GA_Params.vTypes[j]==building)&&(manhatanDistance(i,possition,GA_Params)<distance+1)){
      score += points;
    }
  }

  for(int j= GA_Params.iNroIndustrialPlaces;j< GA_Params.iNroComercialPlaces + GA_Params.iNroIndustrialPlaces; j++){
    possition += Individual.gene[j];
    if(possition> GA_Params.iNroRowsField*GA_Params.iNroColField){
      possition -= GA_Params.iNroRowsField*GA_Params.iNroColField;
    }
    if((i!=possition)&&(GA_Params.vTypes[j]==building)&&(manhatanDistance(i,possition,GA_Params)<distance+1)){
      score += points;
    }
  }

  for(int j=GA_Params.iNroComercialPlaces+GA_Params.iNroIndustrialPlaces;j< GA_Params.iNroResidencialPlaces+ GA_Params.iNroComercialPlaces+GA_Params.iNroIndustrialPlaces; j++){
    possition += Individual.gene[j];
    if(possition> GA_Params.iNroRowsField*GA_Params.iNroColField){
      possition -= GA_Params.iNroRowsField*GA_Params.iNroColField;
    }
    if((i!=possition)&&(GA_Params.vTypes[j]==building)&&(manhatanDistance(i,possition,GA_Params)<distance+1)){
      score += points;
    }
  }


  return score;
}

int fitMap(struct Params GA_Params, struct individual Individual, int i,int building, int distance, int points){
  int score= 0;

  for(int j=0;j< (int)GA_Params.Map.size();j++){
    if((i!=j)&&(GA_Params.Map[j]==building)&&(manhatanDistance(i,j,GA_Params)<distance+1)){
      score += points;
    }
  }
  return score;
}

//Get the Manhatan Distance
int manhatanDistance(int pos1,int pos2,struct Params GA_Params){
  return abs(((int)pos1/GA_Params.iNroColField)-((int)pos2/GA_Params.iNroColField))+abs((pos1%GA_Params.iNroColField)-(pos2%GA_Params.iNroColField));
}

int fitnessFnc(struct Params GA_Params, struct individual Individual) {

  int fitness =0;
  int possition= 0;

  // Industrial buildings
  for(int i=0;i< GA_Params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> GA_Params.iNroRowsField*GA_Params.iNroColField){
      possition -= GA_Params.iNroRowsField*GA_Params.iNroColField;
    }

    //Dificulty of building
    fitness += costBuild(GA_Params,possition);
    // Industrial tiles benefit from being near other industry.
    //For each industrial tile within 2, there is a bonus of 3 points.
    fitness += fitBuild(GA_Params,Individual,possition,10,2,3);
    // Former toxic waste site: Industrial zones within 2 tiles take a penalty of -10.
    fitness += fitMap(GA_Params,Individual,possition,13,2,-10);
  }
  // Commercial buildings
  for(int i= GA_Params.iNroIndustrialPlaces;i< GA_Params.iNroComercialPlaces + GA_Params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> GA_Params.iNroRowsField*GA_Params.iNroColField){
      possition -= GA_Params.iNroRowsField*GA_Params.iNroColField;
    }

    //Dificulty of building
    fitness += costBuild(GA_Params,possition);
    // Commercial sites benefit from being near residential tiles.
    // For each residential tile within 3 squares, there is a bonus of 5 points.
    fitness += fitBuild(GA_Params,Individual,possition,12,3,5);
    // However, commercial sites do not like competition.
    //For each commercial site with 2 squares, there is a penalty of 5 points.
    fitness += fitBuild(GA_Params,Individual,possition,11,2,-5);
    // Former toxic waste site: Commercial and residential zones within 2 tiles take a penalty of -20.
    fitness += fitMap(GA_Params,Individual,possition,13,2,-20);
  }
  // Residential buildings
  for(int i=GA_Params.iNroComercialPlaces+GA_Params.iNroIndustrialPlaces;i< GA_Params.iNroResidencialPlaces+ GA_Params.iNroComercialPlaces+GA_Params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> GA_Params.iNroRowsField*GA_Params.iNroColField){
      possition -= GA_Params.iNroRowsField*GA_Params.iNroColField;
    }

    //Dificulty of building
    fitness += costBuild(GA_Params,possition);
    // Residential sites do not like being near industrial sites.
    // For each industrial site within 3 squares there is a penalty of 5 points.
    fitness += fitBuild(GA_Params,Individual,possition,10,3,-5);
    // However, for each commercial site with 3 squares there is a bonus of 5 points.
    fitness += fitBuild(GA_Params,Individual,possition,11,3,5);
    // Former toxic waste site: Commercial and residential zones within 2 tiles take a penalty of -20.
    fitness += fitMap(GA_Params,Individual,possition,13,2,-20);
    // Scenic view.  Residential zones within 2 tiles gain a bonus of 10 points.
    fitness += fitMap(GA_Params,Individual,possition,14,2,10);
  }

  return fitness;
}

// Calculates the fitness of all population
int evalFitnessPopulation(struct Params GA_Params, vector<struct individual> &vPopulation){
    if(vPopulation.size()==0)
        return FAILURE;
    for(int i=0;i<(int)vPopulation.size();i++)
    {
        vPopulation[i].fitness=fitnessFnc(GA_Params, vPopulation[i]);
        //cout<<vPopulation[i].fitness<<endl;
    }
    return SUCCESS;
}


int isAnIndividualValid(struct Params GA_Params, struct individual nIndividual){
    vector<int> Pos;
    int iValue=0;
    int iSum=0;
    for(int i=0;i<(int)nIndividual.gene.size();i++) {
        iSum = iSum + nIndividual.gene[i];
        iValue = iSum % GA_Params.iSizeOfField;
        //cout<<iSum<<" "<<iValue<<endl;

        if(GA_Params.Map[iValue]==TOXIC_SITE)  //Check if a building is not over a toxic zone
            return FAILURE;

        if (Pos.size() != 0) {     //Check if a building is not over another building
            for (int j = 0; j < (int)Pos.size(); j++) {
                //cout<<GA_Params.Map[iValue]<<" "<<endl;
                if (Pos[j] == iValue) {
                    //cout << "Invalid individual: [" << nIndividual.gene[0] << " " << nIndividual.gene[1] << " "
                    //     << nIndividual.gene[2] << "]" << endl;
                    return FAILURE;
                }
            }
        }
        Pos.push_back(iValue);
    }
    return SUCCESS;
}

//Generic
long getRandom(long maxNumber){
    long long int seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    int iNumber=generator()%maxNumber;
    return iNumber;
}
