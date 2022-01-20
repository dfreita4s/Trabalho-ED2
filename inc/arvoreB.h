#include "NoB.h"

class arvoreB
{

private:
    NoB* raiz; // Raíz da Árvore B
    int t; // Grau mínimo

public:
    arvoreB(int);
    ~arvoreB();

    void inserir(std::string, int);
    void inserirChave(T*, NoB*);
    void exibeArvore();
    void imprimeArvB();

    void split(NoB*, int, NoB*, T*);
    void procurar(NoB*, T*);
};
