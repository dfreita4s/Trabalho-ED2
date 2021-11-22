#include <iostream>
#include <fstream>
#include "../inc/lista.h"

using namespace std;

int obterReview();
void acessaRegistro(int);

void menu(Lista* listaReview){

    cout<<"Menu:\nDigite o valore da função para acessa-la\n[1] Acessa Registro\n[2] Teste Importação\n[3] Sair\nFunção: ";
    int resp = 0;
    cin>>resp;
    if(resp == 1){
        int n = 0;
        cout<<"Digite o registro que deseja: ";
        cin>>n;
        acessaRegistro(n);
        menu(listaReview);
    }else if(resp ==2){
        
        listaReview->testeImportacao();
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
    {
        std::cout << "Nenhum aquivo foi passado como argumento." << std::endl;
        return -1;
    }
    else
        caminhoArquivo = argv[1];
        

    Lista *listaReview = new Lista(caminhoArquivo);

    listaReview->obterReviews();
    
    menu(listaReview); //menu para o usuario
    


    delete listaReview;
    return 0;
}


void acessaRegistro(int k)
{
    std::cout << "Acessando registro " << k << std::endl;
    
    std::ifstream arqBin;
    arqBin.open("./data/tiktok_app_reviews.bin", std::ios::binary);
    if (arqBin.is_open())
    {
        arqBin.seekg(0,arqBin.end);
        int tamTotal = arqBin.tellg();
        arqBin.seekg(0,arqBin.beg);

        char * aux = new char; // ponteiro auxiliar
        int posInicial=0, posFinal=0, tamanhoRegistro=0; // Ponteiro no arquivo
        int i = 0; // Contador de linhas

        do
        {
            /* Como a estrutura não possui tamanho fixo, 
                lê um a um até '\n' para calcular o tamanho de cada registro.
            */
            posInicial = arqBin.tellg();

            while(*aux != '\n')
                arqBin.read(aux, 1);
                
            posFinal = arqBin.tellg();
            arqBin.read(aux, 1);
            i++;

        } while(i<k && posFinal <= tamTotal );

        if (posFinal > tamTotal)
            std::cout << "O valor informado não é válido.";
        else
        {
            tamanhoRegistro = posFinal - posInicial; // Calcula o tamanho do registro
            arqBin.seekg(posInicial);

            char * buffer = new char[tamanhoRegistro];
            arqBin.read(buffer, tamanhoRegistro);

            std::cout.write(buffer, tamanhoRegistro);
            std::cout << std::endl;
            delete [] buffer;
        }

        delete aux;
        arqBin.close();
    }
    else
        std::cout << "Erro ao obter registro." << std::endl;
}