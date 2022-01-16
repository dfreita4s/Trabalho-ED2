#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "../inc/registro.h"


Registro::Registro()
{
    //contrutor
}

Registro::~Registro()
{
    //Destructor
}

std::string Registro::imprimeRegistros()
{
    return ("ID: " + getID() + "\nMensagem: " + getText() + "\nVotos: " + std::to_string(getVotes()) + "\nVersão: " + getVersion() + "\nData/Hora: " + getDate());
}

void Registro::setID(std::string id)
{
    this->review_id = id;
}
void Registro::setText(std::string text)
{
    this->review_text = text;
}
void Registro::setVersion(std::string version)
{
    this->app_version = version;
}
void Registro::setDate(std::string date)
{
    this->posted_date = date;
}
void Registro::setVotes(int votes)
{
    this->upvotes = votes;
}
std::string Registro::getID()
{
    return this->review_id;
}
std::string Registro::getText()
{
    return this->review_text;
}
std::string Registro::getVersion()
{
    return this->app_version;
}
std::string Registro::getDate()
{
    return this->posted_date;
}
int Registro::getVotes()
{
    return this->upvotes;
}

void Registro::setN(int N)
{
    this->N = N;
}

int Registro::getN()
{
    return this->N;
}

