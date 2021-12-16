#include<iostream>
#include <fstream>
#include "../inc/registro.h"
using namespace std;

Registro::Registro(const std::string &caminhoArquivo, int N){
     this->registros = new string[N]; //chama o array para salvar na memoria principal os N registros
}

Registro::~Registro(){
    //Destructor
}


string Registro::leBinario(int k)
{

    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        arqBin.seekg(0, arqBin.end);
        int tamTotal = arqBin.tellg();
        arqBin.seekg(0, arqBin.beg);
        char *buffer = new char[tamTotal];
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
        cout << "Diretório " << k << " não existe!" << endl;
        return "";
        arqBin.close();
    }
    else
    {
        cout << "Não foi possível abrir o arquivo!" << endl;
        return "";
    }
}


void Registro::testeImportacao()
{
    int resp, N = 0;
    std::cout << "Deseja exibir a saida no console ou salva-la em um arquivo texto? 1 para no console 2 para salvar.:";
    std::cin >> resp;
    if (resp == 1)
    {
        // Printar no terminal N = 10 registros aleatorios
        N = 10;
        for (int i = 0; i < 10; i++)
            std::cout << leBinario(rand() % 3646475 + 0) << std::endl;
    }
    else if (resp == 2)
    {
        //Salvar em um txt N = 100 registros aleatorios
        std::fstream saidaTxt;
        saidaTxt.open("./data/saidaTxt.txt", std::ios_base::out | std::ios_base::app);
        if (saidaTxt.is_open())
        {
            N = 100;
            std::string linha = "";
            for (int i = 0; i < N; i++)
            {
                linha = leBinario(rand() % 3646475 + 0);
                saidaTxt.write(linha.c_str(), sizeof(char) * linha.size());
            }
            cout<<"O arquivo de texto foi criado!"<<endl;
        }
        saidaTxt.close();
    }
    else
    {
        std::cout << "Por favor, digite um valor válido!" << std::endl;
    }
}