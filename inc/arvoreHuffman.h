#include "NoHuffman.h"

class noDupEnc
{

private:

    NoHuffman *noH;
    noDupEnc *ant;
    noDupEnc *prox;
    std::string codificacao;

public:

    void setNoH(NoHuffman*);
    void setAnt(noDupEnc*);
    void setProx(noDupEnc*);
    void setCodificacao(std::string);
    NoHuffman* getNoH();
    noDupEnc* getAnt();
    noDupEnc* getProx();
    std::string getCodificacao();
    void geraCodificacao(NoHuffman *);

    noDupEnc();
    ~noDupEnc();   
};

class listaDupEnc
{

private:
    noDupEnc *inicio;
    noDupEnc *fim;
    noDupEnc *atual;

public:

    void setInicio(noDupEnc*);
    noDupEnc* getInicio();
    void setFim(noDupEnc*);
    noDupEnc* getFim();
    void setAtual(noDupEnc*);
    noDupEnc* getAtual();

    //função para saber se um determinado nó já foi incluído na lista duplamente encadeada
    void verificaLista(listaDupEnc);
    listaDupEnc();
    ~listaDupEnc();
};

class arvoreHuffman
{
private:
    NoHuffman *raiz;
    NoHuffman *escape;
    listaDupEnc biblioteca;
    //noDupEnc *noDE;

public:
    arvoreHuffman();
    ~arvoreHuffman();
    void constroiArvore(char);
    void recebeReview(std::string);
    //adiciona novo caractere na biblioteca (caso não tinha sido adicionada antes)
    void addBiblioteca(NoHuffman*);
    //verifica se o caractere já não foi incluído antes, retornando sua codificação, retorna NaN quando não encontra
    std::string checaBiblioteca(char);
    //aumenta frequencia de um símbolo que já está na árvore
    void incrementaFrequencia(char);
    //imprime a arvore de huffman
    void imprimeArvore();
    //verifica se no com símbolo está presente na árvore
    bool verificaSimbolo(char);
    //verifica se no com um determinado símbolo está presente na lista duplamente encadeada ("biblioteca")
    bool verificaLista(NoHuffman *);
    //soma frequencia de um no que já está na lista
    void increFreqBib(NoHuffman*);
    //função para verificar se as propriedades da árvore de huffman estão sendo respeitadas
    void verificaPropriedade(NoHuffman *);

    NoHuffman* buscaNo(char);
};