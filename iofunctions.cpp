
#include "iofunctions.h"


int readMap(struct Params params){

  string line;
  ifstream myfile (name);
  if (myfile.is_open()){

      getline (myfile,line);
      params.iNroIndustrialPlaces = line.at(0) - '0';

      getline (myfile,line);
      params.iNroComercialPlaces = line.at(0) - '0';

      getline (myfile,line);
      params.iNroResidencialPlaces = line.at(0) - '0';

      int rows = 0;
      int columns = 0;
      vector<vector<int>> Map;
    while ( getline (myfile,line)){
      columns = 0;
      vector<int> row;
      for (int i =0; i < line.length(); i++){
        if(line.at(i) == 'X'){
          row.push_back(TOXIC_SITE);
          columns++;
        }else if(line.at(i)=='S'){
          row.push_back(SCENIC_VIEW);
          columns++;
        }else if((line.at(i) - '0')>=0 && (line.at(i) - '0')<=9){
          row.push_back(line.at(i) - '0');
          columns++;
        }
      }
      Map.push_back(row);
      rows++;
    }

    myfile.close();
  }else{
    cout << "Unable to open file"<< '\n';
    return 0;
  }

  for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
      params.Map.push_back(Map[i][j]);
    }
  }

  params.iNroRowsField =rows;
  params.iNroColField = columns;

  return 1;
}

int printMap(vector<vector<int>> map){

  cout << "MAP" << '\n';
  for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
      cout << Map[i][j]<<",";
    }
    cout << '\n';
  }

  return 1;
}
