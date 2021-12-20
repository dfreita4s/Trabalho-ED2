#include <iostream>
#include <fstream>
#include <chrono>
#include "../inc/registro.h"

Registro::Registro(const std::string &caminhoArquivo, int N)
{
    this->registros = new std::string[N]; //chama o array para salvar na memoria principal os N registros
    setN(N);
    setRegistro(importaRegistros(N));
}

Registro::~Registro()
{
    //Destructor
    delete registros;
}

std::string Registro::getTerms(int i, std::string regist)
{ 
    std::string term = "";

    switch (i)
    {

    case 1: //nota
        int pos = regist.find_last_of("\"");
        int posfim = regist.substr(pos + 1).find(",");

        term = regist.substr(pos + 1, posfim);
        return term;
        break;

    case 2: //version

        int pos = regist.substr(regist.find("\"") + 1).find(",");
        term = regist.substr(pos, regist.find_last_of(","));
        return term;
        break;

    default:
        break;
    }
}

void Registro::setID(std::string)
{
}

void Registro::setN(int N)
{
    this->N = N;
}

int Registro::getN()
{
    return this->N;
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

void Registro::ordenaRegistros()
{
    quickSort_time(getRegistro(), getN());
}

/// ALGORITMO DE ORDENAÇÃO - QUICK SORT ///


void Registro::trocaNo(std::string &r1, std::string &r2)
{
    std::string aux = r1;
    r1 = r2;
    r2 = aux;
}

std::string Registro::pivoMediano(std::string *l, int inicio, int fim)
{
    int media = (inicio + fim) / 2;
    if (l[inicio] > l[fim])
        trocaNo(l[inicio], l[fim]);
    if (l[media] > l[fim])
        trocaNo(l[media], l[fim]);
    if (l[inicio] > l[media])
        trocaNo(l[inicio], l[media]);
    trocaNo(l[media], l[fim]);
    return l[fim];
}

int Registro::quickSort_particionaLista(std::string *list, int i, int j)
{

    int fim = j - 1;
    int init = i;
    std::string pivo = pivoMediano(list, i, j);

    while (true)
    {
        while (i < j && list[i] < pivo)
        {
            i = i + 1;
        }
        while (j >= init && list[j] > pivo)
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
void Registro::quickSort_ordena(std::string *list, int i, int k)
{
    if (i - k > 0)
    {
        int p = quickSort_particionaLista(list, i, k);
        quickSort_ordena(list, i, p);
        quickSort_ordena(list, p + 1, k);
    }
}

void Registro::quickSort_time(std::string *list, int n)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    quickSort_ordena(list, 0, n - 1);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "/nTempo gasto na ordenação: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " segundos" << std::endl;
}

/// ALGORITMO DE ORDENAÇÃO - HEAPSORT ///


void heapify(std::string *list, int i, int tam)
{
    while(i < tam)
    {
        int filho = 2*i + 1;
        if(filho < tam)
        {
            if(filho+1 < tam && list[filho+1] > list[filho]){
                filho++;
            }
            
            if(list[filho] > list[i]){
                trocaNo(list[i], list[filho]);
            }
        }
        i = filho;
    }

}

void build_heap(std::string *list, int tam)
{
    for(int i = tam/2-1; i >= 0; i--){
        heapify(list, i, tam);
    }
}

void heapSort_ordena(std::string *list, int tam)
{
    build_heap(list, tam);
    while(tam > 0)
    {
        trocaNo(list[0], list[tam-1]);
        heapify(list, 0, tam-1);
        tam--;
    }
}

void heapSort_time(std::string *list, int tam)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    heapSort_ordena(list, tam);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "/nTempo gasto na ordenação: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " segundos" << std::endl;
}

/// ALGORITMO DE ORDENAÇÃO - COMB SORT ///


int find_next(int gap)
{
    gap = (gap*10)/13;
 
    if (gap < 1)
        return 1;
    return gap;
}
 

void combSort_ordena(std::string *list, int tam)
{
    int gap = tam;
    bool switched = true;

    while (gap != 1 || switched == true)
    {
        gap = find_next(gap);

        switched = false;
 
        int i=0;
        while(i < tam-gap)
        {
            if (list[i] > list[i+gap])
            {
                trocaNo(list[i], list[i+gap]);
                switched = true;
            }
            i++;
        }
    }
}

void combSort_time(std::string *list, int tam){

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    combSort_ordena(list, tam);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "/nTempo gasto na ordenação: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count() << " segundos" << std::endl;

}

