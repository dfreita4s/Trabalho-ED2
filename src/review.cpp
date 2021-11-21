#include "../inc/review.h"
#include <fstream>
#include <iostream>

Review::Review(std::string id, std::string texto, int upvotes, std::string versao, std::string data)
{
    this->id = id;
    this->texto = texto;
    this->upvotes = upvotes;
    this->versaoApp = versao;
    this->data = data;
    this->proxReview = nullptr;
}

Review::~Review()
{
   //std::cout << "Destruindo " << this->id << std::endl;
}

void Review::exibeRegistro()
{
    std::cout << "ID: " << this->id << std::endl;
    std::cout << "Mensagem: \"" << this->texto << "\"" <<std::endl;
    std::cout << "Votos /\\: " << this->upvotes << std::endl;
    std::cout << "Versão do Aplicativo: " << this->versaoApp << std::endl;
    std::cout << "Data/Hora: " << this->data << std::endl;
    std::cout << std::endl;
}

std::string Review::obterID()
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

std::string Review::obterVersao()
{
    return this->versaoApp;
}

std::string Review::obterData()
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

