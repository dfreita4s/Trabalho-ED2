#include "../inc/NoVP.h"

NoVP::NoVP()
{
    NoVP("", 0);
}

NoVP::NoVP(std::string id, int posicao)
{
    ID = id;
    Valor = posicao;
    Cor = Vermelho;
    NoPai = nullptr;
    NoEsq = nullptr;
    NoDir = nullptr;
}

NoVP::~NoVP()
{
    std::cout << "Destruindo no " << Valor << std::endl;
}

// Review do Nó

void NoVP::setValor(int novoValor)
{
    Valor = novoValor;
}

int NoVP::getValor()
{
    return Valor;
}

void NoVP::setNoPai(NoVP *no)
{
    NoPai = no;
}

void NoVP::setNoEsq(NoVP *no)
{
    NoEsq = no;
}

void NoVP::setNoDir(NoVP *no)
{
    NoDir = no;
}

NoVP* NoVP::getNoPai()
{
    return NoPai;
}

NoVP* NoVP::getNoEsq()
{
    return NoEsq;
}

NoVP* NoVP::getNoDir()
{
    return NoDir;
}

void NoVP::setColor(Color cor)
{
    Cor = cor;
}

std::string NoVP::getID()
{
    return ID;
}

Color NoVP::getColor()
{
    return Cor;
}

void NoVP::info()
{
    Color estacor = getColor();
    std::cout <<"[Posição("<< getID() <<"),Posição("<< getValor() <<"),Cor(";
    estacor == Vermelho ? std::cout <<  "Vermelho" : std::cout << "Preto";
    std::cout << ")]" << std::endl;
}