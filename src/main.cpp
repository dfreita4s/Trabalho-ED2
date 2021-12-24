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

void exportaHashing();
void exportaHashingOrdenacao();
int obterReview();
bool checaArqBin();
void criaTabelaHash(tabelaHash *, Registro *, int );
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
        cout << N << " registros foram importados\n";
    }

    else
        cout << "Não foi possível abrir o arquivo!" << endl;
}

// Faz cópia dos registros para usar nos testes
void copiaRegistro(Registro *registro, Registro *registro2, int N)
{
    for (int i = 0; i < N; i++)
    {
        registro[i].setID(registro2[i].getID());
        registro[i].setText(registro2[i].getText());
        registro[i].setVotes(registro2[i].getVotes());
        registro[i].setVersion(registro2[i].getVersion());
        registro[i].setDate(registro2[i].getDate());
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

void ordenacao()
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
    float tempoCombsort = 0;

    float tempoMediaQuicksort = 0;
    float tempoMediaHeapsort = 0;
    float tempoMediaCombsort = 0;

    float comparacoesMediaQuicksort = 0;
    float comparacoesMediaHeapsort = 0;
    float comparacoesMediaCombsort = 0;

    float movimentacoesMediaQuicksort = 0;
    float movimentacoesMediaHeapsort = 0;
    float movimentacoesMediaCombsort = 0;

    int comparacoesQuicksort = 0;
    int movimentacoesQuicksort = 0;

    int comparacoesHeapsort = 0;
    int movimentacoesHeapsort = 0;

    int comparacoesCombsort = 0;
    int movimentacoesCombsort = 0;

    int M = 3;
    std::fstream saida;
    saida.open("./data/saida.txt", std::ios_base::out | std::ios_base::app);
    if (saida.is_open())
    {
        for (int i = 0; i < M; i++)
        {
            int tam = dat[rand() % 5];
            Registro *registro = new Registro[tam];
            leBinario(registro, tam);

            Registro *registro2 = new Registro[tam];
            copiaRegistro(registro2, registro, tam);

            Registro *registro3 = new Registro[tam];
            copiaRegistro(registro3, registro, tam);

            cout << "Fazendo teste para " << tam << " números de registros" << endl;

            tempoQuicksort = sort.quickSort_time(registro2, tam, &comparacoesQuicksort, &movimentacoesQuicksort);
            delete [] registro2;
            tempoHeapsort = sort.heapSort_time(registro3, tam, &comparacoesHeapsort, &movimentacoesHeapsort);
            delete [] registro3;
            tempoCombsort = sort.combSort_time(registro, tam, &comparacoesCombsort, &movimentacoesCombsort);
            delete[] registro;

            tempoMediaQuicksort += tempoQuicksort;
            tempoMediaHeapsort += tempoHeapsort;
            tempoMediaCombsort += tempoCombsort;

            comparacoesMediaQuicksort += comparacoesQuicksort / 3;
            comparacoesMediaHeapsort += comparacoesHeapsort / 3;
            comparacoesMediaCombsort += comparacoesCombsort / 3;

            movimentacoesMediaQuicksort += movimentacoesQuicksort / 3;
            movimentacoesMediaHeapsort += movimentacoesHeapsort / 3;
            movimentacoesMediaCombsort += movimentacoesCombsort / 3;

            saida << "\n====Quicksort====" << endl;
            saida << "Estatisticas para " << tam << " números de registros" << endl;
            saida << "Tempo de execução: " << tempoQuicksort << " segundos" << endl;
            saida << "Número de comparações: " << comparacoesQuicksort << endl;
            saida << "Número de movimentações: " << movimentacoesQuicksort << endl;

            saida << "\n====Heapsort====" << endl;
            saida << "Estatisticas para " << tam << " números de registros" << endl;
            saida << "Tempo de execução: " << tempoHeapsort << " segundos" << endl;
            saida << "Número de comparações: " << comparacoesHeapsort << endl;
            saida << "Número de movimentações: " << movimentacoesHeapsort << endl;

            saida << "\n====Combsort====" << endl;
            saida << "Estatisticas para " << tam << " números de registros" << endl;
            saida << "Tempo de execução: " << tempoCombsort << " segundos" << endl;
            saida << "Número de comparações: " << comparacoesCombsort << endl;
            saida << "Número de movimentações: " << movimentacoesCombsort << endl;
        }
        saida << "======Média final das execuções======" << endl;
        saida << "====Quicksort====" << endl;
        saida << "Média tempo de execução: " << tempoMediaQuicksort << " segundos" << endl;
        saida << "Média túmero de comparações: " << comparacoesMediaQuicksort << endl;
        saida << "Média túmero de movimentações: " << movimentacoesMediaQuicksort << endl;

        saida << "====Heapsort====" << endl;
        saida << "Média tempo de execução: " << tempoMediaHeapsort << " segundos" << endl;
        saida << "Média túmero de comparações: " << comparacoesMediaHeapsort << endl;
        saida << "Média túmero de movimentações: " << movimentacoesMediaHeapsort << endl;

        saida << "====Combsort====" << endl;
        saida << "Média tempo de execução: " << tempoMediaCombsort << " segundos" << endl;
        saida << "Média túmero de comparações: " << comparacoesMediaCombsort << endl;
        saida << "Média túmero de movimentações: " << movimentacoesMediaCombsort << endl;
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
        ordenacao();

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
        cout << "Escolha\n[1] Teste de Importação\n[2] Módulo de teste - Parte 2";
        cin >> resp;

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
            std::cout << "Módulo de teste - Parte 2" << std::endl;
            exportaHashingOrdenacao();
            menu();
        }
    }
    else if (resp == 4)
    {
        return;
    }
    else if(resp == 5)
    {
        int n = 99;
        Registro *registro = new Registro[n];
        leBinario(registro,n);
        criaTabelaHash(registro,n);
        menu();
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
    criaTabelaHash(tab, reg, n);
    delete [] tab;
}

void criaTabelaHash(tabelaHash *tab, Registro *reg, int n)
{
    tabelaHash aux;
    int chave;
    std::string chaveOrig;
    for (int i = 0; i < n; i++)
    {
        if (retiraPontos(reg[i].getVersion()) != 0)
        {
            chave = retiraPontos(reg[i].getVersion());
            chaveOrig = reg[i].getVersion();
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
    int *i = new int [n];
    int *j = new int [n];
    aux.quickSort_time(tab, n, i, j);
    
    cout << "Tabela Hash criada com sucesso" << endl;
    aux.imprimeTabela(tab, n);
}

int retiraPontos(std::string versao)
{
    char removePonto[] = ".";
    int chave;
    if (versao == "00.0.0")
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

void exportaHashingOrdenacao()
{
    std::ofstream arquivoSaida;
    arquivoSaida.open("./data/teste.txt", std::ios_base::out | std::ios_base::app);
    if (arquivoSaida.is_open())
    {
        int n = 99;
        int N = 100;
        Registro *reg = new Registro[N];
        leBinario(reg, N);

        arquivoSaida << " === " << N << " registro importados. === " << std::endl;
        for (int i = 0; i < N; i++)
            arquivoSaida << reg[i].imprimeRegistros() << std::endl;
        
        arquivoSaida << std::endl;

        tabelaHash *tab = new tabelaHash[n];
        tabelaHash aux;

        criaTabelaHash(tab, reg, n);
        arquivoSaida << " === Tabela Hashing === " << std::endl;
        for(int i=0; i<n; i++)
            if(tab[i].consultaChave() != 0)
                arquivoSaida << "Versão " << tab[i].consultaChaveOrig() << " : " << tab[i].consultaContador() << std::endl;
        
        Ordenacao ordenacao;
        Registro *regQS = new Registro[N];
        Registro *regHS = new Registro[N];

        copiaRegistro(regQS, reg, N);
        copiaRegistro(regHS, reg, N);
        
        int movimentacoes=0, comparacoes=0;

        arquivoSaida << std::endl;
        arquivoSaida << " === Ordenação QuickSort === " << std::endl;
        float tempoQuicksort = ordenacao.quickSort_time(regQS, N, &comparacoes, &movimentacoes);
        for(int i=0; i<N; i++)       
            arquivoSaida << regQS[i].imprimeRegistros() << std::endl;
        delete [] regQS;

        arquivoSaida << std::endl;
        arquivoSaida << " === Ordenação HeapSort === " << std::endl;
        float tempoHeapsort = ordenacao.heapSort_time(regHS, N, &comparacoes, &movimentacoes);
        for(int i=0; i<N; i++)       
            arquivoSaida << regHS[i].imprimeRegistros() << std::endl;
        delete [] regHS;

        arquivoSaida << std::endl;
        arquivoSaida << " === Ordenação CombSort === " << std::endl;
        float tempoCombsort = ordenacao.combSort_time(reg, N, &comparacoes, &movimentacoes);
        for(int i=0; i<N; i++)       
            arquivoSaida << reg[i].imprimeRegistros() << std::endl;
        delete [] reg;

        delete [] tab;
    }
}