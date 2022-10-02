#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct state{
	string id; // só a parte "0", de q0, por exemplo
	vector<string> letra;
    vector<string> proxS;
    bool final=false;
    bool inicial=false;
    // um vetor que armazena infinitos arrays de 2 posicoes,
    // a posiçao 0 tem um simbolo do alfabeto e a 1 tem o estado a qual é levado
};

bool tab[1000][1000];

vector<state> states;

void readFile();
bool isReachable(state s);
void apagaTranParaEstado(string estado);
void printStates();
void eraseUnreachable();

int main (){

    readFile();

    cout << "\n\n";
    
    //não deter estados inacessiveis
    eraseUnreachable();

    //funcao deve ser total()

    cout << "\n\n";
    printStates();

    
    //areEqual();


    return 0;
}
/*
1. Teste de equivalência de estados
2. Unificação de estados equivalentes
3. Exclusão de estado inúteis
4. Construção do AF minimizado
*/

void eraseUnreachable(){
    vector<int> apaga;
    // eliminar estados inacessives
    for (int i=0;i<states.size();i++){
        //cout << "\n s" << states[i].id << isReachable(states[i]) <<"\n\n";
        if(!isReachable(states[i])){
            cout << "\n nreach "<< states[i].id<< "\n";
            //states.erase(states.begin()+i);
            apaga.push_back(i);
                       
            
            
        }
    }

    for (int x=0;x<apaga.size();x++){
        states.erase(states.begin()+apaga[x]);
    }
}

void printStates(){
    //só pra ver como estão salvos os estados e transiçoes
    for(int x=0;x<states.size();x++){
        cout << "\nest " << states[x].id;

        for (int y =0;y<states[x].letra.size();y++){
            cout << "\n    " <<states[x].letra[y]<< " " << states[x].proxS[y];
        }
    }
}

void apagaTranParaEstado(string estado){
    for(int x=0;x<states.size();x++){
        for (int y=0;y<states[x].proxS.size();y++){
            if(states[x].proxS[y]==estado){
                states[x].proxS.erase(states[x].proxS.begin()+y);
                states[x].letra.erase(states[x].letra.begin()+y);
            }
        } 
    }
}


bool isReachable(state s){
    if (s.inicial==true){
        return true;
    }
     //para um estado

    //cout << "\n\n estfunc " << s.id;

    for (int y=0;y<states.size();y++){ //procura um estado que leve a ele
        //cout << "\n est " << y;
        for(int z=0;z<states[y].proxS.size();z++){//percorre a lista de proximos estados de um estado
            //cout << "\n proxS " << states[y].proxS[z] ;
            if(states[y].proxS[z]==s.id){//se algum dos próximos estados é igual ao atual
                //cout << " entrou ";
                if(states[y].inicial==true){//se esse próximo estado é inicial
                    //cout << " entrou1 ";
                    return true;
                }else{
                    //cout << " entrou2 ";
                    return isReachable(states[y]);
                }
            }
        }
        //if (y==3){
        //    return false;
        //}
    }
    return false;
}

void readFile(){
    string line, name;
    int lnum=0;
    vector<string> estados, alfabeto, transicoes;
    
    state sta;
    string trans[2], letra, proxS;

    while (getline(std::cin, line)){

        if (lnum==0){
            name = line;
        }else if (lnum==1){ //le estados
            line.erase(0,3);// apaga os tres caracteres iniciais
            istringstream linestream(line);
            string estado;
            while (getline(linestream, estado, ',')){//le até a ,
                estados.push_back(estado);
                sta.id = estado.erase(0,1);
                states.push_back(sta);
            }
        }else if(lnum==2){ //le alfabeto
            line.erase(0,3);// apaga os tres caracteres iniciais
            istringstream linestream(line);
            string letra;
            while (getline(linestream, letra, ',')){ //le até a ,
                alfabeto.push_back(letra);
            }
        }else if (lnum==3){//le estado inicila
            line.erase(0,4);// apaga os quatro caracteres iniciais
            for(int x=0;x<states.size();x++){
                
                if (states[x].id==line){
                    states[x].inicial = true;
                }
            }

        }else if(lnum==4){//le estado final
            line.erase(0,4);// apaga os quatro caracteres iniciais
            for(int x=0;x<states.size();x++){
                
                if (states[x].id==line){
                    states[x].final = true;
                }
            }
            
        }else{
            transicoes.push_back(line);
            sta.id = line.substr(2,line.find(',')-2);
            line.erase(0, line.find(',')+1);
            sta.letra.clear();
            sta.proxS.clear();

            for(int x=0;x<states.size();x++){
                
                if (states[x].id==sta.id){
                    letra = line.substr(0,line.find(','));
                    line.erase(0, line.find(',')+1+1);

                    proxS = line.erase(line.find(')'),1);

                    states[x].letra.push_back(letra);
                    states[x].proxS.push_back(proxS);
                }
            }            
        }
        lnum++;
    }
}
