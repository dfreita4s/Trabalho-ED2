#include "review.h"
#include <fstream>

class Lista
{
    public:
        Review *raiz;
        std::ifstream arquivo;

        Lista();
        Lista(const std::string&);
        ~Lista();

        int obterTam();
        bool obterReviews();
        Review *obterRaiz();
        void listarTodas();
        bool acessaRegistro(int);
        void inserirReview(Review *, Review *);
        void testeImportacao();
        bool criarArquivoBinario();
        void usaListaImportacao();

    protected:
        bool abrirArquivo(const std::string&);
        
};