#pragma once //famoso ifndef
#include <limits>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>

using namespace std;

struct Pessoa {
    int pos;
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
    cout << "3 - Exluir pessoa" << endl;
    cout << "4 - Sair" << endl << endl;
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

void ordenar(vector<Pessoa>& p){
    Pessoa menor, temp;
    int posMenor;
    for(int i = 0; i < p.size(); i++){
        menor = p[i];
        posMenor = i;
        for (int j = i; j < p.size(); j++){
            if (strcmp(p[j].nome, menor.nome) < 0){
                menor = p[j];
                posMenor = j;
            }
        }
        temp = p[i];
        p[i] = menor;
        p[posMenor] = temp;
    }

    // atualiza as posicoes;
    for (int i = 0; i < p.size(); i++){
        p[i].pos = i+1;
    }
}

void atualiza_arquivo(string nome_arquivo){
    for (int i = 0; i < 4; i++) nome_arquivo.pop_back();
    string temp = nome_arquivo + "_temp.txt";
    nome_arquivo += ".txt";

    vector<Pessoa> p_final;

    // Abre os arquivos, mas só tenta ler se existirem
    ifstream arq(nome_arquivo);
    if (arq.is_open()) {
        Pessoa p;
        string linha;

        while (getline(arq, linha)) {
            remove_final(linha);
            p.pos = stoi(linha);

            getline(arq, linha);
            remove_final(linha);
            strncpy(p.nome, linha.c_str(), sizeof(p.nome));
            p.nome[sizeof(p.nome) - 1] = '\0';

            getline(arq, linha);
            remove_final(linha);
            strncpy(p.telefone, linha.c_str(), sizeof(p.telefone));
            p.telefone[sizeof(p.telefone) - 1] = '\0';

            getline(arq, linha);
            sscanf(linha.c_str(), "%d/%d/%d", &p.dn_dia, &p.dn_mes, &p.dn_ano);

            getline(arq, linha);
            remove_final(linha);
            strncpy(p.cidade, linha.c_str(), sizeof(p.cidade));
            p.cidade[sizeof(p.cidade) - 1] = '\0';

            getline(arq, linha);
            remove_final(linha);
            strncpy(p.cep, linha.c_str(), sizeof(p.cep));
            p.cep[sizeof(p.cep) - 1] = '\0';

            getline(arq, linha);
            remove_final(linha);
            strncpy(p.email, linha.c_str(), sizeof(p.email));
            p.email[sizeof(p.email) - 1] = '\0';

            p_final.push_back(p);
        }
        arq.close();
    }

    ifstream arq_temp(temp);
    if (arq_temp.is_open()) {
        Pessoa p;
        string linha;

        while (getline(arq_temp, linha)) {
            remove_final(linha);
            p.pos = stoi(linha);

            getline(arq_temp, linha);
            remove_final(linha);
            strncpy(p.nome, linha.c_str(), sizeof(p.nome));
            p.nome[sizeof(p.nome) - 1] = '\0';

            getline(arq_temp, linha);
            remove_final(linha);
            strncpy(p.telefone, linha.c_str(), sizeof(p.telefone));
            p.telefone[sizeof(p.telefone) - 1] = '\0';

            getline(arq_temp, linha);
            sscanf(linha.c_str(), "%d/%d/%d", &p.dn_dia, &p.dn_mes, &p.dn_ano);

            getline(arq_temp, linha);
            remove_final(linha);
            strncpy(p.cidade, linha.c_str(), sizeof(p.cidade));
            p.cidade[sizeof(p.cidade) - 1] = '\0';

            getline(arq_temp, linha);
            remove_final(linha);
            strncpy(p.cep, linha.c_str(), sizeof(p.cep));
            p.cep[sizeof(p.cep) - 1] = '\0';

            getline(arq_temp, linha);
            remove_final(linha);
            strncpy(p.email, linha.c_str(), sizeof(p.email));
            p.email[sizeof(p.email) - 1] = '\0';

            p_final.push_back(p);
        }
        arq_temp.close();
    }

    // Ordena e atualiza as posições
    ordenar(p_final);

    // Remove os arquivos antigos
    remove(nome_arquivo.c_str());
    remove(temp.c_str());

    // Recria o principal 
    ofstream arq2(nome_arquivo);
    if (!arq2) {
        cerr << "Erro ao criar novo arquivo de dados." << endl;
        return;
    }

    for (auto &p : p_final){
        arq2 << p.pos << endl 
             << p.nome << endl
             << p.telefone << endl
             << p.dn_dia << "/" << p.dn_mes << "/" << p.dn_ano << endl
             << p.cidade << endl
             << p.cep << endl
             << p.email << endl;
    }

    arq2.close();
}

void adicionar(string nome_arquivo){
    for (int i = 0; i < 4; i++) nome_arquivo.pop_back();
    string temp = nome_arquivo + "_temp.txt";
    nome_arquivo += ".txt";

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

    ofstream arquivo(temp, ios::app);  // ofstream para escrever no arquivo

    if (!arquivo){
        cerr << "Erro ao abrir o arquivo para escrita. Aperte enter para voltar" << endl;
        limpa_buffer();
        cin.get();  // espera um caracter para prosseguir
        delete p;
        return;
    }

    arquivo << '0' << endl  // pos sempre inicia 0
            << p->nome << endl
            << p->telefone << endl
            << p->dn_dia << "/" << p->dn_mes << "/" << p->dn_ano << endl
            << p->cidade << endl
            << p->cep << endl
            << p->email << endl;
    arquivo.close();  // fechar arquivo
    delete p;  // free(p) 
}

void buscar(string nome_arquivo){
    string nome;
    cout << "Digite o nome a ser procurado: ";
    limpa_buffer();
    getline(cin, nome);  // permite entrada com espaços

    ifstream arquivo(nome_arquivo);  // abre arquivo para leitura

    if (!arquivo){
        cerr << "Erro ao abrir o arquivo ou arquivo inexistente. Aperte enter para voltar: ";
        cin.get();
        return;
    }

    Pessoa p;
    string linha;
    string dn;
    bool encontrado = false;

    while (getline(arquivo, linha)) {
        remove_final(linha);
        if (linha.empty() || !isdigit(linha[0])) continue;  // pula linhas inválidas
        p.pos = stoi(linha);

        // nome
        if (!getline(arquivo, linha)) break;
        remove_final(linha);
        strncpy(p.nome, linha.c_str(), sizeof(p.nome));
        p.nome[sizeof(p.nome) - 1] = '\0';

        // telefone
        if (!getline(arquivo, linha)) break;
        remove_final(linha);
        strncpy(p.telefone, linha.c_str(), sizeof(p.telefone));
        p.telefone[sizeof(p.telefone) - 1] = '\0';

        // data de nascimento
        if (!getline(arquivo, dn)) break;

        // cidade
        if (!getline(arquivo, linha)) break;
        remove_final(linha);
        strncpy(p.cidade, linha.c_str(), sizeof(p.cidade));
        p.cidade[sizeof(p.cidade) - 1] = '\0';

        // cep
        if (!getline(arquivo, linha)) break;
        remove_final(linha);
        strncpy(p.cep, linha.c_str(), sizeof(p.cep));
        p.cep[sizeof(p.cep) - 1] = '\0';

        // email
        if (!getline(arquivo, linha)) break;
        remove_final(linha);
        strncpy(p.email, linha.c_str(), sizeof(p.email));
        p.email[sizeof(p.email) - 1] = '\0';

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

    cout << "\n=== Pessoa Encontrada ===" << endl;
    cout << "Posicao: " << p.pos << endl;
    cout << "Nome: " << p.nome << endl;
    cout << "Telefone: " << p.telefone << endl;
    cout << "Data de nascimento: " << dn << endl;
    cout << "Cidade: " << p.cidade << endl;
    cout << "CEP: " << p.cep << endl;
    cout << "Email: " << p.email << endl;

    cout << "\nAperte enter para voltar. ";
    cin.get();  

    arquivo.close();
}

void excluir(string nome_arquivo){
    for (int i = 0; i < 4; i++) nome_arquivo.pop_back();
    string temp = nome_arquivo + "_temp.txt";
    nome_arquivo += ".txt";

    string alvo, atual;
    cout << "Digite a nome que deseja excluir: ";
    limpa_buffer();
    getline(cin, alvo);

    ifstream arq(nome_arquivo);
    ofstream arq_temp(temp);

    if (!arq.is_open() || !arq_temp.is_open()) {
        cerr << "Erro ao abrir arquivos." << endl;
        return;
    }

    Pessoa p;
    string linha;
    int cont = 1;
    bool encontrado = false;
    
    while(getline(arq, linha)){
        remove_final(linha);
        if (linha.empty()) continue;
        p.pos = stoi(linha);

        getline(arq, linha); remove_final(linha); strncpy(p.nome, linha.c_str(), sizeof(p.nome));
        
        getline(arq, linha); remove_final(linha); strncpy(p.telefone, linha.c_str(), sizeof(p.telefone));
        getline(arq, linha); sscanf(linha.c_str(), "%d/%d/%d", &p.dn_dia, &p.dn_mes, &p.dn_ano);
        getline(arq, linha); remove_final(linha); strncpy(p.cidade, linha.c_str(), sizeof(p.cidade));
        getline(arq, linha); remove_final(linha); strncpy(p.cep, linha.c_str(), sizeof(p.cep));
        getline(arq, linha); remove_final(linha); strncpy(p.email, linha.c_str(), sizeof(p.email));

        if (string(p.nome) == alvo){
            encontrado = true;
        }else {
            arq_temp << cont << endl
                 << p.nome << endl
                 << p.telefone << endl
                 << p.dn_dia << "/" << p.dn_mes << "/" << p.dn_ano << endl
                 << p.cidade << endl
                 << p.cep << endl
                 << p.email << endl;

                cont++;
        }  
    }
    arq_temp.close();
    
    remove(nome_arquivo.c_str());
    rename(temp.c_str(), nome_arquivo.c_str());

    if (encontrado) {
        cout << "Removido com sucesso. Aperte enter para voltar: ";
        cin.get();
    }else {
        cout << "Pessoa nao encontrada. Aperte enter para voltar: ";
        cin.get();
    }
    
}