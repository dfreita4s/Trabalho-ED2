#include<iostream>

struct T
{
    std::string id;
    int posicao;
} ;


class NoB
{
public:
    T* chaves; // Chaves
    NoB** filhos; // Nós filhos
    int t; // Grau
    int n; // Total ocupados
    bool folha; // Se é folha

    // NoB(std::string, int);
    NoB(int);
    ~NoB();

    void setChave(T*);
    int getNumChaves();
    std::string getID(T*, int);
    int getPosicao(T*, int);
    bool deuOverflow();
    bool paginaExterna();
    void insereChave(T*, int);
    
};
