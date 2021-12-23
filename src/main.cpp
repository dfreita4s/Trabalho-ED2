#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include "../inc/lista.h"
#include "../inc/registro.h"
#include "../inc/tabelaHash.h"

#define NREGISTROS 3646475
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

int obterReview();
bool checaArqBin();
void testeImportacao(Registro *lista)
{
    int resp, N = 0;
    std::cout << "Deseja exibir a saida no console ou salva-la em um arquivo texto? 1 para no console 2 para salvar.:";
    std::cin >> resp;
    if (resp == 1)
    {
        // Printar no terminal N = 10 registros aleatorios
        N = 10;
        for (int i = 0; i < N; i++)
            std::cout << "[" << i << "]" << lista[i].imprimeRegistros() << std::endl
                      << std::endl;
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
                // (rand() % 3646475 + 0)
                linha = lista[i].imprimeRegistros() + "\n";
                saidaTxt.write(linha.c_str(), sizeof(char) * linha.size());
            }
            cout << "O arquivo de texto foi criado!" << endl;
        }
        saidaTxt.close();
    }
    else
    {
        std::cout << "Por favor, digite um valor válido!" << std::endl;
    }
}
void acessaRegistro(int k) // acessa o K-ésimo registro do arquivo binario
{
    std::cout << "Acessando registro " << k << std::endl;
    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        std::string str = "";
        int i = 0;
        while (getline(arqBin, str))
        {
            if (i == k)
            {                            //se o i == k chegou na linha certa
                std::cout << str + "\n"; //retorna a linha
                break;
            }
            else
                i++;
        }
        arqBin.close();
    }
    else
    {
        cout << "Não foi possível abrir o arquivo!" << endl;
    }
}

void leBinario(Registro *registro, int N)
{

    //pensei pra ler o review_text e saber o tamanho um for em cada catactere da linha e ir ate o caracter ser == \n
    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    srand(time(NULL));
    if (arqBin.is_open())
    {
        int j = 0;
        int randNum = 0;
        std::string str = "";
        std::string *regist = new std::string[NREGISTROS];
        while (getline(arqBin, str)) //aloca todas a linhas no vetor regist
        {
            regist[j] = str + "\n";
            j++;
        }

        for (int i = 0; i < N; i++) //pega alguma linha aleatoria do regist e passa para o registro.cpp
        {
            randNum = rand() % NREGISTROS + 1;
            j = regist[randNum].find(",");
            registro[i].setID(regist[randNum].substr(0, j));

            regist[randNum] = regist[randNum].substr(j + 1, regist[randNum].length());

            j = regist[randNum].find_last_of("\"") + 1;
            registro[i].setText(regist[randNum].substr(0, j));

            regist[randNum] = regist[randNum].substr(j + 1, regist[randNum].length());

            j = regist[randNum].find(",");
            registro[i].setVotes(atoi(regist[randNum].substr(0, j).c_str()));

            regist[randNum] = regist[randNum].substr(j + 1, regist[randNum].length());

            j = regist[randNum].find(",");
            registro[i].setVersion(regist[randNum].substr(0, j));
            regist[randNum] = regist[randNum].substr(j + 1, regist[randNum].length());

            registro[i].setDate(regist[randNum].substr(0, regist[randNum].length()));
        }
        delete[] regist;
        arqBin.close();
    }

    else
        cout << "Não foi possível abrir o arquivo!" << endl;
}

bool checaArqBin()
{
    ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        std::cout << "O arquivo binário existe." << std::endl;
        return true;
    }
    return false;
}



bool confereNum(int *num, int i) // função avisa quando um número randômico é gerado mais de uma vez
{
    for (int j = i - 1; j >= 0; j--)
    {
        if (num[i] == num[j])
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

void menu()
{

    cout << "Menu:\nDigite o valor da função para acessa-la\n[1] Acessa Registro\n[2] Teste Importação\n[3] Importa na tabela Hash\n[4] Sair\nFunção: ";
    int resp = 0;
    cin >> resp;
    if (resp == 1)
    {
        int n = 0;
        cout << "Digite o registro que deseja: ";
        cin >> n;
        acessaRegistro(n);
        menu();
    }
    else if (resp == 2)
    {
        cout << "Digite o numero de importacoes que deseja: ";
        int N = 0;
        cin >> N;
        Registro *registro = new Registro[N];
        leBinario(registro, N); //importa N registros do arquivo Binario
        cout << "Digite a funçao que deseja acessar\n[1] Teste Importação\n[2] Ordenar Registros\nFunção: ";
        cin >> resp;
        if (resp == 1)
            testeImportacao(registro);
        else if (resp == 2)
        {
            std::cout << "Qual Ordendação voce deseja?\n[1] Quicksort\n[2] Heapsort\n[3] Combsort\nFunção: ";
            cin >> resp;
            if (resp == 1)
            std::cout<<"";
            // quickSort_time(registro, N);
            else if (resp == 2)
            std::cout<<"";
            // heapSort_time(registro, N);
            else if (resp == 3)
            std::cout<<"";
            // combSort_time(registro, N);
            else
                std::cout << "Digite uma resposta valida!" << std::endl;
        }
        else
            cout << "Digite um valor valido!" << endl;
        menu();
    }
    else if (resp == 3)
    {
        int n = 99;
        int resp;
        Registro *reg = new Registro[n];
        tabelaHash aux;
        aux.criaTabelaHash(reg,n);
        cout << "Tabela Hash gerada com sucesso..." << endl;
        cout << "Digite 1 para fazer a ordenacao e 2 para retornar ao menu" << endl;
        cin >> resp;
        if (resp == 1)
        {
            //chama ordenação
        }
        else
        {
            menu();
        }
    }
    else if (resp == 4)
    {
        return;
    }
    else
    {
        cout << "Por favor digite uma resposta válida!" << endl;
        menu();
    }
}

int main(int argc, char const *argv[])
{
    if (!checaArqBin())
    {
        // Diretório completo para funcionar o Debug
        string caminhoArquivo = "./data/tiktok_app_reviews.csv";
        if (argc == 1)
        {
            caminhoArquivo = "./data/tiktok_app_reviews.csv";
        }
        else
        {
            caminhoArquivo = argv[1];
        }
        Lista *listaReview = new Lista(caminhoArquivo);
        listaReview->obterReviews(); // Leitura e armazenamento dos dados.

        //listaReview->criarArquivoBinario(); // Criação do aquivo binário.
        //listaReview->criaTabelaHash();

        delete listaReview;
    }

    menu();

    return 0;
}
// void acessaRegistro(int k)
// {
//     std::cout << "Acessando registro " << k << std::endl;
//     std::string registro = leBinario(k);
//     if (registro != "")
//         std::cout << registro;
// }

// void testeImportacao()
// {
//     int resp, N = 0;
//     std::cout << "Deseja exibir a saida no console ou salva-la em um arquivo texto? 1 para no console 2 para salvar.:";
//     std::cin >> resp;
//     if (resp == 1)
//     {
//         // Printar no terminal N = 10 registros aleatorios
//         N = 10;
//         for (int i = 0; i < 10; i++)
//             std::cout << leBinario(rand() % 3646475 + 0) << std::endl;
//     }
//     else if (resp == 2)
//     {
//         //Salvar em um txt N = 100 registros aleatorios
//         std::fstream saidaTxt;
//         saidaTxt.open("./data/saidaTxt.txt", std::ios_base::out | std::ios_base::app);
//         if (saidaTxt.is_open())
//         {
//             N = 100;
//             std::string linha = "";
//             for (int i = 0; i < N; i++)
//             {
//                 linha = leBinario(rand() % 3646475 + 0);
//                 saidaTxt.write(linha.c_str(), sizeof(char) * linha.size());
//             }
//             cout << "O arquivo de texto foi criado!" << endl;
//         }
//         saidaTxt.close();
//     }
//     else
//     {
//         std::cout << "Por favor, digite um valor válido!" << std::endl;
//     }
// }