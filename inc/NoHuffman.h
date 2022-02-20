#include <iostream>

class NoHuffman
{
private:
    char simbolo;
    int frequencia = 0;
    std::string tipoNo;
    std::string codificacao;
    NoHuffman *pai;
    NoHuffman *dir;
    NoHuffman *esq;
public:
    NoHuffman();
    NoHuffman(char, int, std::string, std::string);
    ~NoHuffman();

    void setNoPai(NoHuffman *);
    NoHuffman* getNoPai();
    void setNoDir(NoHuffman *);
    NoHuffman* getNoDir();
    void setNoEsq(NoHuffman *);
    NoHuffman* getNoEsq();
    NoHuffman* getNoEscape();

    void setSimbolo(char s);
    char getSimbolo();
    void setFrequencia();
    int getFrequencia();
    void setTipoNo(std::string);
    std::string getTipoNo();
    void setCodificacao(std::string);
    std::string getCodificacao();
    void incrementaCodificacao(std::string);
    void recebeFrequencia(int);
};