#ifndef IOFUNCTIONS_H
#define IOFUNCTIONS_H

#include <c++/iostream>
#include <string>
#include <fstream>
#include "global.h"

using std::string;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;

int saveCSV_File(vector<struct individual>);
int readMap(struct Params &params);

/*
int readMap(struct Params &params);
int printMap(vector<vector<int>> map);*/

#endif  //IOFUNCTIONS.H