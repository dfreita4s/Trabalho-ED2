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
    void inserirNo(NoVP *, int *);
    void inserir(std::string, int, int *);
    void arrumaArvore(NoVP *);
    Color getColor(NoVP *);
    bool arvoreVazia();
    
    void printHelper(NoVP*, std::string, bool);
    void prettyPrint();
    void imprimirArvore();
    void imprimirNo(NoVP* no, bool);
    void buscaNo(arvoreVP *, std::string, int *);

    //novas funções recursivas para a árvore vermelho e preta
    void insere_caso1(NoVP *);
    void insere_caso2(NoVP *);
    void insere_caso3(NoVP *);
    void insere_caso4(NoVP *);
    void novoRotacionaDir(NoVP *);
    void novoRotacionaEsq(NoVP *);
    void novoRotDuplaEsq(NoVP *);
    void novoRotDuplaDir(NoVP *);
};

#endif