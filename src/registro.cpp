#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "../inc/registro.h"

// Registro::Registro(const std::string &caminhoArquivo, int N)
// {
//     this->registros = new std::string[N]; //chama o array para salvar na memoria principal os N registros
//     setN(N);
//     setRegistro(importaRegistros(N));
// }

Registro::Registro()
{
    //contrutor
}

Registro::~Registro()
{
    //Destructor
    delete registros;
}

std::string Registro::imprimeRegistros()
{
    return ("ID: " + getID() + "\nMensagem: " + getText() + "\nVotos: " + std::to_string(getVotes()) + "\nVersão: " + getVersion() + "\nData/Hora: " + getDate());
    // std::cout << "ID: " << getID() << std::endl;
    // std::cout << "Mensagem: \"" << getText() << "\"" <<std::endl;
    // std::cout << "Votos /\\: " << getVotes() << std::endl;
    // std::cout << "Versão do Aplicativo: " << getVersion() << std::endl;
    // std::cout << "Data/Hora: " << getDate() << std::endl;
    // std::cout << std::endl;
}

void Registro::setID(std::string id)
{
    this->review_id = id;
}
void Registro::setText(std::string text)
{
    this->review_text = text;
}
void Registro::setVersion(std::string version)
{
    this->app_version = version;
}
void Registro::setDate(std::string date)
{
    this->posted_date = date;
}
void Registro::setVotes(int votes)
{
    this->upvotes = votes;
}
std::string Registro::getID()
{
    return this->review_id;
}
std::string Registro::getText()
{
    return this->review_text;
}
std::string Registro::getVersion()
{
    return this->app_version;
}
std::string Registro::getDate()
{
    return this->posted_date;
}
int Registro::getVotes()
{
    return this->upvotes;
}

void Registro::setN(int N)
{
    this->N = N;
}

int Registro::getN()
{
    return this->N;
}

std::string *Registro::getRegistro()
{
    return this->registros;
}

void Registro::setRegistro(std::string *regist)
{
    this->registros = regist;
}

// std::string *Registro::importaRegistros(int N) //retorna N registros aleatorios do arquivo binario
// {
//     std::string *aux = new std::string[N];
//     for (int i = 0; i < N; i++)
//         aux[i] = leBinario(rand() % 3646475 + 0);

//     return aux;
// }

void Registro::ordenaRegistros()
{
    quickSort_time(getRegistro(), getN());
}

/// ALGORITMO DE ORDENAÇÃO - QUICK SORT ///


void Registro::trocaNo(std::string &r1, std::string &r2)
{
    std::string aux = r1;
    r1 = r2;
    r2 = aux;
}

std::string Registro::pivoMediano(std::string *l, int inicio, int fim)
{
    int media = (inicio + fim) / 2;
    if (l[inicio] > l[fim])
        trocaNo(l[inicio], l[fim]);
    if (l[media] > l[fim])
        trocaNo(l[media], l[fim]);
    if (l[inicio] > l[media])
        trocaNo(l[inicio], l[media]);
    trocaNo(l[media], l[fim]);
    return l[fim];
}

int Registro::quickSort_particionaLista(std::string *list, int i, int j)
{

    int fim = j - 1;
    int init = i;
    std::string pivo = pivoMediano(list, i, j);

    while (true)
    {
        while (i < j && list[i] < pivo)
        {
            i = i + 1;
        }
        while (j >= init && list[j] > pivo)
        {
            j = j - 1;
        }
        if (i <= j)
        {
            trocaNo(list[i], list[j]);
            i = i + 1;
            j = j - 1;
        }
        else
            break;
        trocaNo(list[i], list[j]);
        return i;
    }
}
void Registro::quickSort_ordena(std::string *list, int i, int k)
{
    if (i - k > 0)
    {
        int p = quickSort_particionaLista(list, i, k);
        quickSort_ordena(list, i, p);
        quickSort_ordena(list, p + 1, k);
    }
}

void Registro::quickSort_time(std::string *list, int n)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    quickSort_ordena(list, 0, n - 1);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "/nTempo gasto na ordenação: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " segundos" << std::endl;
}