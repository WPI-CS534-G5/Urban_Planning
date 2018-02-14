
#include <random>
#include <chrono>
#include <algorithm>
#include "genetic.h"
#include "iofunctions.h"
#include <cmath>


// Generates the total number of individuals with random genes
int initPopulation(struct Params GA_Params,vector<struct individual> &vPopulation){
    struct individual newIndividual;
    int iValue=0;

    for(int i=0;i<GA_Params.iSizeOfPopulation;i++)
    {
        for(int j=0;j<GA_Params.iSizeOfGene;j++)
        {
            iValue=getRandom(GA_Params.iSizeOfField);
            newIndividual.gene.push_back(iValue);
        }

        //Check for an invalid individual!
        if(isAnIndividualValid(GA_Params,newIndividual)) {
            newIndividual.fitness = 0;
            vPopulation.push_back(newIndividual);
        }
        else{
            i--;
            //cout<<"Invalid individue detected"<<endl;
        }

        newIndividual.gene.clear();
    }

    // Calculate Fitness Function
    if(evalFitnessPopulation(GA_Params, vPopulation)!=SUCCESS)
    {
        cout<<"Error! Fitness Function failed!"<<endl;
        _Exit(EXIT_FAILURE);
    }

    //showPopulation(vPopulation);
    return SUCCESS;
}



  int costBuild(struct Params GA_Params,int i){
    int score=0;
    if(GA_Params.InitialMap[i]<10){
      score -= GA_Params.InitialMap[i];
    }
    return score;
  }

  int fitBuild(struct Params GA_Params, int i,int building, int distance, int points){
    int score=0;
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

    //cout << "oooooooooooooo" << '\n';
    //updateMap(Individual,GA_Params);
    //cout << "eeeeeeeeeeeeee" << '\n';
    for(int i=0;i<(int) GA_Params.Map.size();i++){
      switch (GA_Params.Map[i]) {
        // Industrial buildings
        case 10:
          //Dificulty of building
          fitness += costBuild(GA_Params,i);
          // Industrial tiles benefit from being near other industry.
          //For each industrial tile within 2, there is a bonus of 3 points.
          fitness += fitBuild(GA_Params,i,10,2,3);
          break;
        case 11:
          //Dificulty of building
          fitness += costBuild(GA_Params,i);
          // Commercial sites benefit from being near residential tiles.
          // For each residential tile within 3 squares, there is a bonus of 5 points.
          fitness += fitBuild(GA_Params,i,12,3,5);
          // However, commercial sites do not like competition.
          //For each commercial site with 2 squares, there is a penalty of 5 points.
          fitness += fitBuild(GA_Params,i,11,2,-5);
          break;
        case 12:
          cout << "R" << '\n';
          //Dificulty of building
          fitness += costBuild(GA_Params,i);
          // Residential sites do not like being near industrial sites.
          // For each industrial site within 3 squares there is a penalty of 5 points.
          fitness += fitBuild(GA_Params,i,10,3,-5);
          // However, for each commercial site with 3 squares there is a bonus of 5 points.
          fitness += fitBuild(GA_Params,i,11,3,5);
          break;
        case 13:
          // Former toxic waste site: Industrial zones within 2 tiles take a penalty of -10.
          // Commercial and residential zones within 2 tiles take a penalty of -20.
          fitness += fitBuild(GA_Params,i,10,2,-10);
          fitness += fitBuild(GA_Params,i,11,2,-20);
          fitness += fitBuild(GA_Params,i,12,2,-20);
          break;
        case 14:
          // scenic view.  Residential zones within 2 tiles gain a bonus of 10 points.
          fitness += fitBuild(GA_Params,i,12,2,10);
          break;
        default:
          break;
      }
    }
    //cleanMap(Individual,GA_Params);

    return fitness;

    //
    // long long int seed = std::chrono::steady_clock::now().time_since_epoch().count();
    // std::mt19937 generator (seed);
    // return generator()%100;

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

// This is used to sort vPopulation[i].fitnessan array. It is the condition of sorting
bool wayToSort(individual i, individual j) { return i.fitness > j.fitness; }

// This function evolve the past generation and create the new generation using Elitism, Crossover and Mutation
struct individual evolvePopulation(struct Params GA_Params, vector<struct individual> &vPopulation){
    vector<struct individual> vNewPopulation;
    vector<struct individual> vElitism;
    long int iCountElitism=GA_Params.iSizeOfPopulation*GA_Params.iMaxElitism/100;   //Number of elitist individuals
    long int iCountMutation=GA_Params.iSizeOfPopulation*GA_Params.iMaxMutation/100; //Number of mutated individuals
    struct individual newIndividual;

    // Save the best individuals -> Elitism
      vElitism=vPopulation;
      // Sort the array and take only the iCountElitism first elements
      std::sort(vElitism.begin(),vElitism.end(),wayToSort);
      vElitism.erase(vElitism.begin()+iCountElitism,vElitism.end());

    // Generate crossover
      for(long i=0;i<(GA_Params.iSizeOfPopulation-iCountElitism-iCountMutation);i++){
          do {
              newIndividual = getNewIndividualByCrossover(vPopulation, GA_Params);
          }while(!isAnIndividualValid(GA_Params,newIndividual));
          vNewPopulation.push_back(newIndividual);
      }

    // Insert the Elite elements randomically in the new generation of individuals
    int iSize=vElitism.size();
        for(int i=0;i<iSize;i++){
            long iPos=getRandom(vNewPopulation.size());
            vNewPopulation.insert(vNewPopulation.begin()+iPos,vElitism.back());
            vElitism.pop_back();
        }

    // Insert mutations
    for(int i=0;i<iCountMutation;i++){
        do {
            long iPos = getRandom(vPopulation.size());    //For getting a random individual from the population
            newIndividual = vPopulation[iPos];
            iPos = getRandom(GA_Params.iSizeOfGene);      //For getting the position to mutate
            long newValue = getRandom((GA_Params.iSizeOfField - 1) + 1);  //For getting the new value for the mutation
            newIndividual.gene[iPos] = newValue;
        }while(!isAnIndividualValid(GA_Params,newIndividual));
        newIndividual.fitness = 0;
        long iPos = getRandom(vNewPopulation.size());       //For getting the position en the newGeneration array
        vNewPopulation.insert(vNewPopulation.begin()+iPos,newIndividual);
    }

    // Calculate Fitness Function
    if(evalFitnessPopulation(GA_Params, vNewPopulation)!=SUCCESS)
    {
        cout<<"Error! Fitness Function failed!"<<endl;
        _Exit(EXIT_FAILURE);
    }
/*    for(int k=1;k<vNewPopulation.size();k++)
    {
        cout<<vNewPopulation[k].fitness<<" "<<endl;
    }
    cout<<endl;*/
    // Find the best individual (min)
    int Pos=0;
    vector<struct individual>::iterator iBestValue;
    iBestValue=std::min_element(vNewPopulation.begin(),vNewPopulation.end(),wayToSort);
    Pos=std::distance(vNewPopulation.begin(),iBestValue);

    //showPopulation(vNewPopulation);
    return vNewPopulation[Pos];

}

// This function generates new individues using crossover. It is used in evolve function
struct individual getNewIndividualByCrossover(vector<struct individual> &vPopulation, struct Params GA_Params){
    struct individual Parents[2];  //Parents to crossover
    Parents[0].fitness=20000;
    Parents[1].fitness=20000;
    struct individual temp;

    // Select the parents
    switch (GA_Params.iMethodSelection){
        case TOURNAMENT:
                for(int i=0;i<2;i++){
                    for(int j=0;j<MAX_TOURNAMENT;j++){
                        temp=vPopulation[getRandom(GA_Params.iSizeOfPopulation)];
                        if(temp.fitness<Parents[i].fitness)
                            Parents[i]=temp;
                    }
                }
            break;
    }

    // Make Crossover
    temp.fitness=0;
    switch(GA_Params.iMethodCrossover){
        case RANDOM:
            int iCross=getRandom(GA_Params.iSizeOfGene-1)+1;  //Threshold for the crossover
            Parents[0].gene.erase(Parents[0].gene.begin()+iCross,Parents[0].gene.end());
            Parents[1].gene.erase(Parents[1].gene.begin(),Parents[1].gene.begin()+iCross);
            temp=Parents[0];
            temp.gene.insert(temp.gene.end(),Parents[1].gene.begin(),Parents[1].gene.end());
            break;
    }
    //showPopulation(vPopulation);
    if(isAnIndividualValid(GA_Params,temp)){
        return temp;
    }else {
        temp.fitness=-10000;  //To indicate that it is an invalid individual
        return temp;
    }
}



// Main function for the genetic algorithm
int genetic(int argc,char* argv[]){
  vector <struct individual> vPopulation;
  vector <struct individual> finalPopulation;
    struct Params GA_Params;
    struct individual iGoalReached;
    long iter=0;

    //For measurement the time ellased
    auto tStart= std::chrono::steady_clock::now();


    //Init the parameters of the Genetic Algorithm.
    GA_Params.file = argv[1];
    //GA_Params.iSizeOfGene=3;
    GA_Params.iSizeOfPopulation=20;
    GA_Params.iMethodSelection=TOURNAMENT;
    GA_Params.iMethodCrossover=RANDOM;
    GA_Params.iMaxElitism=MAX_ELITISM;
    GA_Params.iMaxMutation=MAX_MUTATION;
    GA_Params.iTime=10000; //milliseconds
    GA_Params.iNroIterations=100;
    GA_Params.vTypes.push_back(INDUSTRIAL);
    GA_Params.vTypes.push_back(COMMERCIAL);
    GA_Params.vTypes.push_back(RESIDENTIAL);

    readMap(GA_Params);


    // //Fitness testing
    // struct individual Individual;
    // Individual.gene.push_back(16);
    // Individual.gene.push_back(1);
    // Individual.gene.push_back(18);
    // Individual.gene.push_back(8);
    // Individual.gene.push_back(12);
    //
    // //for(int i = 0;i<100;i++){
    // cout<<"Fitness: "<<fitnessFnc(GA_Params,Individual)<< '\n';
    // //}


    //Init the first generation of population
    if(initPopulation(GA_Params, vPopulation)!=SUCCESS)
    {
        cout<<"Error! A new population cannot be generated!"<<endl;
        _Exit(EXIT_FAILURE);
    }
    long iTime=0;

    while(iter<GA_Params.iNroIterations&&iTime<GA_Params.iTime){
    //while(iter<30){
        // Iterate with the next generations
        iGoalReached=evolvePopulation(GA_Params, vPopulation);
        finalPopulation.push_back(iGoalReached);
        //cout<<"["<<iGoalReached.gene[0]<<" "<<iGoalReached.gene[1]<<" "<<iGoalReached.gene[2]<<"] Fitness: "<<iGoalReached.fitness<<endl;
        auto tEnd= std::chrono::steady_clock::now();
        iTime=std::chrono::duration_cast<std::chrono::milliseconds>(tEnd-tStart).count();
        iter++;
    }

    /* Show information of the process */
    cout<<"Simulation finished after "<<iTime<<" ms **********************************"<<endl;
    cout<<endl<<"S T A T I S T I C S   O F   T H E   S I M U L A T I O N:"<<endl<<endl;
    cout<<"  Algorithm: Genetic Algorithm"<<endl;
    cout<<"  Selection Method: TOURNAMENT"<<endl;
    cout<<"  Crossover Method: RANDOM"<<endl;
    cout<<"  Population:"<<GA_Params.iSizeOfPopulation<<endl;
    cout<<"  %Elitism: "<<GA_Params.iMaxElitism<<"% \t %Mutations: "<<GA_Params.iMaxMutation*90/100<<"%";
    cout<<"\t%Crossover:"<<100-GA_Params.iMaxElitism-GA_Params.iMaxMutation*90/100<<"%"<<endl;
    cout<<"  Max_Iterations: "<<GA_Params.iNroIterations<<"\tIterations:"<<iter--<<endl;
    cout << '\n';
    updateMap(iGoalReached,GA_Params);
    finalPrint(GA_Params);;
    cout<<"  Score: "<<iGoalReached.fitness<<endl;
    cout << '\n';
    cout<<endl<<"Exiting of the simulation..."<<endl;
    saveCSV_File(finalPopulation);


    return 1;
}


int updateMap(struct individual Individual, struct Params &params){

  int possition= 0;

  for(int i=0;i< params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = INDUSTRIAL;
  }

  for(int i= params.iNroIndustrialPlaces;i< params.iNroComercialPlaces + params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = COMMERCIAL;
  }

  for(int i=params.iNroComercialPlaces+params.iNroIndustrialPlaces;i< params.iNroResidencialPlaces+ params.iNroComercialPlaces+params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = RESIDENTIAL;
  }
  return 1;
}

int cleanMap(struct individual Individual, struct Params &params){

  int possition= 0;

  for(int i=0;i< params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = params.InitialMap[possition];
  }

  for(int i= params.iNroIndustrialPlaces;i< params.iNroComercialPlaces + params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = params.InitialMap[possition];
  }

  for(int i=params.iNroComercialPlaces+params.iNroIndustrialPlaces;i< params.iNroResidencialPlaces+ params.iNroComercialPlaces+params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = params.InitialMap[possition];
  }
  return 1;
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
            for (int j = 0; j <(int) Pos.size(); j++) {
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

/* Only for debuggin functions */
void showGene(struct individual Gene){
    cout<<endl<<"Fitness:"<<Gene.fitness<<endl;
    cout<<"Genes:";
    for(int n:Gene.gene){
        cout<<n<<" ";
    }
}

void showPopulation(vector<struct individual> &vPopulation){
    for(struct individual n:vPopulation){
        cout<<n.fitness<<" ";
    }
    cout<<endl;
}
