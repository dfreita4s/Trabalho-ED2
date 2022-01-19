#include "../inc/ArvoreB.h"


ArvoreB::ArvoreB(int m)
{
    this->raiz = nullptr;
    this->nChaves = m -1;
}

ArvoreB::~ArvoreB()
{
}

void ArvoreB::inserir(std::string ID, int pos, int *comparacoes)
{
    T* novaChave = new T;
    novaChave->id = ID;
    novaChave->posicao = pos;

    inserirChave(novaChave, raiz, comparacoes);
}

void ArvoreB::inserirChave(T* chave, NoB* pagina, int *comparacoes)
{

    if ( this->raiz == nullptr) {
        NoB* novoNoB = new NoB(this->nChaves, true);
        raiz = novoNoB;
        novoNoB->insereChave(chave);
        return;
    }

    raiz->insereChave(chave);
    if(pagina->getNumChaves() == this->nChaves) // Overflow
        split(pagina);

}

void ArvoreB::exibeArvore()
{

}

