#include "NoB.h"

class ArvoreB
{
private:
    NoB* raiz;
    int nChaves;
public:
    ArvoreB(int);
    ~ArvoreB();

    void inserir(std::string, int, int *);
    void inserirChave(T*, NoB*, int *);
    void exibeArvore();
    void split(NoB*);
};