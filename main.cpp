#include "genetic.h"
#include "HillClimbing.h"

int main(int argc,char* argv[]){

    int a=0;
  // Here we need to write all the exceptions for input
  // and choose an algorithm based om the input
  //Genetic algorithm for Urban Planning
    //genetic(argc,argv);
    a=HillClimbing(argc,argv);
    return 1;

}
