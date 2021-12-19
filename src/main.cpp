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
bool checaArqBin();
void criaTabelaHash(Lista *lista);
bool confereNum(int *num, int i);
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

bool confereNum(int *num, int i) // função avisa quando um número randômico é gerado mais de uma vez
{
    for (int j = i-1; j >= 0; j--)
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

void criaTabelaHash(Lista *listaReview)
{
        int n = 499;
        tabelaHash *tab = new tabelaHash[n];
        tabelaHash aux;
        int contaColisao = 0;
        srand(time(NULL));
        int *num = new int [n];
        for (int i = 0; i < n; i++){
            //cout << "Na execucao " << " " << i << endl;
            num[i] = rand() % 3646475;
            if (confereNum(num,i) == true) // garante que um mesmo review não seja lido mais de uma vez
            {
                int chave = listaReview->pegaVersao(num[i]);
                if (chave != 0) //será 0 caso o review retorne versão vazia
                {
                    if (tab[aux.funcaoHash(chave, n)].consultaContador() == 0)
                    {
                        tab[aux.funcaoHash(chave,n)].insereChave(chave);
                        cout << "Chave" << " " <<  tab[aux.funcaoHash(chave,n)].consultaChave() << " " <<"inserida com sucesso na posicao " << " " << aux.funcaoHash(chave,n) << " " << endl;
                    }
                    else if ((tab[aux.funcaoHash(chave, n)].consultaContador() != 0) && (tab[aux.funcaoHash(chave, n)].consultaChave() == chave))
                    {
                        tab[aux.funcaoHash(chave,n)].somaContador();
                        cout << "Repeticao da chave " << " " << tab[aux.funcaoHash(chave, n)].consultaChave() << " " << "detectada" << endl;
                        cout << "Contador somado, agora ele eh: " << " " << tab[aux.funcaoHash(chave,n)].consultaContador() << endl;
                    }
                    else if ((tab[aux.funcaoHash(chave, n)].consultaContador() != 0) && (tab[aux.funcaoHash(chave, n)].consultaChave() != chave))
                    {
                        int j = 0;
                        while ((tab[aux.trataColisao(chave, n, j)].consultaContador() != 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() != chave))
                        {
                            j++;
                        }
                        if ((tab[aux.trataColisao(chave, n, j)].consultaContador() != 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() == chave))
                        {
                            tab[aux.trataColisao(chave, n, j)].somaContador();
                            cout << "repeticao via colisao detectada, versao" << " " << chave << " " << "teve seu contador somado para" << " " << tab[aux.trataColisao(chave, n, j)].consultaContador() << endl;
                        }
                        else if ((tab[aux.trataColisao(chave, n, j)].consultaContador() == 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() != chave))
                        {
                            tab[aux.trataColisao(chave, n , j)].insereChave(chave);
                            cout << "colisao detectada e chave" << " " << chave << " " << "tratada e inserida na posicao" << " " << aux.trataColisao(chave, n, j) << endl;
                        }
                        //cout << "Deu colisao" << endl;
                        contaColisao++;
                        //aux.transformaBase(chave, i);
                        //cout << chave << endl;
                        //cout << "Colisao detectada e tratada..." << " " << "na posicao " << " " << i << " " << "da tabela "<< endl;
                        //cout << "Sua nova posicao via trataColisao eh " << " " << aux.trataColisao(chave,n,j) << " " << ", com a versao" << " " << tab[aux.trataColisao(chave,n,j)].consultaChave() << endl;  
                    }
                }
                else
                {
                    // ignora review com versão vazia
                }
            }
        }
    cout << "Tabela Hash criada com sucesso," << " " << contaColisao << " " << "colisoes aconteceram" << endl;
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
        //listaReview->criarArquivoBinario(); // Criação do aquivo binário.
        //listaReview->criaTabelaHash();
        
        delete listaReview;
    }

    menu();

    return 0;
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