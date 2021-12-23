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
void Ordenacao::quickSort_ordena(Registro *list, int i, int k, int *compara, int *movimenta)
{
    if (i < k)
    {
        int p = quickSort_particionaLista(list, i, k, compara, movimenta); //onde terminou a particao
        quickSort_ordena(list, i, p - 1, compara, movimenta);
        quickSort_ordena(list, p + 1, k, compara, movimenta);
    }
}

float Ordenacao::quickSort_time(Registro *list, int n, int *compara, int *movimenta)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    quickSort_ordena(list, 0, n - 1, compara, movimenta);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(end - start).count();
}

/*

===================FIM QUICKSORT========================

*/

/// ALGORITMO DE ORDENAÇÃO - HEAPSORT ///

void Ordenacao::heapify(Registro *list, int i, int tam, int *compara, int *movimenta)
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
            (*compara)++;

            if (list[filho].getVotes() > list[i].getVotes())
            {
                trocaNo(list, i, filho, compara, movimenta);
            }
            (*compara)++;
        }
        i = filho;
    }
}

void Ordenacao::build_heap(Registro *list, int tam, int *compara, int *movimenta)
{
    for (int i = tam / 2 - 1; i >= 0; i--)
    {
        heapify(list, i, tam, compara, movimenta);
    }
}

void Ordenacao::heapSort_ordena(Registro *list, int tam, int *compara, int *movimenta)
{
    build_heap(list, tam, compara, movimenta);
    while (tam > 0)
    {
        trocaNo(list, 0, tam - 1, compara, movimenta);
        heapify(list, 0, tam - 1, compara, movimenta);
        tam--;
    }
}

float Ordenacao::heapSort_time(Registro *list, int tam, int *compara, int *movimenta) //parece que nao esta ordenando
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    heapSort_ordena(list, tam, compara, movimenta);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(end - start).count();
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

void Ordenacao::combSort_ordena(Registro *list, int tam, int *compara, int *movimenta)
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
                std::cout<<"entrou";
                trocaNo(list, i, i + gap, compara, movimenta);
                switched = true;
            }
            (*compara)++;
            i++;
        }
    }
}

float Ordenacao::combSort_time(Registro *list, int tam, int *compara, int *movimenta)
{

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    combSort_ordena(list, tam, compara, movimenta);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    // for(int i =0; i<tam;i++){
    //     std::cout<<"\n"<<list[i].imprimeRegistros()<<std::endl;;
    // }
    return std::chrono::duration<float>(end - start).count();

}
/*
===================FIM COMBSORT =======================

*/