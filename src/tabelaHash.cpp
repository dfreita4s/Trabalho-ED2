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

int tabelaHash::funcaoHash(int versao, int tam){
    return versao % tam;
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