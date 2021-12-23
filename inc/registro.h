#include <iostream>

class Registro
{

public:
    std::string leBinario(int);
    void testeImportacao();
    void acessaRegistro(int);
    void ordenaRegistros();

    Registro();
    ~Registro();

    std::string getTerms(int, std::string); //pega um termo do array de registros(id, text...)

    void setRegistro(std::string *registro); //setar o array registros
    std::string *getRegistro();              //pegar o registro
    void setN(int);
    void setID(std::string);
    void setText(std::string);
    void setVersion(std::string);
    void setDate(std::string);
    void setVotes(int);
    std::string getID();
    std::string getText();
    std::string getVersion();
    std::string getDate();
    int getVotes();
    int getN();


    std::string imprimeRegistros();

    std::string pivoMediano(std::string *, int, int);
    void trocaNo(std::string &r1, std::string &r2);
    int quickSort_particionaLista(std::string *list, int i, int j);
    void quickSort_ordena(std::string *list, int i, int k);
    void quickSort_time(std::string *list, int n);

    std::string *importaRegistros(int); //importar aleatoriamente N registros aleatorios

private:
    std::string *registros; //array de registros para a memoria principal
    std::string review_id;
    std::string review_text;
    int upvotes;
    std::string app_version;
    std::string posted_date;
    int N;
};