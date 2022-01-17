#ifndef NOVP_H
#define NOVP_H

#include<iostream>

enum Color {
    Vermelho, 
    Preto
};

class NoVP
{
private:
    std::string ID;
    int pos;
    Color Cor;
    NoVP *NoPai;
    NoVP *NoEsq;
    NoVP *NoDir;
public:
    NoVP();
    NoVP(std::string, int);
    ~NoVP();

    void setNoPai(NoVP *);
    void setNoEsq(NoVP *);
    void setNoDir(NoVP *);
    void setColor(Color);
    void setPosicao(int);
    NoVP* getNoPai();
    NoVP* getNoEsq();
    NoVP* getNoDir();
    std::string getID();
    Color getColor();
    int getPosicao();
    void info();
};


#endif