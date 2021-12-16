#include <iostream>

class Registro {

    public:
        std::string leBinario(int);
        void testeImportacao();
        Registro(const std::string &, int);
        ~Registro();
    private:
        std::string *registros;
};