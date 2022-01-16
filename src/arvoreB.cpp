#include "../inc/arvoreB.h"

arvoreB::arvoreB(int m)
{
    this->raiz = nullptr;
    this->nChaves = m;
}

arvoreB::~arvoreB()
{
}

void arvoreB::inserir(std::string ID, int pos)
{
    T* novaChave = new T;
    novaChave->id = ID;
    novaChave->posicao = pos;

    inserirChave(novaChave, raiz);
}

void arvoreB::inserirChave(T* chave, NoB* pagina)
{

    if ( this->raiz == nullptr) {
        NoB* novoNoB = new NoB(this->nChaves);
        raiz = novoNoB;
        novoNoB->insereChave(chave);
        return;
    }

    raiz->insereChave(chave);
    if(pagina->getNumChaves() == this->nChaves) // Overflow
        split(pagina);

}

void arvoreB::exibeArvore()
{

}