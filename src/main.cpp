#include <iostream>
#include <fstream>
#include "../inc/lista.h"
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

int obterReview();
void testeImportacao();
void acessaRegistro(int);
void criaTabelaHash(Lista *lista);
bool checaArqBin();
string leBinario(int);

string leBinario(int k)
{

    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        arqBin.seekg(0, arqBin.end);
        int tamTotal = arqBin.tellg();
        arqBin.seekg(0, arqBin.beg);
        char *buffer = new char[tamTotal];
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
        cout << "Diretório " << k << " não existe!" << endl;
        return "";
        arqBin.close();
    }
    else
    {
        cout << "Não foi possível abrir o arquivo!" << endl;
        return "";
    }
}

void menu()
{

    cout << "Menu:\nDigite o valor da função para acessa-la\n[1] Acessa Registro\n[2] Teste Importação\n[3] Ordena Tabela Hash\n[4] Sair\nFunção: ";
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
        else{
            caminhoArquivo = argv[1];
        }
        Lista *listaReview = new Lista(caminhoArquivo);
        listaReview->obterReviews();        // Leitura e armazenamento dos dados.
        criaTabelaHash(listaReview);
        delete listaReview;
    }

    menu();

    return 0;
}

//cria tabela hash de n = 500 posições randômicas da lista de reviews

void criaTabelaHash(Lista *listaReview)
{
        int n = 500;
        tabelaHash *tab = new tabelaHash[n*2];
        tabelaHash aux;
        int novaPosicao;
        srand(time(NULL));
        int *num = new int [n];
        for (int i = 0; i < n; i++){
            //cout << "Na execucao " << " " << i << endl;
            num[i] = rand() % 3646475;
            int chave = listaReview->pegaVersao(num[i], i);
            if (tab[aux.funcaoHash(chave, n)].consultaChave() == 0)
            {
                tab[aux.funcaoHash(chave,n)].insereChave(chave);
                cout << tab[aux.funcaoHash(chave,n)].consultaChave() << "" << "incluida na posicao" << " " << i << " " << "da lista" << endl;
            }
            else if ((tab[aux.funcaoHash(chave, n)].consultaChave() != 0) && (tab[aux.funcaoHash(chave, n)].consultaChave() == chave))
            {
                tab[aux.funcaoHash(chave,n)].somaContador();
                cout << "Repeticao da chave " << " " << tab[aux.funcaoHash(chave, n)].consultaChave() << " " << "detectada" << endl;
                cout << "Contador somado, agora ele eh: " << " " << tab[aux.funcaoHash(chave,n)].consultaContador() << endl;
            }
            else 
            {
                int j = 0;
                while (tab[aux.trataColisao(chave, n, j)].consultaContador() != 0)
                {
                    j++;
                }
                tab[aux.trataColisao(chave,n,j)].insereChave(chave);
                cout << chave << endl;
                cout << "Colisao detectada e tratada..." << " " << "na posicao " << " " << i << " " << "da tabela "<< endl;
                cout << "Sua nova posicao via trataColisao eh " << " " << aux.trataColisao(chave,n,j) << " " << ",com a versao" << " " << tab[aux.trataColisao(chave,n,j)].consultaChave() << endl;  
            }
        }
    cout << "Tabela Hash criada com sucesso" << endl;
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
    std::string registro = leBinario(k);
    if (registro != "")
        std::cout << registro;
}

void testeImportacao()
{
    int resp, N = 0;
    std::cout << "Deseja exibir a saida no console ou salva-la em um arquivo texto? 1 para no console 2 para salvar.:";
    std::cin >> resp;
    if (resp == 1)
    {
        // Printar no terminal N = 10 registros aleatorios
        N = 10;
        for (int i = 0; i < 10; i++)
            std::cout << leBinario(rand() % 3646475 + 0) << std::endl;
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
                linha = leBinario(rand() % 3646475 + 0);
                saidaTxt.write(linha.c_str(), sizeof(char) * linha.size());
            }
            cout<<"O arquivo de texto foi criado!"<<endl;
        }
        saidaTxt.close();
    }
    else
    {
        std::cout << "Por favor, digite um valor válido!" << std::endl;
    }
}