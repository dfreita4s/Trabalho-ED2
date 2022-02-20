#include "../inc/HuffmanNo.h"

HuffmanNo::HuffmanNo(char simb, int freq){
    this->simb = simb;
    this->freq = freq;
    this->esq = nullptr;
    this->dir = nullptr;
}

HuffmanNo::~HuffmanNo(){
    //destructor 
}

void HuffmanNo::setDir(HuffmanNo *dir){
    this->dir = dir;
}

void HuffmanNo::setEsq(HuffmanNo *esq){
    this->esq = esq;
}

void HuffmanNo::setFreq(int freq){
    this->freq = freq;
}

void HuffmanNo::setSimb(char simb){
    this->simb = simb;
}


