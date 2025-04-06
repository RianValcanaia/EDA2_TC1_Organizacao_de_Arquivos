#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"funcoesSec.h"

using namespace std;

int main(){
    int opcao;
    bool continuar = true;
    string arq;

    limpa_tela();
    cout << "Digite o nome do arquivo de salvamento: ";
    cin >> arq;
    limpa_buffer();

    while (continuar){
        limpa_tela();
        menu();
        entrada(1, 3, &opcao);
        switch (opcao){
            case 1:
            adicionar(arq);
            break;
            case 2:
            buscar(arq);
            break;
            case 3:
            continuar = false;
            break;
        }
    } 
}