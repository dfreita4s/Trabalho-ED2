#include <iostream>
#include <fstream>
#include "../inc/lista.h"

using namespace std;

int obterReview();

int main(int argc, char const *argv[])
{
    // Diretório completo para funcionar o Debug
    string caminhoArquivo = "";
    if (argc == 1)
        caminhoArquivo = "";
    else
        caminhoArquivo = argv[1]; // Corrigir

    Lista *listaReview = new Lista(caminhoArquivo);

    listaReview->obterReviews();
    
    int n = 0;
    while(n != -1)
    {
        n = obterReview();
        listaReview->acessaRegistro(n);
    };

    delete listaReview;
    return 0;
}

int obterReview()
{
    std::cout << "Informe o registro que deseja exibir: ";
    int n;
    std::cin >> n;
    return n;
}