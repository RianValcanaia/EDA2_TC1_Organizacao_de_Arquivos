#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <limits>
#include <cstring>
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

void limpa_tela(){  // seq Ansi para limpar tela
    cout << "\033[2J\033[H";
}

void limpa_buffer() {  // limpa buffer de entrada
    cin.clear();               
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void entrada(int ini, int fim, int *opcao){ // verifica se a entrada esta dentro do intervalo
    int a;
    cout << "Digite uma opcao: ";
    cin >> a;
    while (a < ini || a > fim){
        cout << "Digite nomamente, intervalo aceito [" << ini << ',' << fim << ']' << endl;
        cout << "Digite uma opcao: ";
        cin >> a;
    }
    *opcao = a;
}

void remove_final(string linha){
    while(!linha.empty() && isspace(linha.back())) linha.pop_back();
}

void buscar(vector<Spessoa> &agenda){
    limpa_tela();
    cout << "BUSCAR PESSOA " << endl << endl;

    string nome;
    cout << "Digite o nome a ser procurado: ";
    limpa_buffer();
    getline(cin, nome);  // realiza uma entrada ignirando espacos

    vector<Spessoa> encontradas;

    for (int i = 0; i < agenda.size(); i++){
        if (nome == string(agenda[i].nome)){
            encontradas.push_back(agenda[i]);
        }
    }

    if (encontradas.size() == 0) {
        cout << "Pessoa nao encontrada." << endl;
    }else{
        for (const auto &p: encontradas){
            cout << "Nome: " << p.nome << endl;
            cout << "Telefone: " << p.telefone << endl;
            cout << "Data de nascimento: " << setw(2) << p.dn_dia << setw(2) << p.dn_mes << setw(4) << p.dn_ano << endl;
            cout << "Cidade: " << p.cidade << endl;
            cout << "CEP: " << p.cep << endl;
            cout << "Email: " << p.email << endl << endl;
        }
    }

    cout << "Aperte enter para voltar. ";
    cin.get();  
}

void carrega_arquivo(vector<Spessoa> &agenda, string nome_arquivo){
    ifstream arq(nome_arquivo);

    if (!arq) {
        cout << "\nArquivo de Calendario não encontrado. Criando novo arquivo. Aperte enter para continuar.";
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

int main(){
    int opcao;
    bool continuar = true;
    string arq;

    limpa_tela();
    cout << "Digite o nome do arquivo de leitura: ";
    cin >> arq;
    limpa_buffer();

    vector<Spessoa> agenda;
    carrega_arquivo(agenda,arq);

    while(continuar){
        limpa_tela();
        
        cout << "1 - Buscar pessoa na agenda" << endl;
        cout << "2 - Sair" << endl;
        entrada(1,2,&opcao);
        switch (opcao){
            case 1:
                buscar(agenda);
                break;
            case 2:
                continuar = false;
                break;
        }
    }

}