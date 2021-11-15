#include <iostream>
#include <fstream>
#include "../inc/lista.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // Diretório completo para funcionar o Debug
    string caminhoArquivo;
    caminhoArquivo = "";
    
    Lista *listaReview = new Lista(caminhoArquivo);

    listaReview->obterReviews();

    //listaReview->listarTodas();

    delete listaReview;

    return 0;
}