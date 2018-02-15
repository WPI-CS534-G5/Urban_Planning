
#include "iofunctions.h"


int readMap(struct Params &params){

  string line;
  ifstream myfile (params.file);
  int rows = 0;
  int columns = 0;
  vector<vector<int>> Map;
  if (myfile.is_open()){

      getline (myfile,line);
      params.iNroIndustrialPlaces = line.at(0) - '0';

      for(int i=0;i<params.iNroIndustrialPlaces;i++){
        params.vTypes.push_back(INDUSTRIAL);
      }

      getline (myfile,line);
      params.iNroComercialPlaces = line.at(0) - '0';

      for(int i=0;i<params.iNroComercialPlaces;i++){
        params.vTypes.push_back(COMMERCIAL);
      }

      getline (myfile,line);
      params.iNroResidencialPlaces = line.at(0) - '0';

      for(int i=0;i<params.iNroResidencialPlaces;i++){
        params.vTypes.push_back(RESIDENTIAL);
      }

      params.iSizeOfGene= params.iNroIndustrialPlaces+ params.iNroComercialPlaces+params.iNroResidencialPlaces;

    while ( getline (myfile,line)){
      columns = 0;
      vector<int> row;
      for (int i =0; i < (int)line.length(); i++){
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
    _Exit(EXIT_FAILURE);
  }

  for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
      params.Map.push_back(Map[i][j]);
      params.InitialMap.push_back(Map[i][j]);
    }
  }
  params.iNroRowsField =rows;
  params.iNroColField = columns;
  params.iSizeOfField = rows*columns;

  return 1;
}

int printMap(struct Params &params){

  int rows = params.iNroRowsField;
  int columns = params.iNroColField;

  cout << "Initial Map" << '\n';
  for(int i=0;i<rows*columns;i++){
      cout << params.Map[i]<<",";
  }
  cout << '\n';
  return 1;
}


int finalPrint(struct Params &params){
  int rows = params.iNroRowsField;
  int columns = params.iNroColField;
  cout << "--------- Resulting Map ---------" << '\n';
  cout << '\n';
  cout << "  ";
  for(int i=0;i<rows*columns;i++){
      cout << convertNumToChar(params.Map[i])<<"|";
      if (((i+1)%columns == 0)&&(i!=0)){
        cout << '\n';
        cout << "  ";
      }
  }
  cout << '\n';
  return 1;
}

char convertNumToChar(int num){
  char character;
  switch (num) {
    case 10:
      character = 'I';
      break;
    case 11:
      character = 'C';
      break;
    case 12:
      character = 'R';
      break;
    case 13:
      character = 'X';
      break;
    case 14:
      character = 'S';
      break;
    default:
      character = ' ';
      break;
  }
  return character;
}

int updateMap(struct individual Individual, struct Params &params){

  int possition= 0;

  for(int i=0;i< params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = INDUSTRIAL;
  }

  for(int i= params.iNroIndustrialPlaces;i< params.iNroComercialPlaces + params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = COMMERCIAL;
  }

  for(int i=params.iNroComercialPlaces+params.iNroIndustrialPlaces;i< params.iNroResidencialPlaces+ params.iNroComercialPlaces+params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = RESIDENTIAL;
  }
  return 1;
}

int cleanMap(struct individual Individual, struct Params &params){

  int possition= 0;

  for(int i=0;i< params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = params.InitialMap[possition];
  }

  for(int i= params.iNroIndustrialPlaces;i< params.iNroComercialPlaces + params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = params.InitialMap[possition];
  }

  for(int i=params.iNroComercialPlaces+params.iNroIndustrialPlaces;i< params.iNroResidencialPlaces+ params.iNroComercialPlaces+params.iNroIndustrialPlaces; i++){
    possition += Individual.gene[i];
    if(possition> params.iNroRowsField*params.iNroColField){
      possition -= params.iNroRowsField*params.iNroColField;
    }
    params.Map[possition] = params.InitialMap[possition];
  }
  return 1;
}

int helpPrint(){
  cout << "HELP" << '\n';
  return 1;
}


int saveCSV_File(vector<struct individual> Data){
    ofstream outputFile;
    outputFile.open("fitness.txt");

    for(int i=0;i<(int)Data.size();i++)
    {
        outputFile<<Data[i].fitness<<endl;
    }
    outputFile.flush();
    outputFile.close();
    cout<<"fitness.txt Generated!: Log of fitness"<<endl;

    outputFile.open("behavior.txt");

    for(int i=0;i<(int)Data.size();i++)
    {
        for(int j=0;j<(int)Data[i].gene.size();j++){
            outputFile << Data[i].gene[j]<<" ";
        }
        outputFile<<endl;
    }
    outputFile.flush();
    outputFile.close();
    cout<<"behavior.txt Generated!: Log of iterations"<<endl;
    return 1;
}
