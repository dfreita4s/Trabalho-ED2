#include <iostream>
#include <fstream>
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
            std::cout << lista[i].imprimeRegistros() << std::endl;
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
        int randm = rand() % 3646475 + 0;
        std::string str = "";
        int i, j, pos = 0;
        while (getline(arqBin, str))
        {
            if (randm == j)
            {

                while (i < k)
                {
                    pos = str.find(",");
                    registro[i].setID(str.substr(0, pos)); // id

                    str = str.substr(pos, str.length());

                    pos = str.find_last_of("\"");
                    registro[i].setText(str.substr(0, pos - 1)); // text

                    str = str.substr(pos + 1, str.length());

                    pos = str.find(",");
                    registro[i].setVotes(stoi(str.substr(0, pos))); // votes

                    str = str.substr(pos, str.length());

                    pos = str.find(",");
                    registro[i].setVersion(str.substr(0, pos)); // version

                    str = str.substr(pos, str.length());

                    pos = str.length();
                    registro[i].setVersion(str.substr(0, pos)); // data

                    i++;
                }

                randm = rand() % 3646475 + 0;
            }
            else
                j++;
            if (i == k - 1)
                break;
        }
        cout << "Diretório " << k << " não existe!" << endl;

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
        cin >> resp;
        Registro *registro = new Registro[resp];
        leBinario(registro, resp); //le e salva na memoria principal os registros
        cout << "Digite a funçao que deseja acessar\n[1] Teste Importação\n[2] Ordenar Registros\nFunção: ";
        cin >> resp;
        if (resp == 1)
            testeImportacao(registro);
        else if (resp == 2)
            registro->ordenaRegistros();
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
        cout << "Diretório " << k << " não existe!" << endl;
        arqBin.close();
    }
    else
    {
        cout << "Não foi possível abrir o arquivo!" << endl;
    }
}

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
