#ifndef GENETIC_H
#define GENETIC_H
#include <vector>
#include <c++/iostream>
#include "global.h"

using std::vector;
using std::cout; using std::endl;
using std::terminate;

// Basic structure of a Gene
struct individual{
    //individual(const vector<int> &gene);
    int fitness;
    vector<int> gene;
};

// Genetic Algorithm Structure
struct _GA_Params{
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

/* Main function for the genetic algorith */
int genetic(int argc,char* argv[]);

/* makePopulation() : Generates the total number of individuals with random genes
 *  Input:  vector for generate a Population, Size of population, Size of gene
 *  Output: SUCCESS or FAIL */
int initPopulation(struct _GA_Params, vector<struct individual> &);

int fitnessFnc(struct individual);

int evalFitnessPopulation(vector<struct individual> &);

struct individual evolvePopulation(struct _GA_Params, vector<struct individual> &);

struct individual getNewIndividualByCrossover(vector<struct individual> &, struct _GA_Params GA_Params);

/* Generic functions */
long getRandom(long);


/* Only for debuggin purpuses */
void showGene(struct individual Gene);
void showPopulation(vector<struct individual> &vPopulation);
#endif//for GENETIC.H