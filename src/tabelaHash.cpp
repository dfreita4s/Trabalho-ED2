#include "../inc/tabelaHash.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <string>
#include <sstream>
#include <cstring>
#include <algorithm>
//#include <vector>

tabelaHash::tabelaHash(int chave){
    this->chave = chave;
    this->cont = 0;
}

tabelaHash::tabelaHash(){
    this->chave = 0;
    this->cont = 0;
    this->chaveOrig = "0";
}


/*
enum FuncaoHash
{
    DIVISAO,
    ENLACAMENTO_SEPARADO,
    ENLACAMENTO_LIMITE,
    MULTIPLICACAO,
    MEIO_QUADRADO,
    EXTRACAO,
    TRANSFORMACAO_BASE,
    ANALISE_DIGITOS,
    HASHING_UNIVERSAL
};
*/

/*
enum TratamentoColisao
{
    SONDAGEM_LINEAR,
    SONDAGEM_QUADRATICA,
    DUPLO_HASHING,
    ENCADEAMENTO_SEPARADO,
    ENCADEAMENTO_COALESCIDO,
    ENDERECAMENTO_BALDES
};
*/

int tabelaHash::consultaContador(){
        return this->cont;
}

int tabelaHash::consultaChave(){
    return this->chave;
}

std::string tabelaHash::consultaChaveOrig(){
    return this->chaveOrig;
}

void tabelaHash::insereChave(int chave){
    this->chave = chave;
    somaContador();
}

void tabelaHash::insereContador(int contador){
    this->cont = contador;
}

void tabelaHash::insereChaveOrig(std::string chave){
    this->chaveOrig = chave;
}

void tabelaHash::somaContador(){
    this->cont = cont + 1;
}

int tabelaHash::funcaoHash(int versao, int tam) // função hash transforma valores decimais para octais (transformação de base) e depois aplica o método da divisão
{
    std::string resultado;
    while(versao >= 1)
    {
        if(versao % 8 == 0)
        {
            resultado = "0" + resultado;
        }
        else if (versao % 8 == 7)
        {
            resultado = "7" + resultado;
        }
        else if (versao % 8 == 6)
        {
            resultado = "6" + resultado;
        }
        else if (versao % 8 == 5)
        {
            resultado = "5" + resultado;
        }
        else if (versao % 8 == 4)
        {
            resultado = "4" + resultado;
        }
        else if (versao % 8 == 3)
        {
            resultado = "3" + resultado;
        }
        else if (versao % 8 == 2)
        {
            resultado = "2" + resultado;
        }
        else if (versao % 8 == 1)
        {
            resultado = "1" + resultado;
        }
        versao = versao/8;
    }
    int versaoConvertida = stoi(resultado);
    return (versaoConvertida % tam);
}

int tabelaHash::trataColisao(int chave, int tam, int i){
    int m1 = 27;
    int m2 = 26;
    int saida;
    saida = ((chave % m1) + i*((chave % m2)) + 1);
    return saida;
}

void tabelaHash::imprimeTabela(tabelaHash *tabela, int n)
{
    for (int i = 0; i < n; i++){
    cout << "Versao" << " " << "," << " " << "Numero de reviews da mesma versao" << " " << endl;
    cout << tabela[i].consultaChaveOrig() << ", " << tabela[i].consultaContador();
    cout << endl;
    }
}

int tabelaHash::totalColisoes(int *tabela, int m)
{
    int cont = 0;
    for(int i = 0; i < m; i++)
    {
        if(tabela[i] > 1)
            cont += tabela[i]-1;
    }
    return cont;
}

void tabelaHash::criaTabelaHash(Registro *reg, int n)
{
    tabelaHash *tab = new tabelaHash[n];
    tabelaHash aux;
    int chave;
    std::string chaveOrig;
    for (int i = 0; i < n; i++)
    {
        chave = retiraPontos(reg[i].getVersion());
        chaveOrig = reg[i].getVersion();
        if (chave != 0)
        {
            if (tab[aux.funcaoHash(chave, n)].consultaContador() == 0) //Caso a função hash encontre uma posição vazia na tabela para inserir a chave
            {
                tab[aux.funcaoHash(chave, n)].insereChave(chave);
                tab[aux.funcaoHash(chave, n)].insereChaveOrig(chaveOrig);
            }
            else if ((tab[aux.funcaoHash(chave, n)].consultaContador() != 0) && (tab[aux.funcaoHash(chave, n)].consultaChave() == chave)) // Caso a função hash encontre uma posição na tabela onde outro review com a mesma versão já tenha sido inserido
            {
                tab[aux.funcaoHash(chave, n)].somaContador();
            }
            else if ((tab[aux.funcaoHash(chave, n)].consultaContador() != 0) && (tab[aux.funcaoHash(chave, n)].consultaChave() != chave)) //Caso a função hash devolva uma posição da tabela não vazia e que a versão do review é diferente do já inserido, ocorre a colisão
            {
                int j = 0;
                while ((tab[aux.trataColisao(chave, n, j)].consultaContador() != 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() != chave)) //Enquanto a colisão persistir, índice j, que entra na função de tratamento de colisão, é somado
                {
                    j++;
                }
                // ao sair do while, temos que a função trataColisao encontrou uma posição vazia na tabela para inserir a versão, ou ela encontrou uma posição na tabela onde a mesma versão de outro review já havia colidido e sido salva
                if ((tab[aux.trataColisao(chave, n, j)].consultaContador() != 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() == chave)) // caso a tabela já tenha a versão inserida por um review anterior
                {
                    tab[aux.trataColisao(chave, n, j)].somaContador();
                }
                else if ((tab[aux.trataColisao(chave, n, j)].consultaContador() == 0) && (tab[aux.trataColisao(chave, n, j)].consultaChave() != chave)) // caso uma posição vazia na tabela tenha sido encontrada para guardar a versão
                {
                    tab[aux.trataColisao(chave, n, j)].insereChave(chave);
                    tab[aux.trataColisao(chave, n, j)].insereChaveOrig(chaveOrig);
                }
                    //contaColisao++;
            }            
        }
        else
        {
            // ignora review com versão vazia
        }
    }
    cout << "Tabela Hash criada com sucesso" << endl;
}

int tabelaHash::retiraPontos(std::string versao)
{
    char removePonto[] = ".";
    int chave;
    if (versao == "NaN")
    {
        return 0;
    }
    else
    {
        std::string temp = versao;
        for (unsigned int j = 0; j < strlen(removePonto); j++)
        {
            temp.erase(std::remove(temp.begin(), temp.end(), removePonto[j]), temp.end());
        }
        chave = stoi(temp);
        return chave;
    }
}

