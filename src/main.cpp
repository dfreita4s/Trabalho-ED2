#include <iostream>
#include <fstream>
#include "../inc/lista.h"

using namespace std;

int obterReview();
void testeImportacao();
void acessaRegistro(int);
bool checaArqBin();
char* leBinario(int);

string leBinary(int k){
    
    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if(arqBin.is_open()){
        arqBin.seekg(0, arqBin.end);
        int tamTotal = arqBin.tellg();
        arqBin.seekg(0, arqBin.beg);
        char *buffer = new char[tamTotal];
        std::string str = "";
        int cont = 0;
        while(getline(arqBin, str)){
            if(cont == k){
                return str +"\n";
            }
            else cont++;
        }
        arqBin.close();

        
    }
}


void menu()
{

    cout << "Menu:\nDigite o valor da função para acessa-la\n[1] Acessa Registro\n[2] Teste Importação\n[3] Sair\nFunção: ";
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

        testeImportacao();
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

int main(int argc, char const *argv[])
{
    if(!checaArqBin())
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
        listaReview->obterReviews(); // Leitura e armazenamento dos dados.
        listaReview->criarArquivoBinario(); // Criação do aquivo binário.
        delete listaReview;
    }

    menu();

    return 0;
}

bool checaArqBin()
{
    ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if(arqBin.is_open())
    {
        std::cout << "O arquivo binário existe." << std::endl;
        return true;
    }
    return false;
}
char* leBinario(int k) //le e retorna a k-ésima linha
{   
    std::string registro = "";
    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        arqBin.seekg(0, arqBin.end);
        int tamTotal = arqBin.tellg();
        arqBin.seekg(0, arqBin.beg);

        char *aux = new char;                                  // ponteiro auxiliar
        int posInicial = 0, posFinal = 0, tamanhoRegistro = 0; // Ponteiro no arquivo
        int i = 0;                                             // Contador de linhas

        do
        {
            /* Como a estrutura não possui tamanho fixo, 
                lê um a um até '\n' para calcular o tamanho de cada registro.
            */
            posInicial = arqBin.tellg();

            while (*aux != '\n')
                arqBin.read(aux, 1);

            posFinal = arqBin.tellg();
            arqBin.read(aux, 1);
            i++;

        } while (i < k && posFinal <= tamTotal);

        if (posFinal > tamTotal)
            std::cout << "O valor informado não é válido.";
        else
        {
            tamanhoRegistro = posFinal - posInicial; // Calcula o tamanho do registro
            arqBin.seekg(posInicial);

            char *buffer = new char[tamanhoRegistro];
            arqBin.read(buffer, tamanhoRegistro);

            // string str(buffer);
            // return buffer;
            
            return buffer;    
            delete[] buffer;
        }

        delete aux;
        arqBin.close();
        
    }
    else
        std::cout << "Erro ao obter registro." << std::endl;
}



void acessaRegistro(int k)
{
    std::cout << "Acessando registro " << k << std::endl;
    std::cout << leBinary(k);
}

void testeImportacao()
{
    int resp, N = 0;
    std::cout << "Deseja exibir a saida no console ou salva-la em um arquivo texto? 1 para no console 2 para salvar.:";
    std::cin>>resp;
    if (resp == 1)
    {
        // Printar no terminal N = 10 registros aleatorios
        N = 10;
        for (int i = 0; i < 10; i++)
            std::cout << leBinary(rand() % 3646475 + 0) << std::endl;
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
                linha = leBinary(rand() % 3646475 + 0);
                saidaTxt.write(linha.c_str(), sizeof(char)*linha.size());
            }
            
        }
        saidaTxt.close();
    }
    else
    {
        std::cout << "Por favor, digite um valor válido!" << std::endl;
    }
}