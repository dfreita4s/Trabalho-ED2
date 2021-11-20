#include <iostream>
#include <fstream>
#include "../inc/lista.h"

using namespace std;

int obterReview();

void menu(Lista* listaReview){

    cout<<"Menu:\nDigite o valor da função para acessa-la\n[1] Acessa Registro\n[2] Teste Importação\n[3] Sair\nFunção: ";
    int resp = 0;
    cin>>resp;
    if(resp == 1){
        int n = 0;
        cout<<"Digite o registro que deseja: ";
        cin>>n;
        listaReview->acessaRegistro(n);
        menu(listaReview);
    }else if(resp ==2){
        listaReview->testeImportacao();
        menu(listaReview);
    }else if(resp == 3){
        return;
    }else {
        cout<<"Por favor digite uma resposta válida!"<<endl;
        menu(listaReview);
    }
}

int main(int argc, char const *argv[])
{
    // Diretório completo para funcionar o Debug
    string caminhoArquivo = "./data/tiktok_app_reviews.csv"; // resolver probelma do caminho do arqv
    if (argc == 1)
        caminhoArquivo = "./data/tiktok_app_reviews.csv";
    else
        caminhoArquivo = argv[1]; // Corrigir

    Lista *listaReview = new Lista(caminhoArquivo);

    listaReview->obterReviews();
    
    menu(listaReview); //menu para o usuario
    

    // int n = 0;
    // while(n != -1)
    // {
    //     n = obterReview();
    //     listaReview->acessaRegistro(n);
    // };

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

void testeImportacao(int resp){
    
    string caminhoArquivo = "./data/tiktok_app_reviews.bin";
    if(resp == 1){
        ifstream dadosBin;
        dadosBin.open(caminhoArquivo, ios_base::in | ios_base::binary);
        while(dadosBin.end){
            
        }
        dadosBin.close();
    }
    else if(resp == 2){
    ofstream dadosSaida;
    dadosSaida.open("dados.txt", ios_base::out | ios_base::app);
    // executa a saida de 100 valores do .bin para o .txt
    dadosSaida.close();
    }
    else
    cout << "Opção Inválida";
}