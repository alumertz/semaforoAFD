#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void readFile();

int main (){

    readFile();

    return 0;
}

void readFile(){
    string line, name, eInicial, eFinal;
    int lnum=0;
    vector<string> estados, alfabeto, transicoes;
    while (getline(std::cin, line)){
        if (lnum==0){
            name = line;
        }else if (lnum==1){
            line.erase(0,3);// apaga os tres caracteres iniciais
            istringstream linestream(line);
            string estado;
            while (getline(linestream, estado, ',')){//le até a ,
                estados.push_back(estado);
            }
        }else if(lnum==2){
            line.erase(0,3);// apaga os tres caracteres iniciais
            istringstream linestream(line);
            string letra;
            while (getline(linestream, letra, ',')){ //le até a ,
                alfabeto.push_back(letra);
            }
        }else if (lnum==3){
            line.erase(0,3);// apaga os tres caracteres iniciais
            eInicial = line;
        }else if(lnum==4){
            line.erase(0,3);// apaga os tres caracteres iniciais
            eFinal= line;
            
        }else{
            transicoes.push_back(line);
        }
        lnum++;
    }
}
