#ifndef GENETIC_H
#define GENETIC_H

#include "global.h"
#include "iofunctions.h"
#include "fitness.h"


/* Main function for the genetic algorith */
int genetic(int argc,char* argv[]);

/* makePopulation() : Generates the total number of individuals with random genes
 *  Input:  vector for generate a Population, Size of population, Size of gene
 *  Output: SUCCESS or FAIL */
int initPopulation(struct Params, vector<struct individual> &);

/* evolvePopulation() : It generates a new generation using Elitism, Crossover and Mutation and calculate the Fitness
 *  Input:  A population
 *  Output: The best individual in the new Population  */
struct individual evolvePopulation(struct Params, vector<struct individual> &);

/* getNewIndividualByCrossover() : It generates a new individual using crossover
 *  Input:  A population for the parents, Methods for  selecting and crossover
 *  Output: New Individual */
struct individual getNewIndividualByCrossover(vector<struct individual> &, struct Params GA_Params);



/* Only for debuggin purpuses */
void showGene(struct individual Gene);
void showPopulation(vector<struct individual> &vPopulation);

#endif//for GENETIC.H
