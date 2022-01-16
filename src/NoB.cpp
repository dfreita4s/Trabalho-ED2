#include "../inc/NoB.h"

NoB::NoB(int m)
{
    T* chaves = new T[m];
    NoB** filhos = new NoB*[m];
    this->n = 0;
    this->folha = true;
}

NoB::~NoB()
{
    delete [] chaves;
    delete [] filhos;
}

int NoB::getNumChaves()
{
    return this->n;
}

std::string NoB::getID(T* chave, int pos)
{
    return chave[pos].id;
}

int NoB::getPosicao(T* chave, int pos)
{
    return chave[pos].posicao;
}

bool NoB::deuOverflow()
{
    return this->n == 0;
}

bool NoB::eExterna()
{
    if(this != nullptr)
        return false;
    return this->folha;
}

void NoB::insereChave(T* chave)
{
    if(this->n == 0) // Nenhuma chave
    {
        this->chaves[0] = chave[0];
        this->n++;
        return;
    }
    

    int i;
    for(i=1; chave->id > this->chaves[i].id; i++ )
        continue;

    chaves[i].id = chave->id;
    chaves[i].posicao = chave->posicao;    

}