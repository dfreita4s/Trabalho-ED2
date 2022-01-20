#include "../inc/arvoreB.h"

arvoreB::arvoreB(int m)
{
    raiz = nullptr;
    t = m;
}

arvoreB::~arvoreB()
{
}

void arvoreB::split(NoB* x, int i, NoB* y, T* chave)
{
    NoB* z = new NoB(t);
    z->folha = y->folha;

    int med = (t/2);

    z->n = t-2;

    for(int j=0; (j+med)<(t-1); j++) {
        z->chaves[j] = y->chaves[j+med];
        // y->chaves[j+med].id = "";
        // y->chaves[j+med].posicao = 0;
    }

    if(!(y->folha))
        for(int j=0; j<t; j++) {
            z->filhos[j] = y->filhos[j+med];
            // y->filhos[j+med] = nullptr;
        }

    y->n = med-1;

    for(int j=(x->n); j>=(i+1) ; j--)
        x->filhos[j+1] = x->filhos[j];

    x->filhos[i+1] = z;

    for(int j=x->n-1; j>=i; j--)
        x->chaves[j+1] = x->chaves[j];

    // x->chaves[i] = y->chaves[med-1];
    if(chave->id < y->chaves[med].id)
        x->chaves[i] = y->chaves[med-1];
    else
        x->chaves[i] = y->chaves[med];

    x->n = x->n + 1;

    for(int j=med; j<(t-1); j++)
    {
        y->chaves[j].id = "";
        y->chaves[j].posicao = 0;
    }

}

void arvoreB::inserir(std::string ID, int pos)
{
    T* novaChave = new T;
    novaChave->id = ID;
    novaChave->posicao = pos;

    if ( raiz == nullptr) {
        NoB* novoNoB = new NoB(t);
        raiz = novoNoB;
        novoNoB->chaves[0] = novaChave[0];
        novoNoB->n++;
        return;
    }

    NoB *r = raiz;
    if (r->n == (t-1)) {
        NoB* s = new NoB(t);
        raiz = s;
        s->folha = false;
        s->n = 0;
        s->filhos[0] = r;

        split(s,0,r,novaChave);

        inserirChave(novaChave, s);
    }
    else
        inserirChave(novaChave, r);
}

void arvoreB::inserirChave(T* chave, NoB* x)
{
    int i = x->n-1;
    if(x->folha) {
        while(i>=0 && (chave->id < x->chaves[i].id))
        {
            x->chaves[i+1] = x->chaves[i];
            i--;
        }
        x->chaves[i+1] = chave[0];
        x->n = x->n + 1;
    } else {
        while((i>=0) && (chave->id < x->chaves[i].id))
            i--;
        
        // i++;

        if(x->filhos[i+1]->n == (t-1))
        {
            split(x, i+1, x->filhos[i+1], chave);
            if(chave->id > x->chaves[i+1].id)
                i++;
        }
        
        inserirChave(chave, x->filhos[i+1]);
    }
}

void arvoreB::procurar(NoB* x, T* chave)
{
    int i = 0;
    while(i<=x->n && chave->id >= x->chaves->id);
}