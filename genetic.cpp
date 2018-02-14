
#include <c++/random>
#include <c++/chrono>
#include <algorithm>
#include "genetic.h"


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

// Calculates the fitness of an individual
int fitnessFnc(struct Params GA_Params, struct individual nIndividual)
{
    /// Change this code with the conditions of the homework
    long long int seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    return generator()%100;
}

void pos2xy(struct Params GA_Params, int iPos, struct xyDato &Dato){

    Dato.y=(int)iPos/GA_Params.iNroColField;
    Dato.x=iPos%GA_Params.iNroColField;
}

int fitnessFnc1(struct Params GA_Params, struct individual Individual) {
    struct xyDato Gene;
    struct xyDato Terrain;
    int iValue = 0;
    int Pos = 0;
    int PosT = 0;
    int j = 0;
    int iDeltaX = 0;
    int iDeltaY = 0;
    int Distance = 0;
    /*
    cout<<GA_Params.iNroRowsField<<endl;
    cout<<GA_Params.iNroColField<<endl;
    cout<<GA_Params.iSizeOfField<<endl;*/
    //cout<<"Gene:"<<"["<<Individual.gene[0]<<" "<<Individual.gene[1]<<" "<<Individual.gene[2]<<"]"<<endl;
    Individual.fitness = 0;
    for (int n:Individual.gene) {
        iValue = iValue + n;
        Pos = iValue % GA_Params.iSizeOfField;
        pos2xy(GA_Params, Pos, Gene);
        if(GA_Params.Map[Pos]==SCENIC_VIEW)
            GA_Params.Map[Pos]=0;

        Individual.fitness=Individual.fitness-GA_Params.Map[Pos];
        //cout << "Type:" << GA_Params.vTypes[j] << "\tData: " << "X=" << Gene.x << " Y=" << Gene.y << "Fitness:"<<GA_Params.Map[Pos]<<endl;

        for (int i = 0; i < GA_Params.Map.size(); i++) {
            pos2xy(GA_Params, i, Terrain);
            if (GA_Params.Map[i] == TOXIC_SITE) {
                //cout << "TypeTerrain:" << GA_Params.Map[i] << "\tData: " << "X=" << Terrain.x << " Y=" << Terrain.y << endl;
                iDeltaX = abs(Terrain.x - Gene.x);
                iDeltaY = abs(Terrain.y - Gene.y);
                Distance = iDeltaY + iDeltaX;
                //cout<<"Fitness:"<<Individual.fitness<<endl;
                if (Distance <= 2) {
                    //cout << "Type:" << GA_Params.vTypes[j] << "\tData: " << "X=" << Gene.x << " Y=" << Gene.y << "Fitness:"<<GA_Params.Map[Pos]<<endl;
                    if (GA_Params.vTypes[j] == COMMERCIAL)
                        Individual.fitness = Individual.fitness - 20;
                    if (GA_Params.vTypes[j] == INDUSTRIAL)
                        Individual.fitness = Individual.fitness - 10;
                    if (GA_Params.vTypes[j] == RESIDENTIAL)
                        Individual.fitness = Individual.fitness - 20;
                }
            }
            if(GA_Params.Map[i]==SCENIC_VIEW){
                if(GA_Params.vTypes[j]==RESIDENTIAL){
                    iDeltaX = abs(Terrain.x - Gene.x);
                    iDeltaY = abs(Terrain.y - Gene.y);
                    Distance = iDeltaY + iDeltaX;
                    if(Distance<=2||Distance>0)
                        Individual.fitness = Individual.fitness + 10;
                }
            }
        }
        j++;
    }
    //cout<<"FitnessFnc:"<<Individual.fitness<<endl;
    return Individual.fitness;
}

// Calculates the fitness of all population
int evalFitnessPopulation(struct Params GA_Params, vector<struct individual> &vPopulation){
    if(vPopulation.size()==0)
        return FAILURE;
    for(int i=0;i<vPopulation.size();i++)
    {
        vPopulation[i].fitness=fitnessFnc1(GA_Params, vPopulation[i]);
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
    GA_Params.file = argv[1];  //
    GA_Params.iSizeOfGene=3;
    GA_Params.iSizeOfPopulation=10;
    GA_Params.iMethodSelection=TOURNAMENT;
    GA_Params.iMethodCrossover=RANDOM;
    GA_Params.iMaxElitism=MAX_ELITISM;
    GA_Params.iMaxMutation=MAX_MUTATION;
    GA_Params.iTime=1000; //milliseconds
    GA_Params.iNroIterations=3000;
    GA_Params.iSizeOfField=12;
    GA_Params.iNroColField=2;
    GA_Params.iNroRowsField=2;
 /*   GA_Params.Map.push_back(13);
    GA_Params.Map.push_back(9);
    GA_Params.Map.push_back(5);
    GA_Params.Map.push_back(9);
    GA_Params.Map.push_back(2);
    GA_Params.Map.push_back(2);
    GA_Params.Map.push_back(3);
    GA_Params.Map.push_back(3);
    GA_Params.Map.push_back(1);
    GA_Params.Map.push_back(4);
    GA_Params.Map.push_back(4);
    GA_Params.Map.push_back(4);*/
    GA_Params.vTypes.push_back(COMMERCIAL);
    GA_Params.vTypes.push_back(INDUSTRIAL);
    GA_Params.vTypes.push_back(RESIDENTIAL);

    // Load parameters from the File
    readMap(GA_Params);
    // Init the first generation of population
    if(initPopulation(GA_Params, vPopulation)!=SUCCESS)
    {
        cout<<"Error! A new population cannot be generated!"<<endl;
        _Exit(EXIT_FAILURE);
    }

    long iTime=0;
/*
    struct individual xx;
    xx.gene.push_back(1);
    xx.gene.push_back(3);
    xx.gene.push_back(1);
    cout<<fitnessFnc1(GA_Params,xx);

    vPopulation.push_back(xx);
    vPopulation[0].gene[0]=1;
    vPopulation[0].gene[1]=1;
    vPopulation[0].gene[2]=0;
    int a=isAnIndividualValid(GA_Params,xx);
    cout<<"Valid:"<<a<<endl;
    _Exit(EXIT_FAILURE);*/

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
    cout<<"  Size of Map: "<<GA_Params.iNroRowsField<<" Rows x "<<GA_Params.iNroColField<<" Columns"<<endl;
    cout<<"  Max_Iterations: "<<GA_Params.iNroIterations<<"\tIterations:"<<iter--<<endl;
    cout<<"  Best Fitness value: "<<iGoalReached.fitness<<endl;
    cout<<endl<<endl;
    saveCSV_File(finalPopulation);

    cout<<endl<<"Exiting of the simulation..."<<endl;

    return 1;
}

int isAnIndividualValid(struct Params GA_Params, struct individual nIndividual){
    vector<int> Pos;
    int iValue=0;
    int iSum=0;
    for(int i=0;i<nIndividual.gene.size();i++) {
        iSum = iSum + nIndividual.gene[i];
        iValue = iSum % GA_Params.iSizeOfField;
        //cout<<iSum<<" "<<iValue<<endl;

        if(GA_Params.Map[iValue]==TOXIC_SITE)  //Check if a building is not over a toxic zone
            return FAILURE;

        if (Pos.size() != 0) {     //Check if a building is not over another building
            for (int j = 0; j < Pos.size(); j++) {
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