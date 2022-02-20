
class HuffmanNo
{
private:
    char simb;
    int freq;
    HuffmanNo *esq;
    HuffmanNo *dir;

public:
    HuffmanNo(char, int);
    ~HuffmanNo();

    char getSimb() { return this->simb; };
    int getFreq() { return this->freq; };

    void setFreq(int);
    void setSimb(char);

    void setEsq(HuffmanNo *esq);
    void setDir(HuffmanNo *dir);

    HuffmanNo *getEsq() { return this->esq; };
    HuffmanNo *getDir() { return this->dir; };
};