#include <iostream>
#include "registro.h"

class Ordenacao
{
public:
    Ordenacao();
    ~Ordenacao();
    void trocaNo(Registro *, int, int, int *comparacoes, int *movimentacoes);
    // QUICK SORT

    Registro pivoMediano(Registro *l, int inicio, int fim, int *comparacoes, int *movimentacoes);
    int quickSort_particionaLista(Registro *list, int i, int j, int *comparacoes, int *movimentacoes);
    void quickSort_ordena(Registro *list, int i, int k, int *comparacoes, int *movimentacoes);
    float quickSort_time(Registro *list, int n, int *comparacoes, int *movimentacoes);

    //HEAP SORT

    void heapify(Registro *list, int i, int tam, int *, int *);
    void build_heap(Registro *list, int tam, int *, int *);
    void heapSort_ordena(Registro *list, int tam, int *, int *);
    float heapSort_time(Registro *list, int tam, int *, int *);

    //COMB SORT

    int find_next(int gap);
    void combSort_ordena(Registro *list, int tam, int *, int *);
    float combSort_time(Registro *list, int tam, int *, int *);

private:
    // Registro *registro;
};