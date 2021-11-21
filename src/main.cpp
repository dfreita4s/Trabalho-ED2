#include <iostream>
#include <fstream>
#include "../inc/lista.h"

using namespace std;

int obterReview();

void menu(Lista* listaReview){

    cout<<"Menu:\nDigite o valore da função para acessa-la\n[1] Acessa Registro\n[2] Teste Importação\n[3] Sair\nFunção: ";
    int resp = 0;
    cin>>resp;
    if(resp == 1){
        int n = 0;
        cout<<"Digite o registro que deseja: ";
        cin>>n;
        listaReview->acessaRegistro(n);
        menu(listaReview);
    }else if(resp ==2){
        int n2 = 0;
        cout << "Agora informe se deseja a saida no console, digitando 1, ou em arquivo txt, digitando 2: \n";
        cin >> n2;
        listaReview->testeImportacao(n2);
        //listaReview->usaListaImportacao();
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
        
    else{
        caminhoArquivo = argv[1]; // Corrigir
    }
        

    Lista *listaReview = new Lista(caminhoArquivo);

    listaReview->obterReviews();
    
    menu(listaReview); //menu para o usuario
    


    delete listaReview;
    return 0;
}

