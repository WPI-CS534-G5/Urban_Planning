

#include "global.h"
#include "genetic.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main(int argc,char* argv[]){


  // Here we need to write all the exceptions for input
// and choose an algorithm based om the input
//Genetic algorithm for Urban Planning
  genetic(argc,argv);
  //HillClimbing(argc,argv);
  //return 1;




  //
  // ifstream file(argv[2]);
  // std::cout << "Urban Planning" << '\n';
  // if (argc!= 2) {
  // 	std::cout << "Wrong input, please run again !!!" << '\n';
  // 	return EXIT_FAILURE;
  // }
  // int Algorithm;
  // std::cout << " Menu:" << '\n';
  // std::cout << "1-->Genetic Algorithm" << '\n';
  // std::cout << "2-->Hill Climbing Algorithm" << '\n';
  // std::cin >> Algorithm;
  // if (Algorithm > 2||Algorithm<1) {
  // 	std::cout << "Wrong input, you can either type 1 for a Genetic Algorithm approach, or 2 for Hill Climbing !!!" << '\n';
  // 	return EXIT_FAILURE;
  // }
  //
  //
  // if (file.is_open()){
  //   char c;
  //
  //   commercialBuildings = std::stoi file.get(c);
  //   industrialBuildings = std::stoi file.get(c);
  //   residentialBuildings = (int) file.get(c);
  //   while ( getline (myfile,line)){
  //     cout << line << '\n';
  //   }
  //   file.close();
  // }else{
  //   cout << "Unable to open file";
  //   return 0;
  // }
  //
  //
  // return 1;


  return 1;

}
