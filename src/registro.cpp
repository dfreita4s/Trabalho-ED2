#include <iostream>
#include <fstream>
#include "../inc/registro.h"

Registro::Registro(const std::string &caminhoArquivo, int N)
{
    this->registros = new std::string[N]; //chama o array para salvar na memoria principal os N registros
    setRegistro(importaRegistros(N));
}

Registro::~Registro()
{
    //Destructor
    delete registros;
}


std::string Registro::getTerms(int i, std::string regist){ //i = (id, text, votes, version, date) = (1, 2, 3, ...)
    std::string term = "";
    

    

    switch (i)
    {
    case 1: //id
        int pos = regist.find(",");
        term = regist.substr(0, pos);
        return term;
        break;
    case 2: //txt
        int pos = regist.find("\"");
        term = regist.substr(pos, regist.find_last_of("\""));
        return term;
        break;
    
    case 3: //nota
        int pos = regist.find_last_of("\"");

        term = regist.substr(pos + 1, pos + 2);
        return term;
        break;

    case 4: //version
        int pos = regist.find("\"");
        term = regist.substr(pos, regist.find_last_of(","));
        return term;
        break;

    case 5: //data
        int pos = regist.find("\"");
        term = regist.substr(pos, regist.find_last_of("\""));
        return term;
        break;
    
    
    
    default:
        break;
    }
}

void Registro::setID(std::string){
    
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


void Registro::ordenaRegistros(){

}

