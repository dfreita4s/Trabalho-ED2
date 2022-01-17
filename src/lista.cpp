#include <iostream>
#include "../inc/lista.h"
#include "../inc/registro.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>
Lista::Lista(const std::string &caminhoArquivo)
{
    this->abrirArquivo(caminhoArquivo);
}

Lista::~Lista()
{
    this->arquivo.close();
}

bool Lista::abrirArquivo(const std::string &caminhoArquivo)
{
    try
    {
        this->arquivo.open(caminhoArquivo, std::ios::in);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Houve um erro ao abrir o arquivo!" << std::endl
                  << e.what() << '\n';
    }
    return false;
}

bool Lista::obterReviews()
{
    if (this->arquivo.is_open())
    {
        std::string linha;
        getline(this->arquivo, linha); //Le cabecalho do arquivo

        getline(this->arquivo, linha);

        int k = 0; // contar registros
        int pos = 0;
        std::string id;
        std::string data;
        char *id_c = new char[87];
        char *data_c = new char[20];
        char *versao_c = new char[11];
        Registro *registro = new Registro[3646475];

        while (!arquivo.eof() && linha != "")
        {
            /* Trata os registros que estão com '\n'
               Verifica se a última informação é do tipo ':SS' */

            while (!(isdigit(linha[linha.length() - 1]) && (isdigit(linha[linha.length() - 2])) && (linha[linha.length() - 3] == ':')))
            {
                std::string aux = linha;
                getline(this->arquivo, linha);
                aux.append(linha);
                linha = aux;
            }

            pos = linha.find(",");
            id = linha.substr(3, pos - 3); // Inicio em 3 para retirar 'gp:'

            linha = linha.substr(pos + 1, linha.length());

            pos = linha.find_last_of(",");
            data = linha.substr(pos + 1).c_str(); // Obter a Data
            linha = linha.substr(0, pos);

            pos = linha.find_last_of(",");
            std::string versao = linha.substr(pos + 1); // Obter a versão
            if (versao.length() == 0)
                versao = "00.0.0";
            linha = linha.substr(0, pos);
            pos = linha.find_last_of(",");
            int upvotes = stod(linha.substr(pos + 1)); // Obter upvotes
            linha = linha.substr(0, pos);

            std::string texto = linha; // Obter o comentário
            if (texto.find("\"") != -1)
                texto = texto.substr(1, texto.length() - 2); // Caso comece com esteja entre "", retirá-los

            strcpy(id_c, id.c_str());
            strcpy(data_c, data.c_str());
            strcpy(versao_c, versao.c_str());
            registro[k].setID(id_c);
            registro[k].setDate(data_c);
            registro[k].setVotes(upvotes);
            registro[k].setVersion(versao_c);
            registro[k].setText(texto);

            k++;
            getline(this->arquivo, linha);
        }
        std::cout << k - 1 << " de registros foram importados com sucesso." << std::endl;

        criarArquivoBinario(registro);
        delete[] registro;
        return true;
    }
    std::cout << "Ocorreu um erro ao ler os dados." << std::endl;
    return false;
}


bool Lista::criarArquivoBinario(Registro *registro)
{
    std::ofstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    std::ofstream textBin;
    textBin.open("./data/textBin.bin", std::ios::binary); //binario dos textos

    if (arqBin.is_open() && textBin.is_open())
    {
        // if (this->obterRaiz() == nullptr)
        //     return false;

        // Review *No = this->obterRaiz();

        char *id = new char[87]; //trocar no reviews
        int votos = 0;
        int versao = 0;
        char *data = new char[19];
        int tamTexto = 0, posTexto = 0;

        //Grava o número total de registros
        // int numRegistros = this->obterTotal();

        int i = 0;
        while (i < 3646475)
        {
            // id, votos,tamanho texto, pos texto,versao, data
            arqBin.write(registro[i].getID().c_str(), sizeof(char) * 86);
            votos = registro[i].getVotes();
            arqBin.write((char *)(&votos), sizeof(int));

            //passar o texto para outro arquivo binario com o tamanho dele e pos dele
            tamTexto = registro[i].getText().length();
            arqBin.write((char *)(&tamTexto), sizeof(int));
            arqBin.write((char *)(&posTexto), sizeof(int));
            textBin.write(registro[i].getText().c_str(), sizeof(char) * tamTexto);
            posTexto += tamTexto;

            // versao = versaoToInt(registro[i].getVersion());
            arqBin.write(registro[i].getVersion().c_str(), sizeof(char) * 10);

            arqBin.write(registro[i].getDate().c_str(), sizeof(char) * 19);

            i++;
        }

        arqBin.close();
        std::cout << "O arquivo binário foi criado." << std::endl;
        return true;
    }
    std::cout << "Erro ao criar arquivo binário." << std::endl;
    return false;
}

int Lista::versaoToInt(std::string sversao)
{
    std::string aux;

    for (int i = 0; i < sversao.length(); i++)
        if (sversao[i] != '.' && sversao[i] != 'v')
            aux += sversao[i];

    if (aux == "")
        aux = '0';

    return stoi(aux);
}
