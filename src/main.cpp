#include <iostream>
#include <fstream>
#include <chrono>
#include "../inc/lista.h"
#include "../inc/registro.h"

using namespace std;

int obterReview();
void acessaRegistro(int);
bool checaArqBin();

void testeImportacao(Registro *lista) //passar esse para o registro.cpp
{
    int resp, N = 0;
    std::cout << "Deseja exibir a saida no console ou salva-la em um arquivo texto? 1 para no console 2 para salvar.:";
    std::cin >> resp;
    if (resp == 1)
    {
        // Printar no terminal N = 10 registros aleatorios
        N = 10;
        for (int i = 0; i < N; i++)
            std::cout << lista[i].imprimeRegistros() << std::endl
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
                linha = lista[i].imprimeRegistros();
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

void leBinario(Registro *registro, int k)
{

    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        // arqBin.seekg(0, arqBin.end);
        // int tamTotal = arqBin.tellg();
        // arqBin.seekg(0, arqBin.beg);
        int randm = rand() % 3646475 + 0;
        std::string str = "";
        int i = 0;
        int pos = 0;
        int j = 0;

        while (getline(arqBin, str))
        {
            arqBin.seekg(0);

            if (randm == j)
            {

                pos = str.find(",");
                registro[i].setID(str.substr(0, pos)); // id

                str = str.substr(pos + 1, str.length());

                pos = str.find_last_of("\"") + 1;
                registro[i].setText(str.substr(0, pos)); // text

                str = str.substr(pos + 1, str.length());

                pos = str.find(",");
                registro[i].setVotes(atoi(str.substr(0, pos).c_str())); // votes

                str = str.substr(pos + 1, str.length());

                pos = str.find(",");

                registro[i].setVersion(str.substr(0, pos)); // version
                str = str.substr(pos + 1, str.length());

                registro[i].setDate(str.substr(0, str.length())); // data

                i++;
                randm = rand() % 3646475 + 0;
            }
            else
                j++;
            if (i == k - 1)
                break;
        }

        arqBin.close();
    }
    else
        cout << "Não foi possível abrir o arquivo!" << endl;
}

void menu()
{

    cout << "Menu:\nDigite o valor da função para acessa-la\n[1] Acessa Registro\n[2] Importar Registros\n[3] Sair\nFunção: ";
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
        leBinario(registro, N); //le e salva na memoria principal os registros
        cout << "Digite a funçao que deseja acessar\n[1] Teste Importação\n[2] Ordenar Registros\nFunção: ";
        cin >> resp;
        if (resp == 1)
            testeImportacao(registro);
        else if (resp == 2)
            quickSort_time(registro, N);
        else
            cout << "Digite um valor valido!" << endl;
        menu();
    }
    else if (resp == 3)
    {
        return;
    }
    else
    {
        cout << "Por favor digite uma resposta válida!" << endl;
        menu();
    }
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

void acessaRegistro(int k)
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

/// ALGORITMO DE ORDENAÇÃO - QUICK SORT ///

//realizar a ordenação desses registros, utilizando como chave de ordenação upvotes. Durante a ordenação, deverão ser computados o
//total de comparações de chaves e o total de movimentações de chaves. Além disso, o tempo de execução do algoritmo deverá ser medido.
//Para gerar as estatísticas de desempenho, você deverá executar os passos acima para M diferentes conjuntos de N registros aleatórios.
//Minimamente, utilize M=3. Ao final, compute as médias de cada uma das métricas (comparações, movimentações e tempo)

void trocaNo(Registro r1, Registro r2)
{
    Registro aux;
    aux = r1;
    r1 = r2;
    r2 = aux;
}

Registro pivoMediano(Registro *l, int inicio, int fim)
{
    int media = (inicio + fim) / 2;
    if (l[inicio].getVotes() > l[fim].getVotes())
        trocaNo(l[inicio], l[fim]);
    if (l[media].getVotes() > l[fim].getVotes())
        trocaNo(l[media], l[fim]);
    if (l[inicio].getVotes() > l[media].getVotes())
        trocaNo(l[inicio], l[media]);
    trocaNo(l[media], l[fim]);
    return l[fim];
}

int quickSort_particionaLista(Registro *list, int i, int j)
{

    int fim = j - 1;
    int init = i;
    Registro pivo = pivoMediano(list, i, j);

    while (true)
    {
        while (i < j && list[i].getVotes() < pivo.getVotes())
        {
            i = i + 1;
        }
        while (j >= init && list[i].getVotes() < pivo.getVotes())
        {
            j = j - 1;
        }
        if (i <= j)
        {
            trocaNo(list[i], list[j]);
            i = i + 1;
            j = j - 1;
        }
        else
            break;
        trocaNo(list[i], list[j]);
        return i;
    }
}
void quickSort_ordena(Registro *list, int i, int k)
{
    if (i - k > 0)
    {
        int p = quickSort_particionaLista(list, i, k);
        quickSort_ordena(list, i, p);
        quickSort_ordena(list, p + 1, k);
    }
}

void quickSort_time(Registro *list, int n)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    quickSort_ordena(list, 0, n - 1);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "/nTempo gasto na ordenação: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " segundos" << std::endl;
}

/*

===================FIM QUICKSORT========================

*/

int main(int argc, char const *argv[])
{
    if (!checaArqBin())
    {
        // Diretório completo para funcionar o Debug
        string caminhoArquivo = "";
        if (argc == 1)
        {
            std::cout << "Nenhum aquivo foi passado como argumento." << std::endl;
            return -1;
        }
        else
            caminhoArquivo = argv[1];

        Lista *listaReview = new Lista(caminhoArquivo);
        listaReview->obterReviews();        // Leitura e armazenamento dos dados.
        listaReview->criarArquivoBinario(); // Criação do aquivo binário.
        delete listaReview;
    }

    menu();

    return 0;
}
