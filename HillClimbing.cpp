#include "HillClimbing.h"


int HillClimbing(int argc,char* argv[]){
    struct Params HC_Params;
    struct individual seed;
    vector <struct individual> finalPopulation;
    struct individual iBestValue;
    auto tStart= std::chrono::steady_clock::now();

    /* Initializa parameters */
    HC_Params.file = argv[1];  //
    HC_Params.iSizeOfPopulation=1;
    HC_Params.iTime=1000; //milliseconds
    HC_Params.iNroIterations=500;

    /* Read the file for parameters */
    readMap(HC_Params);

    /* Get a seed */
    getASeed(HC_Params,seed);

    /* Check for the new position */
    struct individual iNewPos;
     int iter=0;
     int nroGen=0;
     int restart=0;

    long iTime=0;
    cout<<endl<<"Calculating the best configuration. Please wait!"<<endl;
    iBestValue.fitness=-1000;
     do {
         //showGene(seed);
         iNewPos = getNewPos(HC_Params, seed, nroGen);
         //showGene(iNewPos);
         nroGen++;
         if(nroGen>HC_Params.iSizeOfGene)
             nroGen=0;

         if(iNewPos.fitness>seed.fitness){
             finalPopulation.push_back(iNewPos);
             seed = iNewPos;
         }else{
             //cout<<"P Fitness: "<<iNewPos.fitness<<" N Fitness"<<seed.fitness<<endl;
             if(seed.fitness>iBestValue.fitness)
                 iBestValue=seed;
             getASeed(HC_Params,seed);
             restart++;
         }
         iter++;
         auto tEnd= std::chrono::steady_clock::now();
         iTime=std::chrono::duration_cast<std::chrono::milliseconds>(tEnd-tStart).count();
         if(iter%20==0)
             cout<<".";
     }while(iter<HC_Params.iNroIterations&&iTime<HC_Params.iTime);


/* Show information of the process */
    cout<<endl<<"Simulation finished after "<<iTime<<" ms **********************************"<<endl;
    cout<<endl<<"S T A T I S T I C S   O F   T H E   S I M U L A T I O N:"<<endl<<endl;
    cout<<"  Algorithm: Hill Climbing with restarts"<<endl;
    cout<<"  Number of Restarts:"<<restart;
    cout<<endl;
    // cout<<"  Size of Map: "<<HC_Params.iNroRowsField<<" Rows x "<<HC_Params.iNroColField<<" Columns"<<endl;
    // cout<<"  Number of buildings: "<<HC_Params.iSizeOfGene<<endl;
    cout<<"  Max_Iterations: "<<HC_Params.iNroIterations<<"\tIterations:"<<iter--<<endl;
    cout<<"  Best Fitness value: "<<iBestValue.fitness<<endl;

    cout << '\n';
    updateMap(iBestValue,HC_Params);
    finalPrint(HC_Params);
    cout<<"  Score: "<<iBestValue.fitness<<endl;
    cout << '\n';
    cout<<endl<<endl;
    saveCSV_File(finalPopulation);

    cout<<endl<<"Exiting of the simulation..."<<endl;

    return SUCCESS;


}

int getASeed(struct Params HC_Params, struct individual &newIndividual){
    int iValue=0;
    do {
        newIndividual.gene.clear();
        newIndividual.fitness=-1000;
        for (int j = 0; j < HC_Params.iSizeOfGene; j++) {
            iValue = getRandom(HC_Params.iSizeOfField);
            newIndividual.gene.push_back(iValue);
        }
    }while(!isAnIndividualValid(HC_Params, newIndividual));
    return SUCCESS;
}

bool wayToSort1(individual i, individual j) { return i.fitness > j.fitness; }
struct individual getNewPos(struct Params HC_Params,struct individual seed, int Gen){
    //Make a population
    vector<struct individual> vPopulation;
    vector<int> distances;
    struct individual seedTemp=seed;
    int iPos=0;
    int iSum=0;


    for(int i=0;i<HC_Params.iSizeOfGene;i++){
        iSum=iSum+seed.gene[i];
        iPos = iSum % HC_Params.iSizeOfField;
        distances.push_back(iPos);
        if(i!=Gen)
           HC_Params.Map[iPos]=HC_Params.vTypes[i];
    }
    //showGene(seedTemp);
    //cout<<endl;
    for(int i=0;i<(int)HC_Params.Map.size();i++){
        //cout<<HC_Params.Map[i]<<" ";
        if(HC_Params.Map[i]<10){
            seedTemp.gene[Gen]=i;
            if(i-distances[Gen+1]<0)
                seedTemp.gene[Gen+1]=abs(i-distances[Gen+1]);
            else
                seedTemp.gene[Gen+1]=HC_Params.Map.size()-abs(i-distances[Gen+1]);

            if(Gen>0){
                if(i-distances[Gen-1]<0)
                    seedTemp.gene[Gen]=i-distances[Gen-1]+HC_Params.Map.size();
                else
                    seedTemp.gene[Gen]=i-distances[Gen-1];
            }
            //cout<<endl<<"Distances:"<<i<<" "<<distances[Gen+1]<<" "<<i-distances[Gen+1]<<" ";
            //showGene(seedTemp);
            vPopulation.push_back(seedTemp);
            //showGene(seedTemp);
        }
    }

    if(evalFitnessPopulation(HC_Params, vPopulation)!=SUCCESS)
    {
        cout<<"Error! Fitness Function failed!"<<endl;
        _Exit(EXIT_FAILURE);
    }

    //saveCSV_File(vPopulation);

    // Find the best individual (min)
    int Pos=0;
    vector<struct individual>::iterator iBestValue;
    iBestValue=std::min_element(vPopulation.begin(),vPopulation.end(),wayToSort1);
    Pos=std::distance(vPopulation.begin(),iBestValue);

    //showPopulation(vNewPopulation);
    return vPopulation[Pos];


    //cout<<endl<<"Size:"<<vPopulation.size();

}
