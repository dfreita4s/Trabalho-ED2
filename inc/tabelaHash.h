#include <iostream>
#include <list>
#include <cstring>
//#include "registro.h"

using namespace std;

class tabelaHash{

    private:
        int cont;
        int chave;
        std::string chaveOrig;

    public:

        tabelaHash(int);
        tabelaHash();
        //~tabelaHash();

        // todos os n passados por paramêtros são a chave principal, no caso a versão do review
        int consultaContador();
        int consultaChave();
        std::string consultaChaveOrig();
        void insereChave(int);
        void insereContador(int);
        void insereChaveOrig(std::string);
        void somaContador();
        int trataColisao(int, int, int);
        int funcaoHash (int, int);
        void imprimeTabela(tabelaHash*, int);
        int totalColisoes(int*,int);
        //void criaTabelaHash(Registro *, int);
        //int retiraPontos(std::string);
        void trocaReviews(tabelaHash *, int, int, int *, int *);
        tabelaHash pivoMediano(tabelaHash *, int, int, int *, int *);
        int quick_particionaTabela (tabelaHash *, int, int, int *, int *);
        void quickSort_ordena(tabelaHash *, int, int, int *, int *);
        float quickSort_time(tabelaHash *, int, int *, int *);

};