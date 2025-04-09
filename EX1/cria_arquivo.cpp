#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include <limits>
#include <cstring>
#include <cstdio>
#include <iomanip>

using namespace std;

struct Spessoa {
    char nome[50];
    char telefone[20];
    int dn_dia, dn_mes, dn_ano;
    char cidade[30];
    char cep[12];
    char email[50];
};

// Funcoes Secundárias
void limpa_tela(){  // seq Ansi para limpar tela
    cout << "\033[2J\033[H";
}

void limpa_buffer() {  // limpa buffer de entrada
    cin.clear();               
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void entrada(int ini, int fim, int *opcao){ // verifica se a entrada esta dentro do intervalo
    int a;
    cout << "Digite uma opção: ";
    cin >> a;
    while (a < ini || a > fim){
        cout << "Digite nomamente, intervalo aceito [" << ini << ',' << fim << ']' << endl;
        cout << "Digite uma opção: ";
        cin >> a;
    }
    *opcao = a;
}

void le_DN(Spessoa *p){  // verifica se eh uma data de nascimento valida
    bool continuar = true;

    while(continuar){
        cout << "\tData de Nascimento: " << endl;
        cout << "\t\tDia: ";
        cin >> p->dn_dia;
        cout << "\t\tMes: ";
        cin >> p->dn_mes;
        cout << "\t\tAno: ";
        cin >> p->dn_ano;

        vector<int> meses = {31,28,31,30,31,30,31,31,30,31,30,31};
        if ((p->dn_ano % 4 == 0 && p->dn_ano % 100 != 0) || (p->dn_ano % 400 == 0)) meses[1] = 29;
        if (p->dn_mes >= 1 && 
            p->dn_mes <= 12 &&
            p->dn_dia >= 1 &&
            p->dn_dia <= meses[p->dn_mes-1] && 
            p->dn_ano <= 2025) continuar = false;

        if (continuar) cout << "\tData nao existente, digite novamente" << endl;
    }
}

void remove_final(string linha){  // remove os espacos no final de uma string
    while(!linha.empty() && isspace(linha.back())) linha.pop_back();
}

// Funcoes Primárias
void adicionar(vector<Spessoa> &agenda){

    Spessoa pessoa;

    // Entrada relacionado a Pessoa
    cout << "Informaões sobre pessoa:" << endl;
    cout << "\tDigite o nome: ";
    limpa_buffer();
    cin.getline(pessoa.nome, 50);  // uso de cin.getline() pois queremos pegar espacos

    cout << "\tDigite o telefone: " ;
    cin.getline(pessoa.telefone, 20);

    le_DN(&pessoa);

    limpa_buffer();

    cout << "\tDigite a cidade: ";
    cin.getline(pessoa.cidade, 30);

    cout << "\tDigite o cep: ";
    cin.getline(pessoa.cep, 12);

    cout << "\tDigite o email: ";
    cin.getline(pessoa.email, 50);

    agenda.push_back(pessoa);

    cout << "Aperte enter para voltar.";
    cin.get();
}

void carrega_arquivo(vector<Spessoa> &agenda, string nome_arquivo){
    ifstream arq(nome_arquivo);

    if (!arq) {
        cout << "\nArquivo de agenda não encontrado. Criando novo arquivo. Aperte enter para continuar.";
        ofstream arq(nome_arquivo);
        cin.ignore();
        return;
    }

    string linha;
    Spessoa pessoa;

    while (getline(arq, linha)){
        remove_final(linha); strncpy(pessoa.nome ,linha.c_str(), sizeof(pessoa.nome));
        getline(arq, linha); remove_final(linha); strncpy(pessoa.telefone ,linha.c_str(), sizeof(pessoa.telefone));
        getline(arq, linha); remove_final(linha); sscanf(linha.c_str(), "%d/%d/%d", &pessoa.dn_dia, &pessoa.dn_mes, &pessoa.dn_ano);
        getline(arq, linha); remove_final(linha); strncpy(pessoa.cidade ,linha.c_str(), sizeof(pessoa.cidade));
        getline(arq, linha); remove_final(linha); strncpy(pessoa.cep ,linha.c_str(), sizeof(pessoa.cep));
        getline(arq, linha); remove_final(linha); strncpy(pessoa.email ,linha.c_str(), sizeof(pessoa.email));

        agenda.push_back(pessoa);
    }
}

void salva_arquivo(vector<Spessoa> &agenda, string nome_arquivo){
    remove(nome_arquivo.c_str());

    ofstream arq(nome_arquivo);

    if(arq.is_open()){
        for (auto &pessoa: agenda){
           arq << pessoa.nome << endl
               << pessoa.telefone << endl
       
               << setw(2) << pessoa.dn_dia << "/"  // setw para gravar no formato dd/mm/aaaa
               << setw(2) << pessoa.dn_mes << "/"
               << setw(4) << pessoa.dn_ano << endl
       
               << pessoa.cidade << endl
               << pessoa.cep << endl
               << pessoa.email << endl;
        }
    }else {
        cout << "Erro ao criar arquivo" << endl;
    }
    limpa_tela();
    cout << "Arquivo salvo com sucesso." << endl;
    arq.close();
}

int main(){
    int opcao;
    bool continuar = true;
    string arq;

    limpa_tela();
    cout << "Digite o nome do arquivo de salvamento: ";
    cin >> arq;
    limpa_buffer();

    vector<Spessoa> agenda;
    carrega_arquivo(agenda, arq);

    while(continuar){
        limpa_tela();
        cout << "1 - Adicionar pessoa na agenda" << endl;
        cout << "2 - Sair" << endl;
        
        entrada(1,2,&opcao);
        switch (opcao){
            case 1:
                limpa_tela();
                cout << "ADICIONAR PESSOA NA AGENDA " << endl << endl;
                adicionar(agenda);
            break;
            case 2:
                continuar = false;
            break;
        }
    }

    salva_arquivo(agenda,arq);
}
