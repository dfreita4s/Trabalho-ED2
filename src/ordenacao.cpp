#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include "../inc/ordenacao.h"

Ordenacao::Ordenacao()
{
}
Ordenacao::~Ordenacao()
{
}

/// ALGORITMO DE ORDENAÇÃO - QUICK SORT ///

//realizar a ordenação desses registros, utilizando como chave de ordenação upvotes. Durante a ordenação, deverão ser computados o
//total de comparações de chaves e o total de movimentações de chaves. Além disso, o tempo de execução do algoritmo deverá ser medido.
//Para gerar as estatísticas de desempenho, você deverá executar os passos acima para M diferentes conjuntos de N registros aleatórios.
//Minimamente, utilize M=3. Ao final, compute as médias de cada uma das métricas (comparações, movimentações e tempo)
void Ordenacao::trocaNo(Registro *troca, int a, int b /*, int *movimentacoes*/)
{
    Registro aux;
    aux = troca[a];
    troca[a] = troca[b];
    troca[b] = aux;
    // (* movimentacoes)++;
}

Registro Ordenacao::pivoMediano(Registro *l, int inicio, int fim)
{
    int media = (inicio + fim) / 2;

    if (l[inicio].getVotes() > l[fim].getVotes())
        trocaNo(l, inicio, fim);
    if (l[media].getVotes() > l[fim].getVotes())
        trocaNo(l, media, fim);
    if (l[inicio].getVotes() > l[media].getVotes())
        trocaNo(l, inicio, media);
    trocaNo(l, media, fim);
    return l[fim];
}

int Ordenacao::quickSort_particionaLista(Registro *list, int inicio, int fim)
{

    Registro pivo = pivoMediano(list, inicio, fim);
    int j = fim - 1;
    int i = inicio;

    while (true)
    {
        while (i < fim && list[i].getVotes() < pivo.getVotes())
            i = i + 1;
        while (j >= inicio && list[j].getVotes() > pivo.getVotes())
            j = j - 1;
        if (i < j)
        {
            trocaNo(list, i, j);
            i = i + 1;
            j = j - 1;
        }
        else
            break;
    }
    trocaNo(list, i, fim);
    return i;
}
void Ordenacao::quickSort_ordena(Registro *list, int i, int k)
{
    if (i < k)
    {
        int p = quickSort_particionaLista(list, i, k); //onde terminou a particao
        quickSort_ordena(list, i, p - 1);
        quickSort_ordena(list, p + 1, k);
    }
}

void Ordenacao::quickSort_time(Registro *list, int n)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    quickSort_ordena(list, 0, n - 1);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "\nTempo gasto na ordenação: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " segundos" << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << list[i].imprimeRegistros();
}

/*

===================FIM QUICKSORT========================

*/

/// ALGORITMO DE ORDENAÇÃO - HEAPSORT ///

void Ordenacao::heapify(Registro *list, int i, int tam)
{
    while (i < tam)
    {
        int filho = 2 * i + 1;
        if (filho < tam)
        {
            if (filho + 1 < tam && list[filho + 1].getVotes() > list[filho].getVotes())
            {
                filho++;
            }

            if (list[filho].getVotes() > list[i].getVotes())
            {
                trocaNo(list, i, filho);
            }
        }
        i = filho;
    }
}

void Ordenacao::build_heap(Registro *list, int tam)
{
    for (int i = tam / 2 - 1; i >= 0; i--)
    {
        heapify(list, i, tam);
    }
}

void Ordenacao::heapSort_ordena(Registro *list, int tam)
{
    build_heap(list, tam);
    while (tam > 0)
    {
        trocaNo(list, 0, tam - 1);
        heapify(list, 0, tam - 1);
        tam--;
    }
}

void Ordenacao::heapSort_time(Registro *list, int tam) //parece que nao esta ordenando
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    heapSort_ordena(list, tam);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempoFinal = (end - start);
    std::cout << "/nTempo gasto na ordenação:  segundos" << std::endl;
    for (int i = 0; i < tam; i++)
        std::cout << list[i].imprimeRegistros();
    // std::fstream saidaTxt;
    // saidaTxt.open("./data/saidaTxt.txt", std::ios_base::out | std::ios_base::app);
    // if (saidaTxt.is_open())
    // {

    //     std::string linha = "";

    //     // linha = "Heapsort\nTempo gasto: "+tempoFinal+" segundos\n";
    //     saidaTxt.write(linha.c_str(), sizeof(char) * linha.size());

    //     std::cout << "O arquivo de texto foi criado!" << std::endl;
    // }
    // saidaTxt.close();
}

/*
====================FIM HEAPSORT ============

*/

/// ALGORITMO DE ORDENAÇÃO - COMB SORT ///

int Ordenacao::find_next(int gap)
{
    gap = (gap * 10) / 13;

    if (gap < 1)
        return 1;
    return gap;
}

void Ordenacao::combSort_ordena(Registro *list, int tam)
{
    int gap = tam;
    bool switched = true;

    while (gap != 1 || switched == true)
    {
        gap = find_next(gap);

        switched = false;

        int i = 0;
        while (i < tam - gap)
        {
            if (list[i].getVotes() > list[i + gap].getVotes())
            {
                trocaNo(list, i, i + gap);
                switched = true;
            }
            i++;
        }
    }
}

void Ordenacao::combSort_time(Registro *list, int tam)
{

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    combSort_ordena(list, tam);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "/nTempo gasto na ordenação: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " segundos" << std::endl;
    std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
    for (int i = 0; i < tam; i++)
        std::cout << list[i].imprimeRegistros();
}
/*
===================FIM COMBSORT =======================

*/