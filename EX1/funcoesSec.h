#pragma once //famoso ifndef
#include <limits>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

struct Pessoa {
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

void menu(){
    cout << "1 - Adicionar pessoa" << endl;
    cout << "2 - Busca pelo nome" << endl;
    cout << "3 - Sair" << endl << endl;
}

void valida_DN(Pessoa *p){  // verifica se eh uma data de nascimento valida
    bool continuar = true;

    while(continuar){
        cout << "Data de Nascimento: " << endl;
        cout << "\tDia: ";
        cin >> p->dn_dia;
        cout << "\tMes: ";
        cin >> p->dn_mes;
        cout << "\tAno: ";
        cin >> p->dn_ano;

        vector<int> meses = {31,28,31,30,31,30,31,31,30,31,30,31};
        if ((p->dn_ano % 4 == 0 && p->dn_ano % 100 != 0) || (p->dn_ano % 400 == 0)) meses[1] = 29;
        if (p->dn_mes >= 1 && 
            p->dn_mes <= 12 &&
            p->dn_dia >= 1 &&
            p->dn_dia <= meses[p->dn_mes-1] && 
            p->dn_ano <= 2025) continuar = false;

        if (continuar) cout << "Data nao existente, digite novamente" << endl;
    }
}

void remove_final(string linha){
    while(!linha.empty() && isspace(linha.back())) linha.pop_back();
}

void adicionar(string nome_arquivo){
    limpa_tela();

    Pessoa *p = new Pessoa;
    
    limpa_buffer();

    cout << "Digite o nome: ";
    cin.getline(p->nome, 50);  // uso de cin.getline() pois queremos pegar espacos

    cout << "Digite o telefone: " ;
    cin.getline(p->telefone, 20);

    valida_DN(p);

    limpa_buffer();

    cout << "Digite a cidade: ";
    cin.getline(p->cidade, 30);

    cout << "Digite o cep: ";
    cin.getline(p->cep, 12);

    cout << "Digite o email: ";
    cin.getline(p->email, 50);

    ofstream arquivo(nome_arquivo, ios::app);  // ofstream para escrever no arquivo

    if (!arquivo){
        cerr << "Erro ao abrir o arquivo para escrita. Aperte enter para voltar" << endl;
        limpa_buffer();
        cin.get();  // espera um caracter para prosseguir
        delete p;
        return;
    }

    arquivo << p->nome << endl
            << p->telefone << endl
            << p->dn_dia << "/" << p->dn_mes << "/" << p->dn_ano << endl
            << p->cidade << endl
            << p->cep << endl
            << p->email << endl;
    arquivo.close();  // fechar arquivo
    delete p;  // free(p) 
}

void buscar(string nome_arquivo){
    limpa_tela();
    string nome;
    cout << "Digite o nome a ser procurado: ";
    limpa_buffer();
    getline(cin, nome);  // realiza uma entrada ignirando espacos

    ifstream arquivo(nome_arquivo);  // abre arquivo somente para leitura

    if (!arquivo){
        cerr << "Erro ao abrir o arquivo ou arquivo inexistente. Aperte enter para voltar: ";
        cin.get();
        return;
    }

    string dn;
    Pessoa p;
    bool encontrado = false;
    string linha;

    while (getline(arquivo, linha)){
        remove_final(linha);  // remove espacos no final
        strncpy(p.nome, linha.c_str(), sizeof(p.nome));  // copia o conteudo da string linha transformando ela em const char e depois colando em p.nome
        p.nome[sizeof(p.nome) -1] = '\0';


        getline(arquivo, linha);
        remove_final(linha);
        strncpy(p.telefone, linha.c_str(), sizeof(p.telefone));
        p.telefone[sizeof(p.telefone) -1] = '\0';

        getline(arquivo, dn);

        getline(arquivo, linha);
        remove_final(linha);
        strncpy(p.cidade, linha.c_str(), sizeof(p.cidade));
        p.cidade[sizeof(p.cidade)-1] = '\0';

        getline(arquivo, linha);
        remove_final(linha);
        strncpy(p.cep, linha.c_str(), sizeof(p.cep));
        p.cep[sizeof(p.cep) -1] = '\0';

        getline(arquivo, linha);
        remove_final(linha);
        strncpy(p.email, linha.c_str(), sizeof(p.email));
        p.email[sizeof(p.email) -1] = '\0';

        if (string(p.nome) == nome) {
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Pessoa nao encontrada." << endl;
        cout << "Aperte enter para voltar. ";
        cin.get();
        return;
    }

    cout << "Nome: " << p.nome << endl;
    cout << "Telefone: " << p.telefone << endl;
    cout << "Data de nascimento: " << dn << endl;
    cout << "Cidade: " << p.cidade << endl;
    cout << "CEP: " << p.cep << endl;
    cout << "Email: " << p.email << endl;

    cout << "Aperte enter para voltar. ";
    cin.get();  

    arquivo.close();
}
