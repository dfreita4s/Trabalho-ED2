#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"

class vermelhaPreta
{
private:
    NoVP* raiz;
    NoVP* nil;

public:
    vermelhaPreta(/* args */);
    ~vermelhaPreta();

    //Rotações
    void rotacaoEsquerda(NoVP *);
    void rotacaoDireita(NoVP *);
    void rotacaoDuplaEsquerda(NoVP *);
    void rotacaoDuplaDireita(NoVP *);
    void inserirNo(NoVP *);
    void inserir(std::string, int);
    void arrumaArvore(NoVP *);
    Color getColor(NoVP *);
    bool arvoreVazia();
    
    void printHelper(NoVP*, std::string, bool);
    void prettyPrint();
    void imprimirArvore();
    void imprimirNo(NoVP* no, bool);

};

#endif