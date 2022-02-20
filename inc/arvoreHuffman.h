#include "NoHuffman.h"

struct noDupEnc
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

struct listaDupEnc
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

    listaDupEnc();
    ~listaDupEnc();
    void troca(noDupEnc*, noDupEnc*);
};

class arvoreHuffman
{
private:
    NoHuffman *raiz;
    NoHuffman *escape;
    listaDupEnc biblioteca;
    //noDupEnc *noDE;
    int tam_inicio;
    int tam_final;

public:
    arvoreHuffman();
    ~arvoreHuffman();
    int getTamIni(){return this->tam_inicio;};
    int getTamFim(){return this->tam_final;};
    void constroiArvore(char);
    void recebeReview(std::string);
    //adiciona novo caractere na biblioteca (caso não tinha sido adicionada antes)
    void addBiblioteca(NoHuffman*);
    //verifica se o caractere já não foi incluído antes, retornando sua codificação, retorna NaN quando não encontra
    std::string checaBiblioteca(char);
    //incrementa no com repetição de símbolos
    void incrementaBiblioteca(NoHuffman*);
    //aumenta frequencia de um símbolo que já está na árvore
    void incrementaFrequencia(char);
    //imprime a arvore de huffman
    void imprimeArvore();
    //imprime nós que estão na lista duplamente encadeada
    void imprimeBiblioteca();
    //verifica se no com símbolo está presente na árvore
    bool verificaSimbolo(char);
    //verifica se no com um determinado símbolo está presente na lista duplamente encadeada ("biblioteca")
    bool verificaLista(NoHuffman *);
    //soma frequencia de um no que já está na lista
    void increFreqBib(NoHuffman*);
    //função para passar todos os nós da árvore/lista até a função verificaPropriedade
    void passaNo(noDupEnc*);
    //função para verificar se as propriedades da árvore de huffman estão sendo respeitadas
    void verificaRotPri(noDupEnc *);
    //função para rotacionar árvore quando a propriedade de huffman não é respeitada após incrementar a frequência de um símbolo que já estava na árvore
    void rotacionaRep(noDupEnc*, noDupEnc*);
    //função para rotacionar árvore quando a propriedade de huffman não é respeitada após adicionar um novo nó na árvore
    void rotacionaPri(noDupEnc*, noDupEnc*);
    //função para checar se será necessário rotacionar árvore após incrementar frequencia
    void verificaRotacao(noDupEnc *, noDupEnc *);

    void verificaRotRep(noDupEnc *);
    //traduzir o arquivo
    void traduzir();
};