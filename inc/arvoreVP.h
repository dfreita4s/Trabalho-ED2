#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"

class arvoreVP
{
private:
    NoVP* raiz;
    NoVP* nil;

public:
    arvoreVP(/* args */);
    ~arvoreVP();

    void auxDeleteNos(NoVP*);
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
    void buscaNo(arvoreVP *, std::string);

};

#endif