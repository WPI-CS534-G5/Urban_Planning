
#ifndef IOFUNCTIONS_H
#define IOFUNCTIONS_H

#include "global.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

using std::vector;
using std::string;

int readMap(struct Params &params);
int printMap(struct Params &params);
int finalPrint(struct Params &params);

#endif  //IOFUNCTIONS.H
