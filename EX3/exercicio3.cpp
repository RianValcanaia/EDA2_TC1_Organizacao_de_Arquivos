#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include <limits>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include <map>

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

        if (continuar) cout << "\tData não existente, digite novamente" << endl;
    }
}

void remove_final(string linha){  // remove os espacos no final de uma string
    while(!linha.empty() && isspace(linha.back())) linha.pop_back();
}

void ordenar(vector<Spessoa> &agenda){
    Spessoa menor, temp;
    int posMenor;
    for(int i = 0; i < agenda.size(); i++){
        menor = agenda[i];
        posMenor = i;
        for (int j = i; j < agenda.size(); j++){
            if (strcmp(agenda[j].nome, menor.nome) < 0){
                menor = agenda[j];
                posMenor = j;
            }
        }
        temp = agenda[i];
        agenda[i] = menor;
        agenda[posMenor] = temp;
    }
}

// Funcoes Primárias
void adicionar(vector<Spessoa> &agenda){
    limpa_tela();
    cout << "ADICIONAR PESSOA NA AGENDA" << endl << endl;

    Spessoa pessoa;

    // Entrada relacionado a Pessoa
    cout << "Informações sobre pessoa:" << endl;
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

void listar_por_cidade(vector<Spessoa> &agenda){
    limpa_tela();
    cout << "LISTAR PESSOA(S) POR CIDADE" << endl << endl;

    string cidade;
    cout << "Digite a cidade que deseja buscar: ";
    limpa_buffer();
    getline(cin, cidade);  // realiza uma entrada ignirando espacos

    vector<Spessoa> encontradas;

    for (int i = 0; i < agenda.size(); i++){
        if (cidade == string(agenda[i].cidade)){
            encontradas.push_back(agenda[i]);
        }
    }

    if (encontradas.size() == 0) {
        cout << "Nenhuma pessoa encontrada desta cidade." << endl;
    }else{
        for (const auto &p: encontradas){
            cout << "Nome: " << p.nome << endl;
            cout << "Telefone: " << p.telefone << endl;
            cout << "Data de nascimento: " << setw(2) << p.dn_dia << "/" << setw(2) << p.dn_mes << "/" << setw(4) << p.dn_ano << endl;
            cout << "Cidade: " << p.cidade << endl;
            cout << "CEP: " << p.cep << endl;
            cout << "Email: " << p.email << endl << endl;
        }
    }

    cout << "Aperte enter para voltar. ";
    cin.get();  
}

void excluir(vector<Spessoa> &agenda){
    limpa_tela();
    cout << "EXCLUIR PESSOA NA AGENDA" << endl << endl;

    string nome;
    cout << "Digite o nome a ser exluido: ";
    limpa_buffer();
    getline(cin, nome);  // realiza uma entrada ignirando espacos

    map<int, Spessoa> encontradas;

    for (int i = 0; i < agenda.size(); i++){
        if (nome == string(agenda[i].nome)){
            encontradas[i] = agenda[i];
        }
    }

    if (encontradas.size() == 0) {
        cout << "Pessoa não encontrada." ;
    }else{
        if (encontradas.size() > 1){
            int i = 1, opcao;
            for (const auto &par: encontradas){
                const Spessoa &p = par.second;

                cout << i << ":" << endl; 
                cout << "\tNome: " << p.nome << endl;
                cout << "\tTelefone: " << p.telefone << endl;
                cout << "\tData de nascimento: " << setw(2) << p.dn_dia << setw(2) << p.dn_mes << setw(4) << p.dn_ano << endl;
                cout << "\tCidade: " << p.cidade << endl;
                cout << "\tCEP: " << p.cep << endl;
                cout << "\tEmail: " << p.email << endl << endl;
                i++;
            }
            cout << "Mais de uma ocorrência encontrada. ";
            entrada(1,encontradas.size(), &opcao);
            agenda.erase(agenda.begin() + opcao - 1);
            limpa_buffer();
        }else{
            agenda.erase(agenda.begin() + encontradas.begin()->first);
        }

        cout << "Pessoa excluida com sucesso. ";
    }

    cout << "Aperte enter para voltar. ";
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
    cout << "Arquivo salvo com sucesso!" << endl;

    arq.close();
}

void cria_arq_invertido(vector<Spessoa> &agenda, string nome_arquivo){
    for (int i = 0; i < 4; i++) nome_arquivo.pop_back();
    string nome_arquivo_invertido = nome_arquivo + "_invertido.txt";
   // nome_arquivo += ".txt";

    remove(nome_arquivo_invertido.c_str());
    ofstream arq_invertido(nome_arquivo_invertido);

    map<string, vector<Spessoa>> cidades;

    for (int i = 0; i < agenda.size(); i++){
        cidades[string(agenda[i].cidade)].push_back(agenda[i]);
    }

    for (const auto &par: cidades){
        vector<Spessoa> v = par.second;
        arq_invertido << par.first << endl;
        for (const auto &i: v){
            arq_invertido << "\t" << i.nome << endl
                          << "\t" << i.telefone << endl 
                          << "\t" << setw(2) << i.dn_dia << "/" << setw(2) << i.dn_mes << "/" << setw(4) << i.dn_ano << endl
                          << "\t" << i.cidade << endl
                          << "\t" << i.cep << endl
                          << "\t" << i.email << endl;
        }
    }

    arq_invertido.close();
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
        cout << "2 - Listar por cidade" << endl;
        cout << "3 - Excluir pessoa" << endl;
        cout << "4 - Sair" << endl;
        
        entrada(1,4,&opcao);
        switch (opcao){
            case 1:
                adicionar(agenda);
                ordenar(agenda);
            break;
            case 2:
                listar_por_cidade(agenda);
            break;
            case 3:
                excluir(agenda);
            break;
            case 4:
                continuar = false;
            break;
        }
        
        salva_arquivo(agenda,arq);
        cria_arq_invertido(agenda, arq);
    }
}