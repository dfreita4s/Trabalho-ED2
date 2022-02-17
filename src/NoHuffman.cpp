#include "../inc/NoHuffman.h"


NoHuffman::NoHuffman()
{
    this->simbolo = '0';
    this->frequencia = 0;
    this->tipoNo = "n_lider";
    this->codificacao = "";
    pai = nullptr;
    dir = nullptr;
    esq = nullptr;
}

NoHuffman::~NoHuffman()
{
    //destrutor
}

void NoHuffman::setNoPai(NoHuffman *no)
{
    this->pai = no;
}

NoHuffman* NoHuffman::getNoPai()
{
    return this->pai;
}

void NoHuffman::setNoDir(NoHuffman *no)
{
    this->dir = no;
}

NoHuffman* NoHuffman::getNoDir()
{
    return this->dir;
}

void NoHuffman::setNoEsq(NoHuffman *no)
{
    this->esq = no;
}

NoHuffman* NoHuffman::getNoEsq()
{
    return this->esq;
}

void NoHuffman::setFrequencia()
{
    this->frequencia++;
}

int NoHuffman::getFrequencia()
{
    return this->frequencia;
}

void NoHuffman::setSimbolo(char s)
{
    this->simbolo = s;
}

char NoHuffman::getSimbolo()
{
    return this->simbolo;
}

void NoHuffman::setTipoNo(std::string tipo)
{
    this->tipoNo = tipo;
}

std::string NoHuffman::getTipoNo()
{
    return this->tipoNo;
}

void NoHuffman::setCodificacao(std::string cod)
{
    this->codificacao = cod;
}

std::string NoHuffman::getCodificacao()
{
    return this->codificacao;
}

void NoHuffman::incrementaCodificacao(std::string cod)
{
    this->codificacao = this->codificacao + cod;
}

