
#include <random>
#include <chrono>
#include <algorithm>
#include "genetic.h"
#include "iofunctions.h"


// Generates the total number of individuals with random genes
int initPopulation(struct Params GA_Params,vector<struct individual> &vPopulation){
    struct individual newIndividual;
    int iValue=0;

    for(int i=0;i<GA_Params.iSizeOfPopulation;i++)
    {
        for(int j=0;j<GA_Params.iSizeOfGene;j++)
        {
            iValue=getRandom(GA_Params.iSizeOfField-1)+1;
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



  void pos2xy(struct Params GA_Params, int iPos, struct xyDato &Dato){

      Dato.y=(int)iPos/GA_Params.iNroColField;
      Dato.x=iPos%GA_Params.iNroColField;
  }


  int fitnessFnc1(struct Params GA_Params, struct individual Individual) {
      struct xyDato Dato;
      struct xyDato Terrain;
      int iValue = 0;
      int Pos = 0;
      int PosT = 0;
      int j = 0;
      int iDeltaX = 0;
      int iDeltaY = 0;
      int Distance = 0;

      Individual.fitness = 0;
      for (int n:Individual.gene) {
          iValue = iValue + n;
          Pos = iValue % GA_Params.iSizeOfField;
          pos2xy(GA_Params, Pos, Dato);
          //cout << "Type:" << GA_Params.vTypes[j] << "\tData: " << "X=" << Dato.x << " Y=" << Dato.y << endl;

          for (int i = 0; i < GA_Params.Map.size(); i++) {
              pos2xy(GA_Params, i, Terrain);
              //cout << "TypeTerrain:" << GA_Params.Map[i] << "\tData: " << "X=" << Terrain.x << " Y=" << Terrain.y << endl;
              if (GA_Params.Map[i] == TOXIC_SITE) {
                  iDeltaX = abs(Terrain.x - Dato.x);
                  iDeltaY = abs(Terrain.y - Dato.y);
                  Distance = iDeltaY + iDeltaX;

                  if (Distance <= 2) {
                      if (GA_Params.vTypes[j] == COMMERCIAL)
                          Individual.fitness = Individual.fitness + 20;
                      if (GA_Params.vTypes[j] == INDUSTRIAL)
                          Individual.fitness = Individual.fitness + 10;
                      if (GA_Params.vTypes[j] == RESIDENTIAL)
                          Individual.fitness = Individual.fitness + 20;
                  }
              }
              if(GA_Params.Map[i]==SCENIC_VIEW){
                  if(GA_Params.vTypes[j]==RESIDENTIAL){
                      iDeltaX = abs(Terrain.x - Dato.x);
                      iDeltaY = abs(Terrain.y - Dato.y);
                      Distance = iDeltaY + iDeltaX;
                      if(Distance<=2)
                          Individual.fitness = Individual.fitness - 10;
                  }
              }
          }
          j++;
      }
      return Individual.fitness;
  }
  // Calculates the fitness of all population
  int evalFitnessPopulation(struct Params GA_Params, vector<struct individual> &vPopulation){
      if(vPopulation.size()==0)
          return FAILURE;
      for(struct individual &oneIndividual:vPopulation){
          oneIndividual.fitness=fitnessFnc1(GA_Params, oneIndividual);
      }
      return SUCCESS;
  }

// This is used to sort an array. It is the condition of sorting
bool wayToSort(individual i, individual j) { return i.fitness < j.fitness; }

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
          }while(newIndividual.fitness==-10000);
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
        }while(newIndividual.fitness==-10000);
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
    struct Params GA_Params;
    struct individual iGoalReached;
    long iter=0;

    //For measurement the time ellased
    auto tStart= std::chrono::steady_clock::now();


    //Init the parameters of the Genetic Algorithm.
    GA_Params.file = argv[1];
    GA_Params.iSizeOfGene=3;
    GA_Params.iSizeOfPopulation=20;
    GA_Params.iMethodSelection=TOURNAMENT;
    GA_Params.iMethodCrossover=RANDOM;
    GA_Params.iMaxElitism=MAX_ELITISM;
    GA_Params.iMaxMutation=MAX_MUTATION;
    GA_Params.iTime=10000; //milliseconds
    GA_Params.iNroIterations=1000;
    GA_Params.iSizeOfField=12;
    GA_Params.iNroColField=4;
    GA_Params.iNroRowsField=3;
    // GA_Params.Map.push_back(13);
    // GA_Params.Map.push_back(9);
    // GA_Params.Map.push_back(5);
    // GA_Params.Map.push_back(9);
    // GA_Params.Map.push_back(2);
    // GA_Params.Map.push_back(2);
    // GA_Params.Map.push_back(3);
    // GA_Params.Map.push_back(3);
    // GA_Params.Map.push_back(1);
    // GA_Params.Map.push_back(4);
    // GA_Params.Map.push_back(4);
    // GA_Params.Map.push_back(4);
    GA_Params.vTypes.push_back(COMMERCIAL);
    GA_Params.vTypes.push_back(INDUSTRIAL);
    GA_Params.vTypes.push_back(RESIDENTIAL);

    readMap(GA_Params);
    printMap(GA_Params);
    finalPrint(GA_Params);

    // Init the first generation of population
    if(initPopulation(GA_Params, vPopulation)!=SUCCESS)
    {
        cout<<"Error! A new population cannot be generated!"<<endl;
        _Exit(EXIT_FAILURE);
    }
    long iTime=0;

    //fitnessFnc1(GA_Params,vPopulation[0]);

    while(iter<GA_Params.iNroIterations&&iTime<GA_Params.iTime){
        // Iterate with the next generations
        iGoalReached=evolvePopulation(GA_Params, vPopulation);
        auto tEnd= std::chrono::steady_clock::now();
        iTime=std::chrono::duration_cast<std::chrono::milliseconds>(tEnd-tStart).count();
        iter++;
    }


    //updateMap(iGoalReached,GA_Params);

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
    cout<<"  Min Goal reached: "<<iGoalReached.fitness<<endl;
    cout<<endl<<"Exiting of the simulation..."<<endl;

    cout << '\n';
    for(int i=0; i< iGoalReached.gene.size(); i++){
      cout << " Position: " << iGoalReached.gene[i]<< '\n';
    }
    printMap(GA_Params);
    finalPrint(GA_Params);


    return 1;
}

int isAnIndividualValid(struct Params GA_Params, struct individual nIndividual){
    vector<int> residuals;
    bool bReturn=FAILURE;
    int iValue=0;
    int iSum;
    for(int i=0;i<(int)nIndividual.gene.size();i++){
        iSum=(iValue+nIndividual.gene[i]);
        iValue=iSum%GA_Params.iSizeOfField;
        if(iValue!=0){
            residuals.push_back(iValue);
            if(residuals.size()>1)
            {
                for(int j=0;j<(int)residuals.size()-1;j++){
                    if(iValue==residuals[j]){
                        return FAILURE;
                    }
                }
            }
        } else
            return FAILURE;
    }

    return SUCCESS;
}

//Get the Manhatan Distance
int manhatanDistance(int distance, int rows,int columns){
  return ((int) distance/columns)+(distance%columns);
}

int updateMap(struct individual Individual, struct Params &params){

  int possition= 0;
  int rows = params.iNroRowsField;
  int columns = params.iNroColField;
  int numOfI;
  int numOfC;

  for(int i=0;i< params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> rows*columns){
      possition -= rows*columns;
    }
    params.Map[possition] = INDUSTRIAL;
    numOfI = i;
  }

  for(int i= numOfI;i< params.iNroComercialPlaces + numOfI; i++){
    possition += Individual.gene[i];
    if(possition> rows*columns){
      possition -= rows*columns;
    }
    params.Map[possition] = COMMERCIAL;
    numOfC = i;
  }

  for(int i=numOfC;i< params.iNroResidencialPlaces+ numOfC; i++){
    possition += Individual.gene[i];
    if(possition> rows*columns){
      possition -= rows*columns;
    }
    params.Map[possition] = RESIDENTIAL;
  }
  return 1;
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
