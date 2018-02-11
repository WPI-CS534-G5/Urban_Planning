#ifndef GLOBAL_H
#define GLOBAL_H
#include <vector>
using std::vector;

// ----- Global Definitions ----- //

#define INDUSTRIAL   10
#define COMMERCIAL  11
#define RESIDENTIAL 12
#define TOXIC_SITE  13
#define SCENIC_VIEW 14

#define SUCCESS     1
#define FAILURE     0

/* For genetic algorithms */
#define MAX_ELITISM     10  //Porcent the elite individual for the next generation
#define MAX_MUTATION    20  //Porcent the mutated individual for the next generation
#define MAX_TOURNAMENT  5

#define TOURNAMENT  1
#define RANDOM      2

#endif  //GLOBAL.H

// Basic structure of a Gene
struct individual{
    //individual(const vector<int> &gene);
    int fitness;
    int iType;
    long iPos;
    vector<int> gene;
};

// Genetic Algorithm Structure
struct Params{
    int iNroIndustrialPlaces;
    int iNroComercialPlaces;
    int iNroResidencialPlaces;
    int iSizeOfGene;
    int iSizeOfPopulation;
    int iSizeOfField;
    int iNroIterations;
    int iTime;
    int iMethodSelection;
    int iMethodCrossover;
    int iMaxElitism;
    int iMaxMutation;
};

