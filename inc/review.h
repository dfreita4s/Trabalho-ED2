#include<iostream>

class Review
{
    private:
        std::string id;
        std::string texto;
        int upvotes;
        std::string versaoApp;
        std::string data;
        Review *proxReview;

    public:
        Review(){};
        Review(std::string , std::string , int , std::string , std::string );
        ~Review();

        void setarProximo(Review *No);
        void exibeRegistro();
        std::string obterID();
        std::string obterTexto();
        int obterVotos();
        std::string obterVersao();
        std::string obterData();
        Review *obterProximo();
};