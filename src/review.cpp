#include "../inc/review.h"
#include <fstream>
#include <iostream>

Review::Review(char *id, std::string texto, int upvotes, char *versao, char *data)
{
    this->id = new char[86];
    this->data = new char[19];
    this->versaoApp = new char[10];

    this->id = id;
    this->texto = texto;
    this->upvotes = upvotes;
    this->versaoApp = versao;
    this->data = data;
    this->proxReview = nullptr;

    //id: 86
    //texto: 3552
    //versao: 10
    //data: 19
    //votes: 4
    //3668
}

Review::~Review()
{
    //std::cout << "Destruindo " << this->id << std::endl;
}

void Review::exibeRegistro()
{
    std::cout << "ID: " << this->id << std::endl;
    std::cout << "Mensagem: \"" << this->texto << "\"" << std::endl;
    std::cout << "Votos /\\: " << this->upvotes << std::endl;
    std::cout << "Versão do Aplicativo: " << this->versaoApp << std::endl;
    std::cout << "Data/Hora: " << this->data << std::endl;
    std::cout << std::endl;
}

char *Review::obterID()
{
    return this->id;
}

std::string Review::obterTexto()
{
    return this->texto;
}

int Review::obterVotos()
{
    return this->upvotes;
}

char *Review::obterVersao()
{
    return this->versaoApp;
}

char *Review::obterData()
{
    return this->data;
}

Review *Review::obterProximo()
{
    return this->proxReview;
}

void Review::setarProximo(Review *No)
{
    this->proxReview = No;
}
