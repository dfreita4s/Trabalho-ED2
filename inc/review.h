#include <iostream>

class Review
{
private:
    char *id;
    std::string texto;
    char *versaoApp;
    char *data;
    int upvotes;
    Review *proxReview;

public:
    Review(){};
    Review(char*, std::string , int, char *, char *);
    ~Review();

    void setarProximo(Review *No);
    void exibeRegistro();
    char *obterID();
    std::string obterTexto();
    int obterVotos();
    char *obterVersao();
    char *obterData();
    Review *obterProximo();
};