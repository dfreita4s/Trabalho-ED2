#include "../inc/tabelaHash.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>
//#include <vector>

tabelaHash::tabelaHash(int chave){
    this->chave = chave;
    this->cont = 0;
}

tabelaHash::tabelaHash(){
    this->chave = 0;
    this->cont = 0;
    this->chaveOrig = "0";
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

std::string tabelaHash::consultaChaveOrig(){
    return this->chaveOrig;
}

void tabelaHash::insereChave(int chave){
    this->chave = chave;
    somaContador();
}

void tabelaHash::insereContador(int contador){
    this->cont = contador;
}

void tabelaHash::insereChaveOrig(std::string chave){
    this->chaveOrig = chave;
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
    int m1 = 27;
    int m2 = 26;
    int saida;
    saida = ((chave % m1) + i*((chave % m2)) + 1);
    return saida;
}

void tabelaHash::imprimeTabela(tabelaHash *tabela, int n)
{
    for (int i = 0; i < n; i++){
    cout << "Versao" << " " << "," << " " << "Numero de reviews da mesma versao" << " " << endl;
    cout << tabela[i].consultaChaveOrig() << ", " << tabela[i].consultaContador();
    cout << endl;
    }
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

