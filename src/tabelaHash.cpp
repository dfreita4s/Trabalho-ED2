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

void tabelaHash::trocaReviews(tabelaHash *troca, int a, int b, int *compara, int *movimenta)
{
    tabelaHash aux;
    aux.insereChave(troca[a].consultaChave());
    aux.insereChaveOrig(troca[a].consultaChaveOrig());
    aux.insereContador(troca[a].consultaContador());
    troca[a].insereChave(troca[b].consultaChave());
    troca[a].insereChaveOrig(troca[b].consultaChaveOrig());
    troca[a].insereContador(troca[b].consultaContador());    
    troca[b].insereChave(aux.consultaChave());
    troca[b].insereChaveOrig(aux.consultaChaveOrig());
    troca[b].insereContador(aux.consultaContador());
    (*movimenta)++;  
}

tabelaHash tabelaHash::pivoMediano(tabelaHash *tabela, int inicio, int fim, int *compara, int *movimenta)
{
    int media = (inicio + fim) / 2;

    if(tabela[inicio].consultaContador() > tabela[fim].consultaContador())
    {
        trocaReviews(tabela, inicio, fim, compara, movimenta);
    }
    if (tabela[media].consultaContador() > tabela[fim].consultaContador())
    {
        trocaReviews(tabela, media, fim, compara, movimenta);
    }
    if (tabela[inicio].consultaContador() > tabela[media].consultaContador())
    {
        trocaReviews(tabela, inicio, media, compara, movimenta);
    }
    trocaReviews(tabela, media, fim, compara, movimenta);
    return tabela[fim];
}

int tabelaHash::quick_particionaTabela (tabelaHash *tabela, int inicio, int fim, int *compara, int *movimenta)
{
    tabelaHash pivo = pivoMediano(tabela, inicio, fim, compara, movimenta);
    int j = fim - 1;
    int i = inicio;

    while (true)
    {
        while (i < fim && tabela[i].consultaContador() < pivo.consultaContador())
        {
            i = i + 1;
            (*compara)++;
        }
        while (j >= inicio && tabela[j].consultaContador() > pivo.consultaContador())
        {
            j = j - 1;
            (*compara)++;
        }
        if(i < j)
        {
            trocaReviews(tabela, i, j, compara, movimenta);
            i = i + 1;
            j = j - 1;
        }
        else
        break;
    }
    trocaReviews(tabela, i, fim, compara, movimenta);
    return i;
}

void tabelaHash::quickSort_ordena(tabelaHash *tabela, int i, int k, int *compara, int *movimenta)
{
    if (i < k)
    {
        int p = quick_particionaTabela(tabela, i, k, compara, movimenta);
        quickSort_ordena(tabela, i, p - 1, compara, movimenta);
        quickSort_ordena(tabela, p + 1, k, compara, movimenta);
    }
}

float tabelaHash::quickSort_time (tabelaHash *tabela, int n, int *compara, int *movimenta)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    quickSort_ordena(tabela, 0, n - 1, compara, movimenta);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(end - start).count();
}


/*

float Ordenacao::quickSort_time(Registro *list, int n, int *compara, int *movimenta)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    quickSort_ordena(list, 0, n - 1, compara, movimenta);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(end - start).count();
}

void Ordenacao::quickSort_ordena(Registro *list, int i, int k, int *compara, int *movimenta)
{
    if (i < k)
    {
        int p = quickSort_particionaLista(list, i, k, compara, movimenta); //onde terminou a particao
        quickSort_ordena(list, i, p - 1, compara, movimenta);
        quickSort_ordena(list, p + 1, k, compara, movimenta);
    }
}

int Ordenacao::quickSort_particionaLista(Registro *list, int inicio, int fim, int *compara, int *movimenta)
{

    Registro pivo = pivoMediano(list, inicio, fim, compara, movimenta);
    int j = fim - 1;
    int i = inicio;

    while (true)
    {
        while (i < fim && list[i].getVotes() < pivo.getVotes())
        {
            i = i + 1;
            (*compara)++;
        }
        while (j >= inicio && list[j].getVotes() > pivo.getVotes())
        {
            j = j - 1;
            (*compara)++;
        }
        if (i < j)
        {
            trocaNo(list, i, j, compara, movimenta);
            i = i + 1;
            j = j - 1;
        }
        else
            break;
    }
    trocaNo(list, i, fim, compara, movimenta);
    return i;
}

void Ordenacao::trocaNo(Registro *troca, int a, int b, int *compara, int *movimenta)
{
    Registro aux;
    aux = troca[a];
    troca[a] = troca[b];
    troca[b] = aux;
    (*movimenta)++;
}

Registro Ordenacao::pivoMediano(Registro *l, int inicio, int fim, int *compara, int *movimenta)
{
    int media = (inicio + fim) / 2;

    if (l[inicio].getVotes() > l[fim].getVotes())
        trocaNo(l, inicio, fim, compara, movimenta);
    if (l[media].getVotes() > l[fim].getVotes())
        trocaNo(l, media, fim, compara, movimenta);
    if (l[inicio].getVotes() > l[media].getVotes())
        trocaNo(l, inicio, media, compara, movimenta);
    trocaNo(l, media, fim, compara, movimenta);
    return l[fim];
}

float Ordenacao::quickSort_time(Registro *list, int n, int *compara, int *movimenta)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    quickSort_ordena(list, 0, n - 1, compara, movimenta);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(end - start).count();
}
*/
