

#ifndef IOFUNCTIONS_H
#define IOFUNCTIONS_H

#include "global.h"

int readMap(struct Params &params);
int printMap(struct Params &params);
int finalPrint(struct Params &params);
char convertNumToChar(int num);
int saveCSV_File(vector<struct individual>);
int updateMap(struct individual Individual, struct Params &params);
int cleanMap(struct individual Individual, struct Params &params);
int helpPrint();

#endif  //IOFUNCTIONS.H
