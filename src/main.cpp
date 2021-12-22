#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include "../inc/lista.h"
#include "../inc/registro.h"

#define NREGISTROS 3646475
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

int obterReview();
bool checaArqBin();
void criaTabelaHash(Lista *lista);
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

void criaTabelaHash(Lista *listaReview) //passar pra Registro *registro
{
    int n = 499;
    tabelaHash *tab = new tabelaHash[n];
    tabelaHash aux;
    int contaColisao = 0;
    srand(time(NULL));
    int *num = new int[n];
    for (int i = 0; i < n; i++)
    {
        //cout << "Na execucao " << " " << i << endl;
        num[i] = rand() % 3646475;
        if (confereNum(num, i) == true) // garante que um mesmo review não seja lido mais de uma vez
        {
            int chave = listaReview->pegaVersao(num[i]);
            if (chave != 0) //será 0 caso o review retorne versão vazia
            {
                if (tab[aux.funcaoHash(chave, n)].consultaContador() == 0) //Caso a função hash encontre uma posição vazia na tabela para inserir a chave
                {
                    tab[aux.funcaoHash(chave, n)].insereChave(chave);
                    cout << "Chave"
                         << " " << tab[aux.funcaoHash(chave, n)].consultaChave() << " "
                         << "inserida com sucesso na posicao "
                         << " " << aux.funcaoHash(chave, n) << " " << endl;
                }
                else if ((tab[aux.funcaoHash(chave, n)].consultaContador() != 0) && (tab[aux.funcaoHash(chave, n)].consultaChave() == chave)) // Caso a função hash encontre uma posição na tabela onde outro review com a mesma versão já tenha sido inserido
                {
                    tab[aux.funcaoHash(chave, n)].somaContador();
                    cout << "Repeticao da chave "
                         << " " << tab[aux.funcaoHash(chave, n)].consultaChave() << " "
                         << "detectada" << endl;
                    cout << "Contador somado, agora ele eh: "
                         << " " << tab[aux.funcaoHash(chave, n)].consultaContador() << endl;
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
                        cout << "repeticao via colisao detectada, versao"
                             << " " << chave << " "
                             << "teve seu contador somado para"
                             << " " << tab[aux.trataColisao(chave, n, j)].consultaContador() << endl;
                    }
                    else if ((tab[aux.trataColisao(chave, n, j)].consultaContador() == 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() != chave)) // caso uma posição vazia na tabela tenha sido encontrada para guardar a versão
                    {
                        tab[aux.trataColisao(chave, n, j)].insereChave(chave);
                        cout << "colisao detectada e chave"
                             << " " << chave << " "
                             << "tratada e inserida na posicao"
                             << " " << aux.trataColisao(chave, n, j) << endl;
                    }
                    contaColisao++;
                }
            }
            else
            {
                // ignora review com versão vazia
            }
        }
    }
    cout << "Tabela Hash criada com sucesso,"
         << " " << contaColisao << " "
         << "colisoes aconteceram" << endl;
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
        int n = 0;
        cout << "Informe quantos valores serao importados na tabela: " << endl;
        cin >> n;
        return;
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
        // criaTabelaHash(listaReview);

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
