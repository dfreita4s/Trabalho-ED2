#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
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

        p->setSimbolo('0');
        p->setFrequencia();
        p->setTipoNo("lider");
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
            NoHuffman *p = new NoHuffman();
            p = escape->getNoPai();

            NoHuffman *np = new NoHuffman();
            NoHuffman *i = new NoHuffman();

            //atualiza frequencia da raiz
            raiz->setFrequencia();

            // atualiza o antigo no pai (p)
            p->setNoEsq(np);

            // atualiza o no de escape
            escape->setNoPai(np);
            escape->setCodificacao("0");

            //atualiza o novo no pai (np)
            np->setNoPai(p);
            np->setNoDir(i);
            np->setNoEsq(escape);

            np->setSimbolo('0');
            np->setFrequencia();
            NoHuffman *aux_np = new NoHuffman();
            aux_np = np->getNoPai();
            while(aux_np != raiz)
            {
                aux_np->setFrequencia();
                aux_np = aux_np->getNoPai();
            }
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
        //outra função precisa ser feita para checar se as propriedades de huffman se sustentam
        else
        {
            NoHuffman *aux = new NoHuffman();
            aux = escape;
            while(aux->getNoPai() != nullptr)
            {
                aux = aux->getNoPai();
                if(aux->getNoDir()->getSimbolo() == review)
                {
                    aux->getNoDir()->setFrequencia();
                    aux->setFrequencia();
                    while(aux->getNoPai() != nullptr)
                    {
                        aux = aux->getNoPai();
                        aux->setFrequencia();
                    }
                }
                else if (aux->getNoEsq()->getSimbolo() == review)
                {
                    aux->getNoEsq()->setFrequencia();
                    aux->setFrequencia();
                    while (aux->getNoPai() != raiz)
                    {
                        aux = aux->getNoPai();
                        aux->setFrequencia();
                    }
                    raiz->setFrequencia();
                }
                else
                {
                    //continua
                }
            }
        }
    }
}


// verifica se no com um determinado símbolo está presente na árvore
bool arvoreHuffman::verificaSimbolo(char review)
{
    NoHuffman *aux = new NoHuffman();
    aux = escape;
    while (aux->getNoPai() != nullptr)
    {
        aux = aux->getNoPai();
        if ((aux->getNoDir()->getSimbolo() == review) && (aux->getNoDir()->getSimbolo() != '0'))
        {
            return true;
        }
        else if ((aux->getNoEsq()->getSimbolo() == review) && (aux->getNoEsq()->getSimbolo() != '0'))
        {
            return true;
        }
    }
    return false;
}


// ########## MANIPULAÇÃO DA LISTA DUPLAMENTE ENCADEADA (BIBLIOTECA) ##########
 
// função com o objetivo de adicionar novos símbolos na lista duplamente encadeada (biblioteca)
void arvoreHuffman::addBiblioteca(NoHuffman* no)
{
    noDupEnc *aux = new noDupEnc();
    aux->setNoH(no);

    if(biblioteca.getInicio() == nullptr)
    {
        biblioteca.setInicio(aux);
        biblioteca.setFim(aux);
        //biblioteca.getFim()->geraCodificacao(no);

        //std::cout << "Simb: " << biblioteca.getInicio()->getNoH()->getSimbolo() << std::endl;
        //std::cout << "Cod: " << biblioteca.getFim()->getCodificacao() << std::endl;
        delete aux;
    }
    else if (biblioteca.getInicio() == biblioteca.getFim())
    {
        biblioteca.setFim(aux);
        biblioteca.getFim()->setAnt(biblioteca.getInicio());
        biblioteca.getInicio()->setProx(biblioteca.getFim());
        //biblioteca.getFim()->geraCodificacao(no);

        //std::cout << "Simb: " << biblioteca.getFim()->getNoH()->getSimbolo() << std::endl;
        //std::cout << "Cod: " << biblioteca.getFim()->getCodificacao() << std::endl;
        delete aux;
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
        //std::cout << "Simb: " << biblioteca.getFim()->getNoH()->getSimbolo() << std::endl;
        //biblioteca.getFim()->geraCodificacao(no);
        //std::cout << "Cod: " << biblioteca.getFim()->getCodificacao() << std::endl;
    }
}

void arvoreHuffman::verificaPropriedade(NoHuffman *noH)
{

}

void arvoreHuffman::imprimeArvore()
{
    std::cout << "Simb: " << raiz->getNoDir()->getSimbolo() << std::endl;
    std::cout << "Freq: " << raiz->getNoDir()->getFrequencia() << std::endl;
    std::cout << "Cod: " << raiz->getNoDir()->getCodificacao() << std::endl;
    NoHuffman *aux = new NoHuffman();
    aux = raiz;
    while(aux->getNoEsq() != escape)
    {
        std::cout << "Simb: " << aux->getNoEsq()->getNoDir()->getSimbolo() << std::endl;
        std::cout << "Freq: " << aux->getNoEsq()->getNoDir()->getFrequencia() << std::endl;
        std::cout << "Cod: " << aux->getNoEsq()->getCodificacao() << std::endl;
        aux = aux->getNoEsq(); 
    }
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
    std::string aux_cod;
    NoHuffman *aux_no = new NoHuffman();
    aux_no = noH;
    while(aux_no->getNoPai()->getNoPai() != nullptr)
    {
        aux_cod = aux_cod + aux_no->getCodificacao();
        aux_no = aux_no->getNoPai();
    }
    int tam = aux_cod.length();
    char char_cod[tam+1];
    char aux_char_cod[tam+1];
    strcpy(char_cod, aux_cod.c_str());
    for (int i = tam-1; i < tam; i--)
    {
        for(int j = 0; j < tam; j++)
        {
            aux_char_cod[j] = char_cod[i];
        }
    }
    std::string saida;
    std::stringstream ss;
    ss << aux_char_cod;
    ss >> saida;
    setCodificacao(saida);
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

