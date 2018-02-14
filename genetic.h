#ifndef GENETIC_H
#define GENETIC_H
#include <vector>
#include <c++/iostream>
#include "global.h"
#include "iofunctions.h"

using std::vector;
using std::cout; using std::endl;
using std::terminate;

/* Main function for the genetic algorith */
int genetic(int argc,char* argv[]);

/* makePopulation() : Generates the total number of individuals with random genes
 *  Input:  vector for generate a Population, Size of population, Size of gene
 *  Output: SUCCESS or FAIL */
int initPopulation(struct Params, vector<struct individual> &);

/* fitnessFnc() : Calculate the fitness for one individual
 *  Input:  An individual
 *  Output: Fitness Value */
int fitnessFnc(struct Params, struct individual);

/* evalFitnessPopulation() : Apply the fitnessFnc over all the population
 *  Input:  A population
 *  Output: SUCCESS or FAIL */
int evalFitnessPopulation(struct Params, vector<struct individual> &);

/* evolvePopulation() : It generates a new generation using Elitism, Crossover and Mutation and calculate the Fitness
 *  Input:  A population
 *  Output: The best individual in the new Population  */
struct individual evolvePopulation(struct Params, vector<struct individual> &);

/* getNewIndividualByCrossover() : It generates a new individual using crossover
 *  Input:  A population for the parents, Methods for  selecting and crossover
 *  Output: New Individual */
struct individual getNewIndividualByCrossover(vector<struct individual> &, struct Params GA_Params);

/* isAnIndividualValir() : It checks for the restrictions of the problem
 *  Input:  Restriccions, Individual
 *  Output: SUCCESS or FAILURE */
int isAnIndividualValid(struct Params, struct individual nIndividual);

/* Generic functions */
/* getRandom() : It gets a random number
 *  Input:  the MAX_NUMBER
 *  Output: A random number between 0 and MAX_NUMBER */
long getRandom(long);


/* Only for debuggin purpuses */
void showGene(struct individual Gene);
void showPopulation(vector<struct individual> &vPopulation);

#endif//for GENETIC.H