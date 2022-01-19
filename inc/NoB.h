#include<iostream>

struct T
{
    std::string id;
    int posicao;
} ;


class NoB
{
private:

    T* chaves; // Chaves
    NoB** filhos; // Nós filhos
    int n; // Total ocupados
    bool folha; // Se é folha
    
public:
    
    // NoB(std::string, int);
    NoB(int, bool);
    ~NoB();

    void setChave(T*);
    int getNumChaves();
    std::string getID(T*, int);
    int getPosicao(T*, int);
    bool deuOverflow();
    bool eExterna();
    void insereChave(T*);
    
};