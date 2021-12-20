#include <iostream>
#include <fstream>
#include <string>

#include "../inc/registro.h"

// Registro::Registro(const std::string &caminhoArquivo, int N)
// {
//     this->registros = new std::string[N]; //chama o array para salvar na memoria principal os N registros
//     setN(N);
//     setRegistro(importaRegistros(N));
// }

Registro::Registro()
{
    //contrutor
}

Registro::~Registro()
{
    //Destructor
    delete registros;
}

std::string Registro::imprimeRegistros()
{
    return ("ID: " + getID() + "\nMensagem: " + getText() + "\nVotos: " + std::to_string(getVotes()) + "\nVersão: " + getVersion() + "\nData/Hora: " + getDate());
    // std::cout << "ID: " << getID() << std::endl;
    // std::cout << "Mensagem: \"" << getText() << "\"" <<std::endl;
    // std::cout << "Votos /\\: " << getVotes() << std::endl;
    // std::cout << "Versão do Aplicativo: " << getVersion() << std::endl;
    // std::cout << "Data/Hora: " << getDate() << std::endl;
    // std::cout << std::endl;
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

void Registro::acessaRegistro(int k)
{
    std::cout << "Acessando registro " << k << std::endl;
    std::string registro = leBinario(k);
    if (registro != "")
        std::cout << registro;
    else
        std::cout << "Numero de registro não encontrado!" << std::endl;
}

std::string Registro::leBinario(int k)
{

    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        std::string str = "";
        int cont = 0;
        while (getline(arqBin, str))
        {
            if (cont == k)
            {                      //se o cont == k chegou na linha certa
                return str + "\n"; //retorna a linha
            }
            else
                cont++;
        }
        std::cout << "Diretório " << k << " não existe!" << std::endl;
        return "";
        arqBin.close();
    }
    else
    {
        std::cout << "Não foi possível abrir o arquivo!" << std::endl;
        return "";
    }
}

std::string *Registro::getRegistro()
{
    return this->registros;
}

void Registro::setRegistro(std::string *regist)
{
    this->registros = regist;
}

std::string *Registro::importaRegistros(int N) //retorna N registros aleatorios do arquivo binario
{
    std::string *aux = new std::string[N];
    for (int i = 0; i < N; i++)
        aux[i] = leBinario(rand() % 3646475 + 0);

    return aux;
}

void Registro::testeImportacao()
{
    int resp = 0;
    std::string *registro = getRegistro();
    std::cout << "Deseja exibir a saida no console ou salva-la em um arquivo texto? 1 para no console 2 para salvar: ";
    std::cin >> resp;
    if (resp == 1)
    {
        // Printar no terminal N = 10 registros aleatorios

        for (int i = 0; i < 10; i++)
            std::cout << "[" << i + 1 << "]" << registro[i] << std::endl;
    }
    else if (resp == 2)
    {
        //Salvar em um txt N = 100 registros aleatorios
        std::fstream saidaTxt;
        saidaTxt.open("./data/saidaTxt.txt", std::ios_base::out | std::ios_base::app);
        if (saidaTxt.is_open())
        {

            std::string linha = "";
            for (int i = 0; i < 100; i++)
            {
                linha = registro[i];
                saidaTxt.write(linha.c_str(), sizeof(char) * linha.size());
            }
            std::cout << "O arquivo de texto foi criado!" << std::endl;
        }
        saidaTxt.close();
    }
    else
    {
        std::cout << "Por favor, digite um valor válido!" << std::endl;
    }
}

void Registro::ordenaRegistros()
{
    quickSort_time(getRegistro(), getN());
}

/// ALGORITMO DE ORDENAÇÃO - HEAPSORT ///

// void Registro::heapSort_ordena(int *list, int tam)
// {
//     //constroiHeap(v, n);
//     while (tam > 0)
//     {
//         troca(list[0], list[tam - 1]);
//         heapify(list, 0, tam - 1);
//         tam = tam - 1;
//     }
// }

// void heapSort_time(Review * list, int n)
// {
//     high_resolution_clock::time_point start = high_resolution_clock::now();
//     heapSort_ordena(list, 0, n - 1);
//     high_resolution_clock::time_point end = high_resolution_clock::now();
//     cout << "/nTempo gasto na ordenação: " << duration_cast<duration<double>>(start - end).count() << " segundos" << endl;
// }
