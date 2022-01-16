#include "NoB.h"

class arvoreB
{
private:
    NoB* raiz;
    int nChaves;
public:
    arvoreB(int);
    ~arvoreB();

    void inserir(std::string, int);
    void inserirChave(T*, NoB*);
    void exibeArvore();
    void split(NoB*);
};
