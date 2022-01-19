#include "registro.h"
#include <fstream>
#include <vector>

class Lista
{
public:
    // Review *raiz;
    std::ifstream arquivo;

    Lista();
    Lista(const std::string &);
    ~Lista();

    int obterTam();
    bool obterReviews();
    // Review *obterRaiz();
    void listarTodas();
    int versaoToInt(std::string);

    // void inserirReview(Review *, Review *);
   

    bool criarArquivoBinario(Registro *);
    void usaListaImportacao();

protected:
    bool abrirArquivo(const std::string &);
};
