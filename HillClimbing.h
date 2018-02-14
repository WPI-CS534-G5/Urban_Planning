#ifndef HILLCLIMBING_H
#define HILLCLIMBING_H

#include "global.h"
#include "fitness.h"
#include "iofunctions.h"


// Main function for HillClimbing
int HillClimbing(int argc,char* argv[]);

/* evalFitness() : It evals an element of the map and creates a vector with the Fitness for each place
 *  Input:  A map, An individual, A population (for results)
 *  Output: SUCCESS OR FAILURE */
int evalFitness(int Map,struct individual evalIndividual,vector<struct individual> &);

int getASeed(struct Params, struct individual &);
struct individual getNewPos(struct Params,struct individual seed, int);


#endif //URBAN_PLANNING_HILLCLIMBING_H
