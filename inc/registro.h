#include <iostream>

class Registro {

    public:
        std::string leBinario(int); 
        void testeImportacao();
        void acessaRegistro(int);

        Registro(const std::string &, int);
        ~Registro();
        
        void setRegistro(std::string *registro); //setar o array registros
        std::string *getRegistro(); //pegar o registro

        std::string *importaRegistros(int); //importar aleatoriamente N registros aleatorios
    private:
        std::string *registros; //array de registros para a memoria principal
};