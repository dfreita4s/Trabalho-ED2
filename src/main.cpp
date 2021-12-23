#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <sstream>
#include <cstring>
#include <algorithm>
#include "../inc/lista.h"
#include "../inc/ordenacao.h"
#include "../inc/tabelaHash.h"

#define NREGISTROS 3646475

using namespace std;

int obterReview();
bool checaArqBin();
void criaTabelaHash(Registro *reg, int n);
int retiraPontos(std::string versao);
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

void ordenacao(Registro *registro, int N)
{
    Ordenacao sort;
    srand(time(NULL));
    int *dat = new int[5]; //vetor com os valores de N 
    dat[0] = 10000;
    dat[1] = 50000;
    dat[2] = 100000;
    dat[3] = 500000;
    dat[4] = 1000000;

    float tempoQuicksort = 0;
    float tempoHeapsort = 0;
    float tempoCombksort = 0;

    float tempoMediaQuicksort = 0;
    float tempoMediaHeapsort = 0;
    float tempoMediaCombsort = 0;


    int *comparcoesQuicksort = 0;
    int *movimentacoesQuicksort = 0;

    int *comparcoesHeapsort = 0;
    int *movimentacoesHeapsort = 0;

    int *comparcoesCombsort = 0;
    int *movimentacoesCombsort = 0;

    int M = 3;
    std::fstream saida;
    saida.open("./data/saida.txt", std::ios_base::out | std::ios_base::app);
    if (saida.is_open())
    {
        for (int i = 0; i < M; i++)
        {
            int tam = dat[rand() % 5];
            leBinario(registro, tam);

            tempoQuicksort = sort.quickSort_time(registro, tam, comparcoesQuicksort, movimentacoesQuicksort);
            tempoHeapsort = sort.heapSort_time(registro, tam, movimentacoesHeapsort, movimentacoesHeapsort);
            tempoCombksort = sort.combSort_time(registro, tam, movimentacoesCombsort, movimentacoesCombsort);

            tempoMediaQuicksort += tempoQuicksort;
            tempoMediaHeapsort += tempoHeapsort;
            tempoMediaCombsort += tempoCombksort;


        }

        std::cout << "O arquivo de texto foi criado!" << std::endl;
    }
    else
        std::cout << "Nao foi possivel abrir o arquivo" << std::endl;
    saida.close();
}

void menu()
{

    cout << "Menu:\nDigite o valor da função para acessa-la\n[1] Ordenacao\n[2] Hash\n[3] Modulo de Teste\n[4] Sair\nFunção: ";
    int resp = 0;
    cin >> resp;
    if (resp == 1)
    {
        cout << "Digite o numero de importacoes que deseja: "; //mudar para testes com M = 3 e N = {10.000, 50.000, 100.000, 500.000, 1.000.000} ler de um .dat
        int N = 0;
        cin >> N;
        Registro *registro = new Registro[N];
        Registro reg;

        leBinario(registro, N); //importa N registros do arquivo Binario

        // cout << "\nQual metodo de ordenação voce deseja?\n[1] Quicksort\n[2] Heapsort\n[3] Combsort\nResposta:";
        // cin >> resp;
        // if (resp == 1)
        // {
        //     sort.quickSort_time(registro, N);
        // }
        // else if (resp == 2)
        //     sort.heapSort_time(registro, N);
        // else if (resp == 3)
        //     sort.combSort_time(registro, N);

        delete[] registro;
        menu();
    }
    else if (resp == 2)
    {
        int n = 99;
        int resp;
        cout << "Digite o numero de importacoes que deseja: ";
        int N = 0;
        cin >> N;
        Registro *reg = new Registro[N];
        leBinario(reg, n);
        criaTabelaHash(reg, n);
        cout << "Tabela Hash gerada com sucesso..." << endl;

        delete[] reg;
        menu();
    }
    else if (resp == 3)
    {
        cout << "Escolha\n[1] Teste de Importação\n[2] outra coisa";
        if (resp == 1)
        {

            cout << "Digite o numero de importacoes que deseja: ";
            int N = 0;
            cin >> N;
            Registro *registro = new Registro[N];
            Ordenacao sort;
            leBinario(registro, N);

            testeImportacao(registro);
            delete[] registro;
            menu();
        }
        else if (resp == 2)
        {
            cout << "Ui ui kk" << endl;
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

void criaTabelaHash(Registro *reg, int n)
{
    tabelaHash *tab = new tabelaHash[n];
    tabelaHash aux;
    int chave;
    std::string chaveOrig;
    for (int i = 0; i < n; i++)
    {
        chave = retiraPontos(reg[i].getVersion());
        chaveOrig = reg[i].getVersion();
        if (chave != 0)
        {
            if (tab[aux.funcaoHash(chave, n)].consultaContador() == 0) //Caso a função hash encontre uma posição vazia na tabela para inserir a chave
            {
                tab[aux.funcaoHash(chave, n)].insereChave(chave);
                tab[aux.funcaoHash(chave, n)].insereChaveOrig(chaveOrig);
            }
            else if ((tab[aux.funcaoHash(chave, n)].consultaContador() != 0) && (tab[aux.funcaoHash(chave, n)].consultaChave() == chave)) // Caso a função hash encontre uma posição na tabela onde outro review com a mesma versão já tenha sido inserido
            {
                tab[aux.funcaoHash(chave, n)].somaContador();
            }
            else if ((tab[aux.funcaoHash(chave, n)].consultaContador() != 0) && (tab[aux.funcaoHash(chave, n)].consultaChave() != chave)) //Caso a função hash devolva uma posição da tabela não vazia e que a versão do review é diferente do já inserido, ocorre a colisão
            {
                int j = 0;
                while ((tab[aux.trataColisao(chave, n, j)].consultaContador() != 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() != chave)) //Enquanto a colisão persistir, índice j, que entra na função de tratamento de colisão, é somado
                {
                    j++;
                }
                // ao sair do while, temos que a função trataColisao encontrou uma posição vazia na tabela para inserir a versão, ou ela encontrou uma posição na tabela onde a mesma versão de outro review já havia colidido e sido salva
                if ((tab[aux.trataColisao(chave, n, j)].consultaContador() != 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() == chave)) // caso a tabela já tenha a versão inserida por um review anterior
                {
                    tab[aux.trataColisao(chave, n, j)].somaContador();
                }
                else if ((tab[aux.trataColisao(chave, n, j)].consultaContador() == 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() != chave)) // caso uma posição vazia na tabela tenha sido encontrada para guardar a versão
                {
                    tab[aux.trataColisao(chave, n, j)].insereChave(chave);
                    tab[aux.trataColisao(chave, n, j)].insereChaveOrig(chaveOrig);
                }
                //contaColisao++;
            }
        }
        else
        {
            // ignora review com versão vazia
        }
    }
    cout << "Tabela Hash criada com sucesso" << endl;
    aux.imprimeTabela(tab, n);
}

int retiraPontos(std::string versao)
{
    char removePonto[] = ".";
    int chave;
    if (versao == "NaN")
    {
        return 0;
    }
    else
    {
        std::string temp = versao;
        for (unsigned int j = 0; j < strlen(removePonto); j++)
        {
            temp.erase(std::remove(temp.begin(), temp.end(), removePonto[j]), temp.end());
        }
        chave = stoi(temp);
        return chave;
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
