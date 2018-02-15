

#include "global.h"
#include "genetic.h"
#include "HillClimbing.h"
#include "iofunctions.h"

using namespace std;

int main(int argc,char* argv[]){


  if(argc !=3){
    helpPrint();
    return 1;
  }
  string str1 (argv[2]);

  if(str1.compare("GA") == 0){
    genetic(argc,argv);
  }else if(str1.compare("HC") == 0){
    HillClimbing(argc,argv);
  }else{
    helpPrint();
    return 1;
  }





  return 1;
}
