#include<iostream>
#include "../inc/lista.h"
#include <string>
#include <fstream>
#include<sstream>
#include <vector>
#include <chrono>

Lista::Lista(const std::string &caminhoArquivo)
{
    this->raiz = nullptr;
    this->abrirArquivo(caminhoArquivo);
}

Lista::~Lista()
{
    while (this->raiz != nullptr)
    {
        Review *novaRaiz = raiz->obterProximo();
        delete this->raiz;
        this->raiz = novaRaiz;
    }
    this->arquivo.close();
}

bool Lista::abrirArquivo(const std::string &caminhoArquivo)
{
    try
    {
        this->arquivo.open(caminhoArquivo, std::ios::in);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Houve um erro ao abrir o arquivo!" << std::endl
                  << e.what() << '\n';
    }
    return false;
}

int Lista::obterTam()
{
    int size = 0;
    if (this->arquivo.is_open())
    {
        if (this->obterRaiz() != nullptr)
        {
            Review *No = this->raiz;
            while (No->obterProximo() != nullptr)
            {
                size++;
                No = No->obterProximo();
            }
            return size;
        }
        else
        {
            return 0;
        }
    }
    return -1;
}

bool Lista::obterReviews()
{
    if (this->arquivo.is_open())
    {
        std::string linha;
        getline(this->arquivo, linha); //Le cabecalho do arquivo
        Review *ultimo = nullptr;

        getline(this->arquivo, linha);

        int k = 0; // contar registros

        while (!arquivo.eof() && linha != "")
        {
            /* Trata os registros que estão com '\n'
               Verifica se a última informação é do tipo ':SS' */

            while (!(isdigit(linha[linha.length() - 1]) && (isdigit(linha[linha.length() - 2])) && (linha[linha.length() - 3] == ':')))
            {
                std::string aux = linha;
                getline(this->arquivo, linha);
                aux.append(linha);
                linha = aux;
            }

            k++;

            int pos;
            pos = linha.find(",");
            std::string id = linha.substr(3, pos - 3); // Inicio em 3 para retirar 'gp:'

            linha = linha.substr(pos + 1, linha.length());

            pos = linha.find_last_of(",");
            std::string data = linha.substr(pos + 1); // Obter a Data
            linha = linha.substr(0, pos);

            pos = linha.find_last_of(",");
            std::string versao = linha.substr(pos + 1); // Obter a versão
            if (versao.length() == 0)
                versao = "NaN";
            linha = linha.substr(0, pos);

            pos = linha.find_last_of(",");
            int upvotes = stod(linha.substr(pos + 1)); // Obter upvotes
            linha = linha.substr(0, pos);

            std::string texto = linha; // Obter o comentário
            if (texto.find("\"") != -1)
                texto = texto.substr(1, texto.length() - 2); // Caso comece com esteja entre "", retirá-los

            Review *review = new Review(id, texto, upvotes, versao, data); // Cria o Review
            this->inserirReview(review, ultimo);                           // Insere na lista
            ultimo = review;                                               // Atualiza ponteiro do último Review para o atual.

            getline(this->arquivo, linha);
        }
        std::cout << k - 1 << " de registros foram importados com sucesso." << std::endl;
        criarArquivoBinario();
        return true;
    }
    std::cout << "Ocorreu um erro ao ler os dados." << std::endl;
    return false;
}

void Lista::inserirReview(Review *rev, Review *ultimo)
{
    if (!(this->raiz == nullptr))
        ultimo->setarProximo(rev);
    else
        this->raiz = rev;
}

Review *Lista::obterRaiz()
{
    if (!(this->raiz == nullptr))
        return this->raiz;
    else
    {
        return nullptr;
        std::cout << "Lista vazia." << std::endl;
    }
}

// Listar todos Reviews presentes na Lista.
void Lista::listarTodas()
{
    if (this->arquivo.is_open())
    {
        if (this->obterRaiz() != nullptr)
        {
            Review *No = this->raiz;
            while (No->obterProximo() != nullptr)
            {
                std::cout << std::endl;
                No->exibeRegistro();
                No = No->obterProximo();
            }
        }
        else
            std::cout << "Lista vazia." << std::endl;
    }
    else
        std::cout << "Impossível listar. O arquivo não existe." << std::endl;
}



bool Lista::criarArquivoBinario()
{
    std::ofstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if(arqBin.is_open())
    {
        if(this->obterRaiz() == nullptr)
            return false;

        Review *No = this->obterRaiz();

        // Escreve cabeçalho
        std::string linha = "review_id,review_text,upvotes,app_version,posted_date\n";
        arqBin.write(linha.c_str() , sizeof(char)*linha.size());
        int contador = 0;
        while(No != nullptr)
        {
            linha = "";
            linha += No->obterID();
            linha += ",\"";
            linha += No->obterTexto();
            linha += "\",";
            linha += std::to_string(No->obterVotos());
            linha += ",";
            linha += No->obterVersao();
            linha += ",";
            linha += No->obterData();
            linha += "\n";

            arqBin.write(linha.c_str() , sizeof(char)*linha.size());

            No = No->obterProximo();            
        }
        arqBin.close();
        std::cout << "O arquivo binário foi criado." << std::endl;    
        return true;
    }
    std::cout << "Erro ao criar arquivo binário." << std::endl;
    return false;
}



/// ALGORITMO DE ORDENAÇÃO - QUICK SORT ///

//realizar a ordenação desses registros, utilizando como chave de ordenação upvotes. Durante a ordenação, deverão ser computados o 
//total de comparações de chaves e o total de movimentações de chaves. Além disso, o tempo de execução do algoritmo deverá ser medido.
//Para gerar as estatísticas de desempenho, você deverá executar os passos acima para M diferentes conjuntos de N registros aleatórios.
//Minimamente, utilize M=3. Ao final, compute as médias de cada uma das métricas (comparações, movimentações e tempo)

int Lista::trocaNo(Review& r1, Review& r1){
    Review aux = r1;
    r1 = r2;
    r2 = aux;   
}

Review Lista::pivoMediano(Review *l, int inicio, int fim){
    int media = (inicio+fim)/2;
    if(l[inicio]>l[fim])
        trocaNo(l[inicio], l[fim]);
    if(l[media]>l[fim])
        trocaNo(l[media], l[fim]);
    if(l[inicio]>l[media])
        trocaNo(l[inicio], l[media]);
    troca(l[media],l[fim]);
    return l[fim];
}

int Lista::quickSort_particionaLista(Review* list, int i, int j){

    int fim = j-1;
    int init = i;
    Review pivo = pivoMediano(list, i, j);

    while(true){
        while (i < j && list[i] < pivo){
            i = i + 1;
        }
        while (j >= init && list[j] > PIVÔ){
            j = j-1;    
        }
        if(i<=j){
            trocaNo(list[i],list[j])
            i = i+1;
            j = j-1;
        }
       else
            break;
    trocaNo(list[i], list[j])
   return i;
 }

 void Lista::quickSort_ordena(Review *list, int i, int k){
    if(i-k > 0){
        p = quickSort_particionaLista(list, i, k);
        quickSort_ordena(list, i, p);
        quickSort_ordena(list, p+1, k);  
    }
 }

void quickSort_time(Review *list, int n)
{
    high_resolution_clock::time_point start = high_resolution_clock::now();
    quickSort_ordena(list, 0, n-1);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    cout << "/nTempo gasto na ordenação: " << duration_cast<duration<double>>(start - end).count() << " segundos" << endl;
}

/// ALGORITMO DE ORDENAÇÃO - HEAPSORT ///

void Lista::heapSort_ordena(int *list, int tam)
{
    //constroiHeap(v, n);
    while(tam > 0)
    {
        troca(list[0], list[tam-1]);
        heapify(list, 0, tam-1);
        tam = tam-1;
    }
}

void heapSort_time(Review *list, int n)
{
    high_resolution_clock::time_point start = high_resolution_clock::now();
    heapSort_ordena(list, 0, n-1);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    cout << "/nTempo gasto na ordenação: " << duration_cast<duration<double>>(start - end).count() << " segundos" << endl;
}
