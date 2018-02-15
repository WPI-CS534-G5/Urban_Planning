#ifndef FITNESS_H
#define FITNESS_H

#include "global.h"

/* fitnessFnc() : Calculate the fitness for one individual
 *  Input:  An individual
 *  Output: Fitness Value */
int fitnessFnc(struct Params GA_Params, struct individual Individual);

/* evalFitnessPopulation() : Apply the fitnessFnc over all the population
 *  Input:  A population
 *  Output: SUCCESS or FAIL */
int evalFitnessPopulation(struct Params, vector<struct individual> &);

/* isAnIndividualValir() : It checks for the restrictions of the problem
 *  Input:  Restriccions, Individual
 *  Output: SUCCESS or FAILURE */
int isAnIndividualValid(struct Params, struct individual nIndividual);


/* Generic functions */
/* getRandom() : It gets a random number
 *  Input:  the MAX_NUMBER
 *  Output: A random number between 0 and MAX_NUMBER */
long getRandom(long);
void showPopulation(vector<struct individual> &vPopulation);

void showGene(struct individual Gene);
void showMap(struct Params _Params);


int costBuild(struct Params GA_Params,int i);
int fitBuild(struct Params GA_Params, struct individual Individual, int i,int building, int distance, int points);
int fitMap(struct Params GA_Params, struct individual Individual, int i,int building, int distance, int points);
int manhatanDistance(int pos1,int pos2,struct Params GA_Params);

#endif  //FITNESS.H
