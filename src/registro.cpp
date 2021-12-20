#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "../inc/registro.h"

Registro::Registro(const std::string &caminhoArquivo, int N)
{
    this->registros = new std::string[N]; //chama o array para salvar na memoria principal os N registros
    setN(N);
    setRegistro(importaRegistros(N));
}

Registro::Registro()
{
    //contrutor
}

Registro::~Registro()
{
    //Destructor
    delete registros;
}

std::string Registro::imprimeRegistros(){
    return ("ID: "+ getID()+"\nMensagem: "+ getText() +"\nVotos: "+std::to_string(getVotes())+"\nVersão: "+getVersion()+"\nData/Hora: "+getDate());
    // std::cout << "ID: " << getID() << std::endl;
    // std::cout << "Mensagem: \"" << getText() << "\"" <<std::endl;
    // std::cout << "Votos /\\: " << getVotes() << std::endl;
    // std::cout << "Versão do Aplicativo: " << getVersion() << std::endl;
    // std::cout << "Data/Hora: " << getDate() << std::endl;
    // std::cout << std::endl;
}

void Registro::setID(std::string id)
{
    this->review_id = id;
}
void Registro::setText(std::string text)
{
    this->review_text = text;
}
void Registro::setVersion(std::string version)
{
    this->app_version = version;
}
void Registro::setDate(std::string date)
{
    this->posted_date = date;
}
void Registro::setVotes(int votes)
{
    this->upvotes = votes;
}
std::string Registro::getID()
{
    return this->review_id;
}
std::string Registro::getText()
{
    return this->review_text;
}
std::string Registro::getVersion()
{
    return this->app_version;
}
std::string Registro::getDate()
{
    return this->posted_date;
}
int Registro::getVotes()
{
    return this->upvotes;
}

// std::string Registro::getTerms(int i, std::string regist)
// {
//     std::string term = "";

//     switch (i)
//     {

//     case 1: //nota
//         int pos = regist.find_last_of("\"");
//         int posfim = regist.substr(pos + 1).find(",");

//         term = regist.substr(pos + 1, posfim);
//         return term;
//         break;

//     case 2: //version

//         int pos = regist.substr(regist.find("\"") + 1).find(",");
//         term = regist.substr(pos, regist.find_last_of(","));
//         return term;
//         break;

//     default:
//         break;
//     }
// }

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

//realizar a ordenação desses registros, utilizando como chave de ordenação upvotes. Durante a ordenação, deverão ser computados o
//total de comparações de chaves e o total de movimentações de chaves. Além disso, o tempo de execução do algoritmo deverá ser medido.
//Para gerar as estatísticas de desempenho, você deverá executar os passos acima para M diferentes conjuntos de N registros aleatórios.
//Minimamente, utilize M=3. Ao final, compute as médias de cada uma das métricas (comparações, movimentações e tempo)

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

// void Registro::heapSort_ordena(int *list, int tam)
// {
//     //constroiHeap(v, n);
//     while (tam > 0)
//     {
//         troca(list[0], list[tam - 1]);
//         heapify(list, 0, tam - 1);
//         tam = tam - 1;
//     }
// }

// void heapSort_time(Review * list, int n)
// {
//     high_resolution_clock::time_point start = high_resolution_clock::now();
//     heapSort_ordena(list, 0, n - 1);
//     high_resolution_clock::time_point end = high_resolution_clock::now();
//     cout << "/nTempo gasto na ordenação: " << duration_cast<duration<double>>(start - end).count() << " segundos" << endl;
// }
