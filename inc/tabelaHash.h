#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class tabelaHash{

    private:
        int cont;
        int chave;

    public:

        tabelaHash(int);
        tabelaHash();
        //~tabelaHash();

        // todos os n passados por paramêtros são a chave principal, no caso a versão do review
        int consultaContador();
        int consultaChave();
        void insereChave(int);
        void somaContador();
        int trataColisao(int, int, int);
        int funcaoHash (int, int);
        void imprimeTabela(int*,int);
        int totalColisoes(int*,int);
};