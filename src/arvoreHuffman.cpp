#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include "../inc/arvoreHuffman.h"


arvoreHuffman::arvoreHuffman()
{
    escape = new NoHuffman();
    raiz = escape;
    listaDupEnc biblioteca;
}

arvoreHuffman::~arvoreHuffman()
{
    // destrutor
}

void arvoreHuffman::recebeReview(std::string reviewID)
{
    if (reviewID != "")
    {
        int tam = reviewID.length();
        char review [tam + 1];
        strcpy(review, reviewID.c_str());
        for (int i = 0; i < tam; i++)
        { 
            constroiArvore(review[i]);
            // verificaPropriedade(raiz);
        }
    }
    else
    {
        std::cout << "Foi encontrado um review sem comentario" << std::endl;
    }
}


void arvoreHuffman::constroiArvore(char review)
{
    //se a árvore possui apenas o no de escape, ainda não tem qualquer símbolo salvo
    if (raiz == escape)
    {
        //cria e atualiza ponteiros
        NoHuffman *p = new NoHuffman();
        NoHuffman *i = new NoHuffman();

        //atualiza pai
        p->setNoDir(i);
        p->setNoEsq(escape);
        p->setNoPai(nullptr);
        raiz = p;

        p->setSimbolo('*');
        p->setFrequencia();
        p->setTipoNo("raiz");
        p->setCodificacao("");

        //atualiza no de escape
        escape->setNoPai(p);
        escape->setNoEsq(nullptr);
        escape->setNoDir(nullptr);
        escape->setCodificacao("0");

        //atualiza filho com símbolo
        i->setNoPai(p);
        i->setNoDir(nullptr);
        i->setNoEsq(nullptr);

        i->setSimbolo(review);
        i->setFrequencia();
        i->setTipoNo("lider");
        i->setCodificacao("1");

        addBiblioteca(p);
        addBiblioteca(i);
    }
    else
    {
        if (verificaSimbolo(review) == false)
        {
            NoHuffman *p = nullptr;
            p = escape->getNoPai();

            NoHuffman *np = new NoHuffman();
            NoHuffman *i = new NoHuffman();

            // atualiza o antigo no pai (p)
            p->setNoEsq(np);

            // atualiza o no de escape
            escape->setNoPai(np);
            escape->setCodificacao("0");

            //atualiza o novo no pai (np)
            np->setNoPai(p);
            np->setNoDir(i);
            np->setNoEsq(escape);

            np->setSimbolo('*');
            np->setFrequencia();
            np->setTipoNo("n_lider");
            np->setCodificacao("0");

            // atualiza o no com o novo símbolo
            i->setNoPai(np);
            i->setNoDir(nullptr);
            i->setNoEsq(nullptr);

            i->setSimbolo(review);
            i->setFrequencia();
            i->setTipoNo("lider");
            i->setCodificacao("1");

            addBiblioteca(np);
            addBiblioteca(i);
        }
        else
        {
            biblioteca.setAtual(biblioteca.getInicio()->getProx());
            while ((biblioteca.getAtual()->getProx() != nullptr) && (biblioteca.getAtual()->getNoH()->getSimbolo() != review))
            {
                biblioteca.setAtual(biblioteca.getAtual()->getProx());
            }
            if (biblioteca.getAtual()->getNoH()->getSimbolo() == review)
            {
                biblioteca.getAtual()->getNoH()->setFrequencia();
                verificaRotRep(biblioteca.getAtual());
            }
        }
    }
}

/*
NoHuffman* arvoreHuffman::buscaNo(char simbolo) {
    
    NoHuffman *p = raiz;
    std::queue<NoHuffman *> que;
    
    que.push(p);
    while(!que.empty()) {
        p = que.front();
        if(p->getSimbolo() == simbolo)
            return p;
        if(p->getNoDir() != nullptr)
            que.push(p->getNoDir());
        if(p->getNoEsq() != nullptr)
            que.push(p->getNoEsq());
        que.pop();
    }
    return escape;
}
*/
bool arvoreHuffman::verificaSimbolo(char review)
{
    biblioteca.setAtual(biblioteca.getInicio());
    while(biblioteca.getAtual()->getProx() != nullptr)
    {
        biblioteca.setAtual(biblioteca.getAtual()->getProx());
        if ((biblioteca.getAtual()->getNoH()->getSimbolo() != '0') && (biblioteca.getAtual()->getNoH()->getSimbolo() == review))
        {
            return true;
        }
    }
    return false;
}
// verifica se no com um determinado símbolo está presente na árvore
/* bool arvoreHuffman::verificaSimbolo(char review)
{
    biblioteca.setAtual(biblioteca.getInicio());
    while(biblioteca.getAtual()->getProx() != nullptr)
    {
        biblioteca.setAtual(biblioteca.getAtual()->getProx());
        if ((biblioteca.getAtual()->getNoH()->getSimbolo() != '0') && (biblioteca.getAtual()->getNoH()->getSimbolo() == review))
        {
            return true;
        }
    }
    return false;
} */



// ########## MANIPULAÇÃO DA LISTA DUPLAMENTE ENCADEADA (BIBLIOTECA) ##########

// verifica uma possível rotação após incrementar símbolo repetido na árvore
void arvoreHuffman::verificaRotRep(noDupEnc *atual)
{ 
    biblioteca.setAtual(atual);
    while (biblioteca.getAtual()->getAnt() != biblioteca.getInicio())
    {
        biblioteca.setAtual(biblioteca.getAtual()->getAnt());
        if ((biblioteca.getAtual()->getNoH()->getSimbolo() != '0') && (biblioteca.getAtual()->getNoH()->getFrequencia() < atual->getNoH()->getFrequencia()))
        {
            rotacionaRep(biblioteca.getAtual(), atual);
            return;
        }
    }
}

// verifica uma possível rotação após adicionar símbolo novo na árvore
void arvoreHuffman::verificaRotPri(noDupEnc *atual)
{
    atual->getNoH()->setFrequencia();
    biblioteca.setAtual(biblioteca.getInicio()->getProx());
    while (biblioteca.getAtual() != atual)
    {
        if ((biblioteca.getAtual()->getNoH()->getSimbolo() != '0') && (biblioteca.getAtual()->getNoH()->getFrequencia() < atual->getNoH()->getFrequencia()))
        {
            rotacionaPri(biblioteca.getAtual(), atual);
            biblioteca.setAtual(atual);
        }
        else
        {
            biblioteca.setAtual(biblioteca.getAtual()->getProx());
        }
    }
}


// função com o objetivo de adicionar novos símbolos na lista duplamente encadeada (biblioteca)
void arvoreHuffman::addBiblioteca(NoHuffman* no)
{
    noDupEnc *aux = new noDupEnc();
    aux->setNoH(no);

    if(biblioteca.getInicio() == nullptr)
    {
        biblioteca.setInicio(aux);
        biblioteca.setFim(aux);
        biblioteca.getFim()->geraCodificacao(no);
    }
    else if (biblioteca.getInicio() == biblioteca.getFim())
    {
        biblioteca.setFim(aux);
        biblioteca.getFim()->setAnt(biblioteca.getInicio());
        biblioteca.getInicio()->setProx(biblioteca.getFim());
        biblioteca.getFim()->geraCodificacao(no);
    }
    else
    {
        biblioteca.setAtual(biblioteca.getInicio());
        while (biblioteca.getAtual() != biblioteca.getFim())
        {
            biblioteca.setAtual(biblioteca.getAtual()->getProx());
        }
        biblioteca.getFim()->setProx(aux);
        biblioteca.setFim(aux);
        biblioteca.getFim()->setAnt(biblioteca.getAtual());
        biblioteca.getFim()->geraCodificacao(no);
        if(no->getSimbolo() != '0')
        {
            if (no->getNoPai()->getNoPai() == raiz)
            {
                no->getNoPai()->getNoPai()->setFrequencia();
            }
            else
            {
                verificaRotPri(biblioteca.getAtual()->getAnt()->getAnt());
            }
        }
    }
}

void arvoreHuffman::rotacionaPri(noDupEnc *anterior, noDupEnc *atual)
{
    
}

void arvoreHuffman::rotacionaRep(noDupEnc *anterior, noDupEnc *atual)
{
    NoHuffman *aux_anterior = new NoHuffman();
    aux_anterior = anterior->getNoH();

    //atualiza a biblioteca
    biblioteca.troca(anterior, atual);

    //atualiza no anterior
    anterior->getNoH()->setNoPai(atual->getNoH()->getNoPai());
    anterior->getNoH()->setNoDir(atual->getNoH()->getNoDir());
    anterior->getNoH()->setNoEsq(atual->getNoH()->getNoEsq());
    if (atual->getNoH()->getNoPai()->getNoDir() == atual->getNoH())
    {
        atual->getNoH()->getNoPai()->setNoDir(anterior->getNoH());
    }
    else
    {
        atual->getNoH()->getNoPai()->setNoEsq(anterior->getNoH());
    }
    anterior->setNoH(atual->getNoH());

    //atualiza no atual
    atual->getNoH()->setNoPai(aux_anterior->getNoPai());
    atual->getNoH()->setNoDir(aux_anterior->getNoDir());
    atual->getNoH()->setNoEsq(aux_anterior->getNoEsq());
    if (aux_anterior->getNoPai()->getNoDir() == aux_anterior)
    {
        aux_anterior->getNoPai()->setNoDir(atual->getNoH());
    }
    else
    {
        aux_anterior->getNoPai()->setNoEsq(atual->getNoH());
    }
    atual->setNoH(aux_anterior);

    anterior->getNoH()->getNoPai()->setFrequencia();
    raiz->setFrequencia();
}

// a função de rotacionar precisará fazer a troca do nó líder pelo seu irmão na árvore, e além disso deverá trocar a posição referente aos dois nós na lista duplamente encadeada
// a função de rotacionar deverá também chamar novamente o verificar propriedade para saber se outras rotações serão necessárias

/*
void arvoreHuffman::imprimeArvore()
{
    
    // NoHuffman *auxD = noH->getNoDir();
    // NoHuffman *auxE = noH;

    NoHuffman *p = raiz;
    std::queue<NoHuffman *> que;
    
    que.push(p);
    while(!que.empty()) {
        p = que.front();
        std::cout << p->getSimbolo() << "\t" << p->getFrequencia() << std::endl;
        if(p->getNoDir() != nullptr)
            que.push(p->getNoDir());
        if(p->getNoEsq() != nullptr)
            que.push(p->getNoEsq());
        que.pop();
    }
    std::cout << "\n";
}
*/


void arvoreHuffman::imprimeArvore()
{
    std::cout << "Simb: " << raiz->getNoDir()->getSimbolo() << std::endl;
    std::cout << "Freq: " << raiz->getNoDir()->getFrequencia() << std::endl;
    //std::cout << "Cod: " << raiz->getNoDir()->getCodificacao() << std::endl;
    NoHuffman *aux = new NoHuffman();
    aux = raiz;
    while(aux->getNoEsq() != escape)
    {
        std::cout << "Simb: " << aux->getNoEsq()->getNoDir()->getSimbolo() << std::endl;
        std::cout << "Freq: " << aux->getNoEsq()->getNoDir()->getFrequencia() << std::endl;
        //std::cout << "Cod: " << aux->getNoEsq()->getNoDir()->getCodificacao() << std::endl;
        aux = aux->getNoEsq(); 
    }
    std::cout << "\n";
}


void arvoreHuffman::imprimeBiblioteca()
{
    biblioteca.setAtual(biblioteca.getInicio());
    while (biblioteca.getAtual()->getProx() != nullptr)
    {
        std::cout << biblioteca.getAtual()->getNoH()->getSimbolo() << std::endl;
        biblioteca.setAtual(biblioteca.getAtual()->getProx());
    }
    std::cout << biblioteca.getAtual()->getNoH()->getSimbolo() << std::endl;
}

// ########## FUNÇÕES DO STRUCT noDupEnc EM arvoreHuffman.h ##########

noDupEnc::noDupEnc()
{
    noH = nullptr;
    ant = nullptr;
    prox = nullptr;
    codificacao = "";
}

noDupEnc::~noDupEnc()
{
    //deleta lista
}

void noDupEnc::setNoH(NoHuffman *no)
{
    noH = no;
}

NoHuffman* noDupEnc::getNoH()
{
    return noH;
}

void noDupEnc::setAnt(noDupEnc *no)
{
    ant = no;
}

noDupEnc* noDupEnc::getAnt()
{
    return ant;
}

void noDupEnc::setProx(noDupEnc *no)
{
    prox = no;
}

noDupEnc* noDupEnc::getProx()
{
    return prox;
}

void noDupEnc::setCodificacao(std::string cod)
{
    codificacao = cod;
}

std::string noDupEnc::getCodificacao()
{
    return codificacao;
}


void noDupEnc::geraCodificacao(NoHuffman *noH)
{
    if (noH->getNoPai() != nullptr)
    {
        std::string mapeamento;
        NoHuffman *aux = new NoHuffman();
        aux = noH;
        while(aux->getNoPai() != nullptr)
        {
            mapeamento.append(aux->getCodificacao());
            aux = aux->getNoPai();
        }
        std::string saida (mapeamento.rbegin(), mapeamento.rend()); 
        setCodificacao(saida);
    }
    else
    {
        //continua
    }
}


// ##### FUNÇÕES DO STRUCT listaDupEnc EM arvoreHuffman.h #####

listaDupEnc::listaDupEnc()
{
    inicio = nullptr;
    fim = nullptr;
    atual = nullptr;
}

listaDupEnc::~listaDupEnc()
{
    // destrutor da lista
}

void listaDupEnc::setInicio(noDupEnc *no)
{
    inicio = no;
}

noDupEnc* listaDupEnc::getInicio()
{
    return inicio;
}

void listaDupEnc::setFim(noDupEnc *no)
{
    fim = no;
}

noDupEnc* listaDupEnc::getFim()
{
    return fim;
}

void listaDupEnc::setAtual(noDupEnc *no)
{
    atual = no;
}

noDupEnc* listaDupEnc::getAtual()
{
    return atual;
}

void listaDupEnc::troca(noDupEnc *anterior, noDupEnc *atual)
{
    //noDupEnc *aux_anterior = anterior;
    noDupEnc *aux_atual = atual;

    //std::cout << anterior->getNoH()->getSimbolo() << std::endl;
    //std::cout << atual->getNoH()->getSimbolo() << std::endl;

    atual->setAnt(anterior->getAnt());
    atual->setProx(anterior->getProx());

    anterior->setAnt(atual->getAnt());
    anterior->setProx(atual->getProx());

    atual = anterior;
    anterior = aux_atual;

    //std::cout << anterior->getNoH()->getSimbolo() << std::endl;
    //std::cout << atual->getNoH()->getSimbolo() << std::endl;
}

