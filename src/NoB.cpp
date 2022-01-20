#include "../inc/NoB.h"

NoB::NoB(int m)
{
    chaves = new T[m-1];
    filhos = new NoB*[m];
    t = m;
    n = 0;
    folha = true;

    for(int i=0; i<m; i++)
        filhos[i] = nullptr;
}

NoB::~NoB()
{
    delete [] chaves;
    delete [] filhos;
}

int NoB::getNumChaves()
{
    return n;
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
    return n == t;
}

bool NoB::paginaExterna()
{
    return folha;
}

void NoB::insereChave(T* chave, int i)
{
    // for(int j=i+1; j<(t-1); j++)
    for(int j=(t-2); j>=i; j--)
    {
        // Desloca chaves
        chaves[j+1].id = chaves[j].id;
        chaves[j+1].posicao = chaves[j].posicao;
        // Desloca filhos
        filhos[j+1] = filhos[j];
    }

    // chaves[i+1].id = chaves[i].id;
    // chaves[i+1].posicao = chaves[i].posicao;
    // Insere a chave
    chaves[i].id = chave->id;
    chaves[i].posicao = chave->posicao;
    n++; // Incrementa total de chaves
}