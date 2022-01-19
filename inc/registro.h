#include <iostream>
#ifndef TRABALHO_ED2
#define TRABALHO_ED2
class Registro
{

public:
    Registro();
    ~Registro();

    //setters
    void setPos(int);
    void setN(int);
    void setID(std::string);
    void setText(std::string);
    void setVersion(std::string);
    void setDate(std::string);
    void setVotes(int);

    //getters
    std::string getID();
    std::string getText();
    std::string getVersion();
    std::string getDate();
    int getVotes();
    int getN();
    int getPos();

    std::string imprimeRegistros();

private:

    int posBinario;
    std::string review_id;
    std::string review_text;
    int upvotes;
    std::string app_version;
    std::string posted_date;
    int N;
};

#endif