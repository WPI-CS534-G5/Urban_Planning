#include "HillClimbing.h"

int HillClimbing(int argc,char* argv[]){
    struct Params HC_Params;
    vector<struct individual> vPopulation;

    /* Initializa parameters */
    HC_Params.iSizeOfPopulation=1;
    HC_Params.iSizeOfGene=4;
    HC_Params.iTime=1000; //milliseconds
    HC_Params.iNroIterations=10;
    HC_Params.iSizeOfField=16;

    if(initPopulation(HC_Params, vPopulation)!=SUCCESS)  //It creates only 1 individual for start the HillClimbing
    {
        cout<<"Error! A new population cannot be generated!"<<endl;
        _Exit(EXIT_FAILURE);
    }



}
