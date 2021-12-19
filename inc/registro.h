#include <iostream>

class Registro
{

public:
    std::string leBinario(int);
    void testeImportacao();
    void acessaRegistro(int);
    void ordenaRegistros();

    Registro(const std::string &, int);
    ~Registro();

    std::string getTerms(int, std::string); //pega um termo do array de registros(id, text...)

    void setRegistro(std::string *registro); //setar o array registros
    std::string *getRegistro();              //pegar o registro
    void setID(std::string);





    std::string *importaRegistros(int); //importar aleatoriamente N registros aleatorios
private:
    std::string *registros; //array de registros para a memoria principal
    std::string review_id;
    std::string review_text;
    int upvotes;
    std::string app_version;
    std::string posted_date;
};