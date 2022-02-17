//#ifndef ARVOREVP_H
#define ARVOREVP_H

#include "NoVP.h"

class arvoreVP
{
private:
    NoVP* raiz;
    NoVP* nil;
    int rot;

public:
    arvoreVP(/* args */);
    ~arvoreVP();

    void auxDeleteNos(NoVP*);
    //Rotações
    void inserirNo(NoVP *, int *);
    void inserir(std::string, int, int *);
    Color getColor(NoVP *);
    bool arvoreVazia();
    
    void printHelper(NoVP*, std::string, bool);
    void prettyPrint();
    void geraTxt();
    void imprimeRelatorio(arvoreVP *, int, int, float);
    void imprimirArvore();
    void imprimirNo(NoVP* no, bool);
    void buscaNo(arvoreVP *, std::string, int *, int);
    void printaArvore(NoVP *, std::string , bool);

    //novas funções recursivas para a árvore vermelho e preta
    void insere_caso1(NoVP *);
    void insere_caso2(NoVP *);
    void insere_caso3(NoVP *);
    void insere_caso4(NoVP *);
    void novoRotacionaDir(NoVP *);
    void novoRotacionaEsq(NoVP *);
    void novoRotDuplaEsq(NoVP *);
    void novoRotDuplaDir(NoVP *);
    int contaRotacoes();
};

//#endif