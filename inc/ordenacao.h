#include <iostream>
#include "../src/registro.cpp"
class Ordenacao{
    public:

    void trocaNo(Registro r1, Registro r2);
    // QUICK SORT 

    Registro pivoMediano(Registro *l, int inicio, int fim);
    int quickSort_particionaLista(Registro *list, int i, int j);
    void quickSort_ordena(Registro *list, int i, int k);
    void quickSort_time(Registro *list, int n);

    //HEAP SORT

    void heapify(Registro *list, int i, int tam);
    void build_heap(Registro *list, int tam);
    void heapSort_ordena(Registro *list, int tam);
    void heapSort_time(Registro *list, int tam);


    //COMB SORT

    int find_next(int gap);
    void combSort_ordena(Registro *list, int tam);
    void combSort_time(Registro *list, int tam);


    private:
        // Registro *registro;

};