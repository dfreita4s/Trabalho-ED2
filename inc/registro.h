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
    void setN(int);
    int getN();

    std::string pivoMediano(std::string *, int, int);
    void trocaNo(std::string &r1, std::string &r2);
    int quickSort_particionaLista(std::string *list, int i, int j);
    void quickSort_ordena(std::string *list, int i, int k);
    void quickSort_time(std::string *list, int n);

    void heapify(std::string *list, int i, int tam);
    void build_heap(std::string *list, int tam);
    void heapSort_ordena(std::string *list, int tam);
    void heapSort_time(std::string *list, int tam);

    int find_next(int gap);
    void combSort_ordena(std::string *list, int tam);
    void combSort_time(std::string *list, int tam);


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