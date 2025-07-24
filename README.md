<div align="center" id="topo">

<img src="https://media.giphy.com/media/iIqmM5tTjmpOB9mpbn/giphy.gif" width="200px" alt="Gif animado"/>

# <code><strong> Gerenciador de Agenda com Arquivos </strong></code>

<em>Trabalho prático sobre manipulação de arquivos sequenciais, sequenciais ordenados e invertidos.</em>

[![CPP Usage](https://img.shields.io/badge/C++-100%25-blue?style=for-the-badge&logo=cplusplus)]()
[![Status](https://img.shields.io/badge/Status-Concluído-green?style=for-the-badge)]()
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Visite%20meu%20perfil-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/rian-carlos-valcanaia-b2b487168/)

</div>

## Índice

- [📌 Objetivos](#-objetivos)
- [📥 Entradas do sistema](#-entradas-do-sistema)
- [🧱 Estruturas de Dados](#-estruturas-de-dados)
- [🧰 Funcionalidades](#-funcionalidades)
- [📊 Exemplo de Execução](#-exemplo-de-execução)
- [📂 Como executar](#-como-executar)
- [👨‍🏫 Envolvidos](#-envolvidos)
- [📅 Curso](#-curso)
- [📄 Código-fonte](#-código-fonte)

## 📌 Objetivos
O projeto consiste na implementação de um sistema de gerenciamento de agenda com o objetivo de praticar diferentes técnicas de manipulação e organização de arquivos.
* **Exercício 1**: Implementar o armazenamento de uma agenda de contatos em um **arquivo sequencial simples**, com funcionalidade de busca por nome.
* **Exercício 2**: Criar um **arquivo sequencial ordenado** pelo nome a partir do arquivo do exercício anterior, implementando operações de busca, inclusão e exclusão de registros, mantendo a ordem.
* **Exercício 3**: Construir um **arquivo invertido**, utilizando a cidade como chave de indexação, para permitir a listagem de todas as pessoas de uma determinada cidade, além de operações de inclusão e exclusão.

[⬆ Voltar ao topo](#topo)

## 📥 Entradas do sistema
O sistema interage com o usuário para receber as informações necessárias para a execução das tarefas.
* Nome do arquivo de texto (`.txt`) para carregar e salvar a agenda.
* Opções do menu selecionadas pelo usuário para executar as funcionalidades.
* Dados da pessoa (nome, telefone, data de nascimento, cidade, CEP, email) para inclusão de novos registros.
* Nome ou cidade como critério para realizar buscas, listagens e exclusões.

[⬆ Voltar ao topo](#topo)

## 🧱 Estruturas de Dados
A estrutura principal utilizada para armazenar os dados de cada contato na agenda é a `Spessoa`.

### 🔸 `Spessoa`
```cpp
typedef struct {
    char nome[50];
    char telefone[20];
    int dn_dia, dn_mes, dn_ano;
    char cidade[30];
    char cep[12];
    char email[50];
} Spessoa;
```
[⬆ Voltar ao topo](#topo)

## 🧰 Funcionalidades
### 🔹 Funções Principais
Estas são as funções que executam as operações centrais do sistema em cada exercício.

- `carrega_arquivo()`: Carrega os contatos de um arquivo de texto para a memória (vetor de Spessoa).
- `salva_arquivo()`: Salva os contatos da memória de volta para o arquivo de texto.
- `adicionar()`: Solicita ao usuário os dados de uma nova pessoa e a adiciona na agenda em memória.
- `buscar()`: Procura por uma pessoa na agenda pelo nome e exibe seus dados.
- `excluir()`: Remove uma pessoa da agenda, buscando-a pelo nome.
- `ordenar()`: Ordena a agenda em memória pelo nome das pessoas (utilizado no Exercício 2).
- `listar_por_cidade()`: Lista todas as pessoas que residem em uma determinada cidade (utilizado no Exercício 3).
- `cria_arq_invertido()`: Gera um arquivo de índice invertido com base na cidade dos contatos (utilizado no Exercício 3).

### 🔸 Funções Secundárias

Funções auxiliares utilizadas para melhorar a interação com o usuário e o processamento de dados.
`limpa_tela()`,`limpa_buffer()`,`entrada()`,`le_DN()`,`remove_final()`.

[⬆ Voltar ao topo](#topo)

## 📊 Exemplo de Execução
1. O usuário executa o programa de um dos exercícios.
2. O sistema solicita o nome do arquivo da agenda (ex: agenda.txt). Se o arquivo não existir, um novo é criado.
3. Um menu é exibido com as opções disponíveis (adicionar, buscar, excluir, listar, sair).
4. O usuário interage com o menu para manipular os dados da agenda.
5. Ao final da execução (ou a cada modificação), os dados são salvos no arquivo principal.
6. No Exercício 3, um arquivo de índice invertido (ex: agenda_invertido.txt) é gerado e atualizado com base nas cidades.

[⬆ Voltar ao topo](#topo)

## 📂 Como executar
Para compilar e executar os programas, você precisará de um compilador C++ (como o g++). Navegue até a pasta do projeto e execute os seguintes comandos no terminal:

EX1:
```bash
# Para criar/adicionar pessoas ao arquivo
g++ EX1/cria_arquivo.cpp -o cria_agenda && ./cria_agenda

# Para buscar pessoas no arquivo criado
g++ EX1/busca_arquivo.cpp -o busca_agenda && ./busca_agenda
```

EX2:
```bash
g++ EX2/exercicio2.cpp -o ex2 && ./ex2
```

EX3:
```bash
g++ EX3/exercicio3.cpp -o ex3 && ./ex3
```

[⬆ Voltar ao topo](#topo)

## 👨‍🏫 Envolvidos
"Envolvidos no trabalho exemplo"
* **Professor**: André Tavares da Silva
* **Estudantes**:
  * [Rian Valcanaia](https://github.com/RianValcanaia)

[⬆ Voltar ao topo](#topo)

## 📅 Curso

* **Universidade**: Universidade do Estado de Santa Catarina (UDESC)
* **Disciplina**: Estrutura de Dados 2
* **Semestre**: 4º

[⬆ Voltar ao topo](#topo)

## 📄 Código-fonte

🔗 [https://github.com/RianValcanaia/EDA2_TC1_Organizacao_de_Arquivos](https://github.com/RianValcanaia/EDA2_TC1_Organizacao_de_Arquivos)

[⬆ Voltar ao topo](#topo)

