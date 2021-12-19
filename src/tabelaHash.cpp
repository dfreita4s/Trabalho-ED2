#include "../inc/tabelaHash.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <chrono>


tabelaHash::tabelaHash(int chave){
    this->chave = chave;
    this->cont = 0;
}

tabelaHash::tabelaHash(){
    this->chave = 0;
    this->cont = 0;
}


/*

enum FuncaoHash
{
    DIVISAO,
    ENLACAMENTO_SEPARADO,
    ENLACAMENTO_LIMITE,
    MULTIPLICACAO,
    MEIO_QUADRADO,
    EXTRACAO,
    TRANSFORMACAO_BASE,
    ANALISE_DIGITOS,
    HASHING_UNIVERSAL
};
*/

/*
enum TratamentoColisao
{
    SONDAGEM_LINEAR,
    SONDAGEM_QUADRATICA,
    DUPLO_HASHING,
    ENCADEAMENTO_SEPARADO,
    ENCADEAMENTO_COALESCIDO,
    ENDERECAMENTO_BALDES
};
*/

int tabelaHash::consultaContador(){
        return this->cont;
}

int tabelaHash::consultaChave(){
    return this->chave;
}

void tabelaHash::insereChave(int chave){
    this->chave = chave;
    somaContador();
}


void tabelaHash::somaContador(){
    this->cont = cont + 1;
}

int tabelaHash::funcaoHash(int versao, int tam) // função hash transforma valores decimais para octais (transformação de base) e depois aplica o método da divisão
{
    std::string resultado;
    while(versao >= 1)
    {
        if(versao % 8 == 0)
        {
            resultado = "0" + resultado;
        }
        else if (versao % 8 == 7)
        {
            resultado = "7" + resultado;
        }
        else if (versao % 8 == 6)
        {
            resultado = "6" + resultado;
        }
        else if (versao % 8 == 5)
        {
            resultado = "5" + resultado;
        }
        else if (versao % 8 == 4)
        {
            resultado = "4" + resultado;
        }
        else if (versao % 8 == 3)
        {
            resultado = "3" + resultado;
        }
        else if (versao % 8 == 2)
        {
            resultado = "2" + resultado;
        }
        else if (versao % 8 == 1)
        {
            resultado = "1" + resultado;
        }
        versao = versao/8;
    }
    int versaoConvertida = stoi(resultado);
    return (versaoConvertida % tam);
}

int tabelaHash::trataColisao(int chave, int tam, int i){
    int m1 = 7;
    int m2 = 5;
    int saida;
    saida = ((chave % 7) + i*(chave % 5)) % 7;
    return saida;
}

void tabelaHash::imprimeTabela(int *tabela, int m)
{
    for(int i = 0; i < m; i++)
        cout << tabela[i] << ", ";
    cout << endl;
}

int tabelaHash::totalColisoes(int *tabela, int m)
{
    int cont = 0;
    for(int i = 0; i < m; i++)
    {
        if(tabela[i] > 1)
            cont += tabela[i]-1;
    }
    return cont;
}

