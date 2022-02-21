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
#include "../inc/arvoreVP.h"
#include "../inc/arvoreB.h"
#include "../inc/arvoreHuffman.h"

#define NREGISTROS 3646475

using namespace std;

void criaTabelaHash(tabelaHash *, Registro *, int);
void criaTabelaHash(Registro *, int);
int retiraPontos(std::string);
// Nova leitura/escrita binário

void menuParteTres();
void testaExec();
void buscaNoAVP(arvoreVP *, string);
void exportaHashing();
void exportaHashingOrdenacao();
int obterReview();
bool checaArqBin();
void criaTabelaHash(tabelaHash *, Registro *, int);
void criaTabelaHash(Registro *reg, int n);
// Nova leitura/escrita binário
int retornaRegistro(int);
std::string exibeRegistro(int);
arvoreVP *testeArvoreVP(int);

void leBinario(Registro *registro, int N)
{

    // pensei pra ler o review_text e saber o tamanho um for em cada catactere da linha e ir ate o caracter ser == \n
    std::ifstream arqBin;
    std::ifstream textBin;
    textBin.open("./data/textBin.bin", std::ios::binary);
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open() && textBin.is_open())
    {
        int randNum = 0;
        int tamanhoRegistro = 127;
        int posTexto = 0;
        char *id_buffer = new char[87];
        char *data_buffer = new char[20];
        char *versaoApp_buffer = new char[11];
        char *str = new char[1000000];
        int tamTexto = 0;
        int votos = 0;
        srand(time(NULL));

        arqBin.seekg(0, ios::beg);
        textBin.seekg(0, ios::beg);
        for (int i = 0; i < N; i++) // pega alguma linha aleatoria do regist e passa para o registro.cpp
        {

            randNum = rand() % NREGISTROS + 0;
            arqBin.seekg(tamanhoRegistro * randNum, ios::beg); // chegar no registro
            registro[i].setPos(tamanhoRegistro * randNum);

            arqBin.read(id_buffer, sizeof(char) * 86);
            registro[i].setID(id_buffer);

            arqBin.read((char *)(&votos), sizeof(int));
            registro[i].setVotes(votos);

            arqBin.read((char *)(&tamTexto), sizeof(int));
            arqBin.read((char *)(&posTexto), sizeof(int));

            textBin.seekg(posTexto, ios::beg);

            textBin.read(str, sizeof(char) * tamTexto);
            str[tamTexto] = '\0';
            registro[i].setText(str);

            arqBin.read(versaoApp_buffer, sizeof(char) * 10);
            registro[i].setVersion(versaoApp_buffer);

            arqBin.read(data_buffer, sizeof(char) * 19);

            registro[i].setDate(data_buffer);

            arqBin.seekg(0, ios::beg);
        }
        delete[] id_buffer;
        delete[] data_buffer;
        delete[] versaoApp_buffer;
        delete[] str;
        arqBin.close();
        textBin.close();
        std::cout << N << " registros foram importados\n";
    }

    else
        std::cout << "Não foi possível abrir o arquivo!" << std::endl;
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

void ordenacao()
{
    Ordenacao sort;
    srand(time(NULL));

    int *dat = new int[5]; // vetor com os valores de N
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

            std::cout << "Fazendo teste para " << tam << " números de registros" << std::endl;

            tempoQuicksort = sort.quickSort_time(registro2, tam, &comparacoesQuicksort, &movimentacoesQuicksort);
            delete[] registro2;
            tempoHeapsort = sort.heapSort_time(registro3, tam, &comparacoesHeapsort, &movimentacoesHeapsort);
            delete[] registro3;
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

            saida << "\n====Quicksort====" << std::endl;
            saida << "Estatisticas para " << tam << " números de registros" << std::endl;
            saida << "Tempo de execução: " << tempoQuicksort << " segundos" << std::endl;
            saida << "Número de comparações: " << comparacoesQuicksort << std::endl;
            saida << "Número de movimentações: " << movimentacoesQuicksort << std::endl;

            saida << "\n====Heapsort====" << std::endl;
            saida << "Estatisticas para " << tam << " números de registros" << std::endl;
            saida << "Tempo de execução: " << tempoHeapsort << " segundos" << std::endl;
            saida << "Número de comparações: " << comparacoesHeapsort << std::endl;
            saida << "Número de movimentações: " << movimentacoesHeapsort << std::endl;

            saida << "\n====Combsort====" << std::endl;
            saida << "Estatisticas para " << tam << " números de registros" << std::endl;
            saida << "Tempo de execução: " << tempoCombsort << " segundos" << std::endl;
            saida << "Número de comparações: " << comparacoesCombsort << std::endl;
            saida << "Número de movimentações: " << movimentacoesCombsort << std::endl;
        }
        saida << "======Média final das execuções======" << std::endl;
        saida << "====Quicksort====" << std::endl;
        saida << "Média tempo de execução: " << tempoMediaQuicksort << " segundos" << std::endl;
        saida << "Média túmero de comparações: " << comparacoesMediaQuicksort << std::endl;
        saida << "Média túmero de movimentações: " << movimentacoesMediaQuicksort << std::endl;

        saida << "====Heapsort====" << std::endl;
        saida << "Média tempo de execução: " << tempoMediaHeapsort << " segundos" << std::endl;
        saida << "Média túmero de comparações: " << comparacoesMediaHeapsort << std::endl;
        saida << "Média túmero de movimentações: " << movimentacoesMediaHeapsort << std::endl;

        saida << "====Combsort====" << std::endl;
        saida << "Média tempo de execução: " << tempoMediaCombsort << " segundos" << std::endl;
        saida << "Média túmero de comparações: " << comparacoesMediaCombsort << std::endl;
        saida << "Média túmero de movimentações: " << movimentacoesMediaCombsort << std::endl;
        std::cout << "O arquivo de texto foi criado!" << std::endl;
    }
    else
        std::cout << "Nao foi possivel abrir o arquivo" << std::endl;
    delete[] dat;
    saida.close();
}

void criaTabelaHash(Registro *reg, int n)
{
    tabelaHash *tab = new tabelaHash[n];
    criaTabelaHash(tab, reg, n);
    delete[] tab;
}

/*
    Importar N registros aleatorios do arquivo binario gerado pelo pre processamento e coloca-los na estrutura
    Computar o total de comparações de chaves e o tempo de execucao
    Realizar a busca de B registros aleatorios na estrutura deverao ser computados o tempo e o total de comparacoes


    M = 3
    N = 1000000
    B = 100

    Ao final, compute as médias de cada uma das métricas (comparações e tempo) obtidas para as M execuções.
    Salve todos os resultados obtidos em um arquivo saida.txt, contendo tanto os resultados individuais quanto a média final.

*/

void analiseEstruturas()
{
    srand(time(NULL));

    int comparacoesAVP = 0;
    int comparacoesAB20 = 0;
    int comparacoesAB200 = 0; // acho que nao precisa dessas variaveis, pode colocar so uma para AB

    int comparacoesBuscaAVP = 0;
    int comparacoesBuscaAB20 = 0;
    int comparacoesBuscaAB200 = 0;

    int comparacoesInserirAVP = 0;
    int comparacoesInserirAB20 = 0;
    int comparacoesInserirAB200 = 0;

    float tempoExecAVP = 0.0000f;
    float tempoExecAB20 = 0.0000f;
    float tempoExecAB200 = 0.0000f;

    float tempoBuscaAVP = 0.0000f;
    float tempoBuscaAB20 = 0.0000f;
    float tempoBuscaAB200 = 0.0000f;

    float tempoInserirAVP = 0.0000f;
    float tempoInserirAB20 = 0.0000f;
    float tempoInserirAB200 = 0.0000f;

    float mediaComparacoesAVP = 0.0000f;
    float mediaComparacoesAB20 = 0.0000f;
    float mediaComparacoesAB200 = 0.0000f;
    float mediaTempoExecAVP = 0.0000f;
    float mediaTempoExecAB20 = 0.0000f;
    float mediaTempoExecAB200 = 0.0000f;

    float mediaComparacoesInserirAVP = 0.0000f;
    float mediaComparacoesInserirAB20 = 0.0000f;
    float mediaComparacoesInserirAB200 = 0.0000f;

    float mediaComparacoesBuscaAVP = 0.0000f;
    float mediaComparacoesBuscaAB20 = 0.0000f;
    float mediaComparacoesBuscaAB200 = 0.0000f;

    float mediaTempoInserirAVP = 0.0000f;
    float mediaTempoInserirAB20 = 0.0000f;
    float mediaTempoInserirAB200 = 0.0000f;
    float mediaTempoBuscaAVP = 0.0000f;
    float mediaTempoBuscaAB20 = 0.0000f;
    float mediaTempoBuscaAB200 = 0.0000f;

    // int N = 1000000;
    int N = 1000000;
    int B = 100;

    std::fstream saida;
    saida.open("./data/saida.txt", std::ios_base::out | std::ios_base::app);
    if (saida.is_open())
    {
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;

        Registro *regEstrutura = new Registro[N];

        leBinario(regEstrutura, N); // importa N registros aleatorios
        // para AVP
        std::cout << "Arvore Vermelho-Preto\nTeste:[";
        for (int i = 0; i < 50; i++)
        {
            arvoreVP *AVP = new arvoreVP();
            start = std::chrono::high_resolution_clock::now();

            for (int j = 0; j < N; j++) // inserir registros na estrutura
                AVP->inserir(regEstrutura[j].getID(), regEstrutura[j].getPos(), &comparacoesInserirAVP);

            end = std::chrono::high_resolution_clock::now();
            tempoInserirAVP = std::chrono::duration<float>(end - start).count();

            start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < B; i++) // buscar B registros aleatorios
                AVP->buscaNo(AVP, regEstrutura[rand() % N + 0].getID(), &comparacoesBuscaAVP, 1);

            end = std::chrono::high_resolution_clock::now();
            tempoBuscaAVP = std::chrono::duration<float>(end - start).count();

            // escrever no txt os valores encontrados
            saida << "===========ARVORE VERMELHO-PRETO===========" << std::endl;
            saida << "Teste: " << (i + 1) << std::endl;
            saida << "Tempo de inserção: " << tempoInserirAVP << std::endl;
            saida << "Comparações inseção: " << comparacoesInserirAVP << std::endl;
            saida << "Tempo busca 100 registro aleatórios" << tempoBuscaAVP << std::endl;
            saida << "Comparacoes busca 100 registro aleatórios" << comparacoesBuscaAVP << std::endl
                  << std::endl;

            mediaTempoBuscaAVP += tempoBuscaAVP;
            mediaTempoInserirAVP += tempoInserirAVP;

            mediaComparacoesInserirAVP += comparacoesInserirAVP;
            mediaComparacoesBuscaAVP += comparacoesBuscaAVP;

            std::cout << "///";

            delete AVP; // delete arvore VP
        }

        mediaTempoBuscaAVP = mediaTempoBuscaAVP / 3;
        mediaTempoInserirAVP = mediaTempoInserirAVP / 3;

        mediaComparacoesInserirAVP = comparacoesInserirAVP / 3;
        mediaComparacoesBuscaAVP = comparacoesBuscaAVP / 3;

        std::cout << "] " << std::endl;
        // exit(0);
        // para Arvore B m = 20

        std::cout << "Arvore B (m = 20)\nTeste:[";
        for (int i = 0; i < 3; i++)

        {
            // arvoreB *arvoreB = new arvoreB(20);

            start = std::chrono::high_resolution_clock::now();
            // for(int j = 0; j < N; j++)
            // arvoreB->inserir(regEstrutura[i].getID(), regEstrutura[i].getPos());//inserir registros na estrutura
            end = std::chrono::high_resolution_clock::now();
            tempoInserirAB20 = std::chrono::duration<float>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            // for(int j = 0; j < N; j++)
            // buscar B registros aleatorios
            end = std::chrono::high_resolution_clock::now();
            tempoBuscaAB20 = std::chrono::duration<float>(end - start).count();

            // escrever no txt os valores encontrados
            saida << "===========ARVORE B (m = 20)===========" << std::endl;
            saida << "Teste: " << (i + 1) << std::endl;
            saida << "Tempo de inserção: " << tempoInserirAB20 << std::endl;
            saida << "Comparações inseção: " << comparacoesInserirAB20 << std::endl;
            saida << "Tempo busca 100 registro aleatórios" << tempoBuscaAB20 << std::endl;
            saida << "Comparacoes busca 100 registro aleatórios" << comparacoesBuscaAB20 << std::endl
                  << std::endl;

            mediaTempoBuscaAB20 += tempoBuscaAB20;
            mediaTempoInserirAB20 += tempoInserirAB20;

            mediaComparacoesInserirAB20 += comparacoesInserirAB20;
            mediaComparacoesBuscaAB20 += comparacoesBuscaAB20;

            std::cout << "///";
            // delete arvoreB;
        }

        mediaTempoBuscaAB20 = tempoBuscaAB20 / 3;
        mediaTempoInserirAB20 = tempoInserirAB20 / 3;

        mediaComparacoesBuscaAB20 = comparacoesBuscaAB20 / 3;
        mediaComparacoesInserirAB20 = comparacoesInserirAB20 / 3;

        std::cout << "]" << std::endl;

        // para Arvore B m = 200
        std::cout << "Arvore B (m = 200)\nTeste:[";
        for (int i = 0; i < 3; i++)

        {
            // ArvoreB *arvoreB = new ArvoreB(200);
            start = std::chrono::high_resolution_clock::now();
            // for(int j = 0; j < N; j++)
            //  arvoreB->inserir(regEstrutura[i].getID(), regEstrutura[i].getPos(), &comparacoesInserirAB20);//inserir registros na estrutura
            end = std::chrono::high_resolution_clock::now();
            tempoInserirAB200 = std::chrono::duration<float>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            // buscar B registros aleatorios
            end = std::chrono::high_resolution_clock::now();
            tempoBuscaAB200 = std::chrono::duration<float>(end - start).count();

            // escrever no txt os valores encontrados
            saida << "===========ARVORE B (m = 200)===========" << std::endl;
            saida << "Teste: " << (i + 1) << std::endl;
            saida << "Tempo de inserção: " << tempoInserirAB200 << std::endl;
            saida << "Comparações inseção: " << comparacoesInserirAB200 << std::endl;
            saida << "Tempo busca 100 registro aleatórios: " << tempoBuscaAB200 << std::endl;
            saida << "Comparacoes busca 100 registro aleatórios: " << comparacoesBuscaAB200 << std::endl
                  << std::endl;

            mediaTempoBuscaAB200 += tempoBuscaAB200;
            mediaTempoInserirAB200 += tempoInserirAB200;

            mediaComparacoesInserirAB200 += comparacoesInserirAB200;
            mediaComparacoesBuscaAB200 += comparacoesBuscaAB200;

            std::cout << "///";
            // delete arvoreB;
        }

        mediaTempoBuscaAB200 = tempoBuscaAB200 / 3;
        mediaTempoInserirAB200 = tempoInserirAB200 / 3;

        mediaComparacoesBuscaAB200 = comparacoesBuscaAB200 / 3;
        mediaComparacoesInserirAB200 = comparacoesInserirAB200 / 3;

        std::cout << "]" << std::endl;

        saida << "======Estatisticas de Desempenho======" << std::endl
              << std::endl;
        saida << "====Arvore Vermelho-Preto====" << std::endl
              << std::endl;
        saida << "Media tempo inserção: " << mediaTempoInserirAVP << std::endl;
        saida << "Media comparacoes inserção: " << mediaComparacoesInserirAVP << std::endl;
        saida << "Media tempo busca: " << mediaTempoExecAVP << std::endl;
        saida << "Media comparacoes busca: " << mediaComparacoesBuscaAVP << std::endl
              << std::endl;

        saida << "====Arvore B(m = 20)====" << std::endl
              << std::endl;
        saida << "Media tempo inserção: " << mediaTempoInserirAB20 << std::endl;
        saida << "Media comparacoes inserção: " << mediaComparacoesInserirAB20 << std::endl;
        saida << "Media tempo busca: " << mediaTempoExecAB20 << std::endl;
        saida << "Media comparacoes busca: " << mediaComparacoesBuscaAB20 << std::endl
              << std::endl;

        saida << "====Arvore B(m = 200)====" << std::endl
              << std::endl;
        saida << "Media tempo inserção: " << mediaTempoInserirAB200 << std::endl;
        saida << "Media comparacoes inserção: " << mediaComparacoesInserirAB200 << std::endl;
        saida << "Media tempo busca: " << mediaTempoExecAB200 << std::endl;
        saida << "Media comparacoes busca: " << mediaComparacoesBuscaAB200 << std::endl
              << std::endl;

        // escrever no txt
        delete[] regEstrutura;
    }
    else
        std::cout << "Não foi possivel abrir o arquivo!" << std::endl;
}

std::string juntaReviews(Registro *registro, int tam)
{ // funçao para juntar todos os reviews do registro em uma string so
    std::string texto = "";
    for (int i = 0; i < tam; i++)
        texto += registro[i].getText();
    return texto;
}

void estatisticasDesempenho()
{
    int M = 3;
    int valores[3] = {
        10000,
        100000,
        1000000};

    // teste para N = 10000
    int comparacoesPrimeiroTeste = 0;
    float mediaComparacoesPrimeiroTeste = 0.000f;
    float taxaCompressaoPrimeiroTeste = 0.000f;
    float mediaTaxaCompressaoPrimeiroTeste = 0.000f;

    // teste para N = 100000
    int comparacoesSegundoTeste = 0;
    float mediaComparacoesSegundoTeste = 0.000f;
    float taxaCompressaoSegundoTeste = 0.000f;
    float mediaTaxaCompressaoSegundoTeste = 0.000f;

    // teste para N = 1000000
    int comparacoesTerceiroTeste = 0;
    float mediaComparacoesTerceiroTeste = 0.000f;
    float taxaCompressaoTerceiroTeste = 0.000f;
    float mediaTaxaCompressaoTerceiroTeste = 0.000f;

    Registro *registro_1 = new Registro[valores[0]];
    Registro *registro_2 = new Registro[valores[1]];
    Registro *registro_3 = new Registro[valores[2]];

    leBinario(registro_1, valores[0]);
    leBinario(registro_2, valores[1]);
    leBinario(registro_3, valores[2]);

    std::fstream saida;
    saida.open("./data/saida.txt", std::ios_base::out | std::ios_base::app);
    if (saida.is_open())
    {

        saida << "========== Estatisticas de desempenho ==========\n";

        for (int i = 0; i < M; i++)
        {
            // Teste para n = 10000
            // aqui vai a funcao para comprimir o arquivo
            arvoreHuffman arv;
            arv.recebeReview(juntaReviews(registro_1, valores[0]));
            saida << " Teste N = 10000\n";
            saida << "  Comparacões: " << comparacoesPrimeiroTeste << std::endl;
            taxaCompressaoPrimeiroTeste = (arv.getTamIni()- arv.getTamFim())/arv.getTamIni();
            saida << "  Taxa de compressão: " << taxaCompressaoPrimeiroTeste << std::endl
                  << std::endl;
            mediaComparacoesPrimeiroTeste += comparacoesPrimeiroTeste; 
            mediaTaxaCompressaoPrimeiroTeste += taxaCompressaoPrimeiroTeste; 

            // Teste para n = 100000
            // aqui vai a funcao para comprimir o arquivo
            saida << " Teste N = 100000\n";
            saida << "  Comparacões: " << comparacoesSegundoTeste << std::endl;
            taxaCompressaoSegundoTeste = (arv.getTamIni()- arv.getTamFim())/arv.getTamIni();
            saida << "  Taxa de compressão: " << taxaCompressaoSegundoTeste << std::endl
                  << std::endl;
            mediaComparacoesSegundoTeste += comparacoesSegundoTeste; 
            mediaTaxaCompressaoSegundoTeste += comparacoesSegundoTeste; 

            // Teste para n = 1000000
            // aqui vai a funcao para comprimir o arquivo
            saida << " Teste N = 1000000\n";
            saida << "  Comparacões: " << comparacoesTerceiroTeste << std::endl;
            taxaCompressaoTerceiroTeste = (arv.getTamIni()- arv.getTamFim())/arv.getTamIni();
            saida << "  Taxa de compressão: " << taxaCompressaoTerceiroTeste << std::endl
                  << std::endl;
            mediaComparacoesTerceiroTeste += comparacoesTerceiroTeste; 
            mediaTaxaCompressaoTerceiroTeste += comparacoesTerceiroTeste; 

            // Escrever no saida.txt
        }

        saida << "=======Estatisticas de desempenho=======" << std::endl;
        saida << "== Para N = 10000 ==\n";
        saida << "Media comparações: " << mediaComparacoesPrimeiroTeste/3 << std::endl;
        saida << "Media taxa de compressão" << mediaTaxaCompressaoPrimeiroTeste/3 << std::endl;
        saida << "== Para N = 100000 ==\n";
        saida << "Media comparações: " << mediaComparacoesSegundoTeste/3 << std::endl;
        saida << "Media taxa de compressão" << mediaTaxaCompressaoSegundoTeste/3 << std::endl;
        saida << "== Para N = 1000000 ==\n";
        saida << "Media comparações: " << mediaComparacoesTerceiroTeste/3 << std::endl;
        saida << "Media taxa de compressão" << mediaTaxaCompressaoTerceiroTeste/3 << std::endl;
    }
    else
    {
        std::cout << "Erro ao abrir arquivo!" << std::endl;
        exit(0);
    }
    saida.close();
    delete[] registro_1;
    delete[] registro_2;
    delete[] registro_3;
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
            if (tab[aux.funcaoHash(chave, n)].consultaContador() == 0) // Caso a função hash encontre uma posição vazia na tabela para inserir a chave
            {
                tab[aux.funcaoHash(chave, n)].insereChave(chave);
                tab[aux.funcaoHash(chave, n)].insereChaveOrig(chaveOrig);
            }
            else if ((tab[aux.funcaoHash(chave, n)].consultaContador() != 0) && (tab[aux.funcaoHash(chave, n)].consultaChave() == chave)) // Caso a função hash encontre uma posição na tabela onde outro review com a mesma versão já tenha sido inserido
            {
                tab[aux.funcaoHash(chave, n)].somaContador();
            }
            else if ((tab[aux.funcaoHash(chave, n)].consultaContador() != 0) && (tab[aux.funcaoHash(chave, n)].consultaChave() != chave)) // Caso a função hash devolva uma posição da tabela não vazia e que a versão do review é diferente do já inserido, ocorre a colisão
            {
                int j = 0;
                while ((tab[aux.trataColisao(chave, n, j)].consultaContador() != 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() != chave)) // Enquanto a colisão persistir, índice j, que entra na função de tratamento de colisão, é somado
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
                // contaColisao++;
            }
        }
        else
        {
            // ignora review com versão vazia
        }
    }
    int qualquer;
    aux.quickSort_time(tab, n, &qualquer, &qualquer);

    std::cout << "Tabela Hash criada com sucesso" << std::endl;
    std::cout << aux.imprimeFrequentes(tab, n) << std::endl;
}

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
        // Salvar em um txt N = 100 registros aleatorios
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

void menu()
{

    cout << "Menu:\nDigite o valor da função para acessa-la\n[1] Comprimir N reviews e salva-los\n[2] Descomprimir o arquivo salvo\n[3] Sequencia de compressões\n[4] Sair \nFunção: ";
    int resp = 0;
    cin >> resp;
    arvoreHuffman arv;
    if (resp == 1) // comprimir N registros aleatórios definidos pelo usuário
    {
        std::cout << "Defina o numero de registros aleatórios para comprimir: ";
        std::cin >> resp;
        Registro *registro = new Registro[resp];
        leBinario(registro, resp);
        arv.recebeReview(juntaReviews(registro, resp));
        menu();
    }
    else if (resp == 2)
    {
        // aqui vai a funcao para descompactar o arquivo e salva-lo em um arquivo binario
        arv.traduzir(); //nao completa
        menu();
    }
    else if (resp == 3)
    {

        /*
         * Gerar estatisticas de desempenho para M = 3
         *computar as metricas comparacoes e taxa de compressao(olhar a formula nos slides)
         *computar tambem as medias das metricas em um arquivo saida.txt(individuais e media)
         */
        estatisticasDesempenho();
        menu();
    }
    else if (resp == 4)
    {
        exit(0);
    }
    else
    {
        cout << "Por favor digite uma resposta válida!" << endl;
        menu();
    }
}
void menuParteTres()
{
    int resp;
    cout << "Digite a opcao que deseja acessar: \n [1] Arvore Vermelho Preto \n [2] Arvore B \n [3] Sair \n"
         << endl;
    cin >> resp;

    // menu para gerar árvore vermelho e preto, além de seu relatório em txt
    if (resp == 1)
    {
        int resp2;
        cout << "Informe o numero de reviews que a arvore vermelho preto deve importar: \n"
             << endl;
        cout << "OBS: De 500 para baixo, sera exibido no console, acima disso so e acessado no relatorio txt" << endl;
        cin >> resp2;
        int aux = 0;
        float tempoExecucao;

        // inicializa variáveis
        arvoreVP *arVP = new arvoreVP();
        Registro *reg = new Registro[resp2];
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;

        leBinario(reg, resp2); // importa N registros aleatorios

        // realiza contagem de tempo de execução para gerar a árvore
        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < resp2; i++)
        {
            arVP->inserir(reg[i].getID(), reg[i].getPos(), &aux);
        }
        end = std::chrono::high_resolution_clock::now();
        tempoExecucao = std::chrono::duration<float>(end - start).count();

        // printa no console caso a árvore tenha menos de 500 reviews
        if (resp2 <= 500)
        {
            arVP->prettyPrint();
        }

        int resp3;
        cout << "Agora pressione [1] para gerar um relatorio ou [2] para procurar uma id de avaliacao \n"
             << endl;
        cin >> resp3;

        // gera relatório em txt com a árvore de tamanho n, digitada no console
        if (resp3 == 1)
        {
            std::fstream saida;
            saida.open("./data/relatorio_etapa3.txt", std::ios_base::out | std::ios_base::app);
            if (saida.is_open())
            {
                saida << "------------- RELATORIO ETAPA 3 - ARVORE VERMELHO PRETO -------------" << std::endl;
                saida << "Numero de reviews que usuario importou para a arvore: "
                      << " " << resp2 << std::endl;
                saida << "Numero de comparacoes realizadas durante as insercoes na arvore: "
                      << " " << aux << std::endl;
                saida << "Tempo gasto para gerar a arvore: "
                      << " " << tempoExecucao << "s" << std::endl;
                saida << "Numero de rotacoes realizadas pela arvore: "
                      << " " << arVP->contaRotacoes() << std::endl;
                saida << "A arvore gerada foi: " << std::endl;
                arVP->geraTxt();
                cout << "Relatorio ('relatorio_etapa3') txt salvo na pasta 'data' do projeto " << endl;
            }
            else
            {
                cout << "Nao foi possivel abrir o arquivo txt" << endl;
            }
            menuParteTres();
        }

        // usuário informa ID que deseja procurar na árvore
        else if (resp3 == 2)
        {
            string resp4;
            cout << "Informe agora o valor da ID que deseja procurar: \n"
                 << endl;
            cin >> resp4;
            arVP->buscaNo(arVP, resp4, &aux, 2);
            cout << "\n";
            menuParteTres();
        }

        // trata uso errado na navegação do menu
        else
        {
            cout << "Favor informar uma opcao valida \n"
                 << endl;
            menuParteTres();
        }

        delete arVP;
        delete[] reg;
    }

    // menu para gerar árvore B, além de seu relatório em txt
    else if (resp == 2)
    {
        int resp2;
        cout << "Informe a quantidade de reviews que serao importados: " << endl;
        cin >> resp2;
        int resp3;
        cout << "Agora, informe a ordem que a arvore B tera: \n"
             << endl;
        cin >> resp3;
        // chama função para criar árvore B de ordem indicada pelo teclado
        int resp4;
        cout << "Perfeito, agora digite [1] se deseja gerar um relatorio ou [2] se deseja buscar uma ID: \n"
             << endl;
        if (resp4 == 1)
        {
            // chama função para gerar relatório da árvore B
            cout << "arvore não implementada" << endl;
            menuParteTres();
        }
        else if (resp4 == 2)
        {
            int resp5;
            cout << "Informe a ID do review que deseja buscar na arvore: \n"
                 << endl;
            cin >> resp5;
            cout << "arvore não implementada" << endl;
            menuParteTres();
            // chama função para fazer a busca da ID digitada
        }
        else
        {
            cout << "Favor informar uma opcao valida \n"
                 << endl;
            menuParteTres();
        }
    }

    else if (resp == 3)
    {
        menu();
    }
    else
    {
        menuParteTres();
    }
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
        // listaReview->criarArquivoBinario(); // Criação do aquivo binário.
        // listaReview->criaTabelaHash();

        delete listaReview;
    }
    arvoreHuffman arv;
    arv.recebeReview("ABBB");


    arv.imprimeArvore();
    menu();
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
        arquivoSaida << " === Versões mais frequentes === " << std::endl;
        int qualquer;
        aux.quickSort_time(tab, n, &qualquer, &qualquer);
        arquivoSaida << aux.imprimeFrequentes(tab, n) << std::endl;

        Ordenacao ordenacao;
        Registro *regQS = new Registro[N];
        Registro *regHS = new Registro[N];

        copiaRegistro(regQS, reg, N);
        copiaRegistro(regHS, reg, N);

        int movimentacoes = 0, comparacoes = 0;

        arquivoSaida << std::endl;
        arquivoSaida << " === Ordenação QuickSort === " << std::endl;
        float tempoQuicksort = ordenacao.quickSort_time(regQS, N, &comparacoes, &movimentacoes);
        for (int i = 0; i < N; i++)
            arquivoSaida << regQS[i].imprimeRegistros() << std::endl;
        delete[] regQS;

        arquivoSaida << std::endl;
        arquivoSaida << " === Ordenação HeapSort === " << std::endl;
        float tempoHeapsort = ordenacao.heapSort_time(regHS, N, &comparacoes, &movimentacoes);
        for (int i = 0; i < N; i++)
            arquivoSaida << regHS[i].imprimeRegistros() << std::endl;
        delete[] regHS;

        arquivoSaida << std::endl;
        arquivoSaida << " === Ordenação CombSort === " << std::endl;
        float tempoCombsort = ordenacao.combSort_time(reg, N, &comparacoes, &movimentacoes);
        for (int i = 0; i < N; i++)
            arquivoSaida << reg[i].imprimeRegistros() << std::endl;
        delete[] reg;

        delete[] tab;
    }
}

// Modificações Leitura/Escrita Binário

int retornaRegistro(int k)
{
    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        arqBin.seekg(0, arqBin.end);
        int tamTotal = arqBin.tellg();
        arqBin.seekg(0, arqBin.beg);

        int posInicial = 0, posProximo = 0; // Ponteiro no arquivo
        int i = 0;                          // Contador de linhas
        unsigned short tamanhoRegistro = 0;
        unsigned short tamanhoReviewText = 0; // tamanho de cada texto

        posProximo += sizeof(double);

        do
        {
            arqBin.seekg(posProximo + 86);
            arqBin.read((char *)&tamanhoReviewText, sizeof(unsigned short));

            tamanhoRegistro = (86 + 2 * sizeof(int) + 19 + sizeof(short) + tamanhoReviewText);
            posProximo += tamanhoRegistro;
            i++;

        } while (i <= k);

        arqBin.seekg(posProximo);

        arqBin.close();
        return posProximo;
    }
    else
        std::cout << "Erro ao ler arquivo." << std::endl;

    return -1;
}

std::string exibeRegistro(int posicao)
{
    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);

    if (arqBin.is_open())
    {
        arqBin.seekg(posicao);
        char *buffer = new char[86];
        arqBin.read(buffer, sizeof(char) * 86);
        std::string reviewID(buffer);
        // std::cout << arqBin.tellg() << ": " << reviewID << std::endl;
        delete[] buffer;

        return reviewID;
    }
    else
    {
        std::cout << "Não foi possivel abrir o arquivo";
        return "";
    }
}