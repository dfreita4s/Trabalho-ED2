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

void acessaRegistro(int k, Registro registro)
{
    std::cout << "Acessando registro " << k << std::endl;

    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        arqBin.seekg(0, arqBin.end);
        int tamTotal = arqBin.tellg();
        arqBin.seekg(0, arqBin.beg);

        int posInicial = 0, posProximo = 0; // Ponteiro no arquivo
        int i = 0;                          // Contador de linhas
        unsigned short tamanhoRegistro = 0; // tamanho de cada registro

        do
        {
            arqBin.read((char *)&tamanhoRegistro, sizeof(tamanhoRegistro));
            posInicial = arqBin.tellg();

            posProximo = tamanhoRegistro + posInicial;
            arqBin.seekg(posProximo);
            i++;

        } while (i <= k && posProximo <= tamTotal);

        // Calcula o tamanho do registro
        arqBin.seekg(posInicial);
        int pos = 0;

        char *buffer = new char[tamanhoRegistro];
        arqBin.read(buffer, tamanhoRegistro);

        std::string str = buffer;

        pos = str.find(",");
        registro.setID(str.substr(0, pos)); // id

        str = str.substr(pos + 1, str.length());

        pos = str.find_last_of("\"") + 1;
        registro.setText(str.substr(0, pos)); // text

        str = str.substr(pos + 1, str.length());

        pos = str.find(",");
        registro.setVotes(atoi(str.substr(0, pos).c_str())); // votes

        str = str.substr(pos + 1, str.length());

        pos = str.find(",");

        registro.setVersion(str.substr(0, pos)); // version
        str = str.substr(pos + 1, str.length());

        registro.setDate(str.substr(0, str.length())); // data

        // std::cout.write(buffer, tamanhoRegistro);
        // std::cout << std::endl;

        delete[] buffer;
        arqBin.close();
    }
    else
        std::cout << "Erro ao obter registro." << std::endl;
}

void leBinario(Registro *registro, int k)
{

    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        arqBin.seekg(0, arqBin.end);
        int tamTotal = arqBin.tellg();
        arqBin.seekg(0, arqBin.beg);
        std::string str = "";
        char *buffer = new char[NREGISTROS];
        int pos = 0;
        int i = 0;
        int cont = 0;

        for (int i = 0; i < k; i++)
        {
            pos = rand() % NREGISTROS + 0;
            arqBin.seekg(0, arqBin.end);
            arqBin.read(buffer, 320);
            str = buffer;

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
        }

        // while (i < k)
        // {
        //     int j = rand() % 3646475 + 0;
        //     while (getline(arqBin, str))
        //     {

        //         if (cont == j)
        //         {
        //             cout << "oi\n";
        //             pos = str.find(",");
        //             registro[i].setID(str.substr(0, pos)); // id

        //             str = str.substr(pos + 1, str.length());

        //             pos = str.find_last_of("\"") + 1;
        //             registro[i].setText(str.substr(0, pos)); // text

        //             str = str.substr(pos + 1, str.length());

        //             pos = str.find(",");
        //             registro[i].setVotes(atoi(str.substr(0, pos).c_str())); // votes

        //             str = str.substr(pos + 1, str.length());

        //             pos = str.find(",");

        //             registro[i].setVersion(str.substr(0, pos)); // version
        //             str = str.substr(pos + 1, str.length());

        //             registro[i].setDate(str.substr(0, str.length())); // data
        //             i++;
        //             break;
        //         }
        //         else
        //             cont++;

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

/// ALGORITMO DE ORDENAÇÃO - HEAPSORT ///

void heapify(Registro *list, int i, int tam)
{
    while (i < tam)
    {
        int filho = 2 * i + 1;
        if (filho < tam)
        {
            if (filho + 1 < tam && list[filho + 1].getVotes() > list[filho].getVotes())
            {
                filho++;
            }

            if (list[filho].getVotes() > list[i].getVotes())
            {
                trocaNo(list[i], list[filho]);
            }
        }
        i = filho;
    }
}

void build_heap(Registro *list, int tam)
{
    for (int i = tam / 2 - 1; i >= 0; i--)
    {
        heapify(list, i, tam);
    }
}

void heapSort_ordena(Registro *list, int tam)
{
    build_heap(list, tam);
    while (tam > 0)
    {
        trocaNo(list[0], list[tam - 1]);
        heapify(list, 0, tam - 1);
        tam--;
    }
}

void heapSort_time(Registro *list, int tam)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    heapSort_ordena(list, tam);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "/nTempo gasto na ordenação: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " segundos" << std::endl;
    std::fstream saidaTxt;
    saidaTxt.open("./data/saidaTxt.txt", std::ios_base::out | std::ios_base::app);
    if (saidaTxt.is_open())
    {

        std::string linha = "";

        linha = "Heapsort\nTempo gasto:  segundos\n";
        saidaTxt.write(linha.c_str(), sizeof(char) * linha.size());

        cout << "O arquivo de texto foi criado!" << endl;
    }
    saidaTxt.close();
}

/*
====================FIM HEAPSORT ============

*/

/// ALGORITMO DE ORDENAÇÃO - COMB SORT ///

int find_next(int gap)
{
    gap = (gap * 10) / 13;

    if (gap < 1)
        return 1;
    return gap;
}

void combSort_ordena(Registro *list, int tam)
{
    int gap = tam;
    bool switched = true;

    while (gap != 1 || switched == true)
    {
        gap = find_next(gap);

        switched = false;

        int i = 0;
        while (i < tam - gap)
        {
            if (list[i].getVotes() > list[i + gap].getVotes())
            {
                trocaNo(list[i], list[i + gap]);
                switched = true;
            }
            i++;
        }
    }
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

void combSort_time(Registro *list, int tam)
{

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    combSort_ordena(list, tam);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "/nTempo gasto na ordenação: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " segundos" << std::endl;
}
/*
===================FIM COMBSORT =======================

*/

void criaTabelaHash(Lista *listaReview)
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
        // acessaRegistro(n);
        menu();
    }
    else if (resp == 2)
    {
        cout << "Digite o numero de importacoes que deseja: ";
        int N = 0;
        cin >> N;
        Registro *registro = new Registro[N];
        for (int i = 0; i < N; i++)
            acessaRegistro(rand() % 3646475 + 0, registro[i]);
        // for (int i = 0; i < N; i++)
        // leBinario(registro, N); //le e salva na memoria principal os registros
        cout << "Digite a funçao que deseja acessar\n[1] Teste Importação\n[2] Ordenar Registros\nFunção: ";
        cin >> resp;
        if (resp == 1)
            testeImportacao(registro);
        else if (resp == 2)
        {
            std::cout << "Qual Ordendação voce deseja?\n[1] Quicksort\n[2] Heapsort\n[3] Combsort\nFunção: ";
            cin >> resp;
            if (resp == 1)
                quickSort_time(registro, N);
            else if (resp == 2)
                heapSort_time(registro, N);
            else if (resp == 3)
                combSort_time(registro, N);
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
