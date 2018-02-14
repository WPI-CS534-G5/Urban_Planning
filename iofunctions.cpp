#include "iofunctions.h"

int saveCSV_File(vector<struct individual> Data){
    ofstream outputFile;
    outputFile.open("fitness.txt");

    for(int i=0;i<Data.size();i++)
    {
        outputFile<<Data[i].fitness<<endl;
    }
    outputFile.flush();
    outputFile.close();
    cout<<"fitness.txt Generated!: Log of fitness"<<endl;

    outputFile.open("behavior.txt");

    for(int i=0;i<Data.size();i++)
    {
        for(int j=0;j<Data[i].gene.size();j++){
            outputFile << Data[i].gene[j]<<" ";
        }
        outputFile<<endl;
    }
    outputFile.flush();
    outputFile.close();
    cout<<"behavior.txt Generated!: Log of iterations"<<endl;
}

int readMap(struct Params &params){

    string line;
    ifstream myfile (params.file);
    int rows = 0;
    int columns = 0;
    vector<vector<int>> Map;
    if (myfile.is_open()){
        getline (myfile,line);
        params.iNroIndustrialPlaces = line.at(0) - '0';
        getline (myfile,line);
        params.iNroComercialPlaces = line.at(0) - '0';
        getline (myfile,line);
        params.iNroResidencialPlaces = line.at(0) - '0';

        while ( getline (myfile,line)){
            columns = 0;
            vector<int> row;
            for (int i =0; i < (int)line.length(); i++){
                //cout<<(int)line.at(i)<<" ";
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
        //cout<<"col:"<<columns<<" rows:"<<rows<<endl;
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
    params.iSizeOfField=rows*columns;
    return 1;
}
