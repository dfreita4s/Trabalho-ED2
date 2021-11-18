#include <iostream>
#include <fstream>
#include "../inc/lista.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // Diretório completo para funcionar o Debug
    string caminhoArquivo;
    caminhoArquivo = "../data/tiktok_app_reviews.csv";
    
    Lista *listaReview = new Lista(caminhoArquivo);

    listaReview->obterReviews();

    listaReview->listarTodas();

   // listaReview->acessaRegistro(2);

    delete listaReview;

    return 0;
}