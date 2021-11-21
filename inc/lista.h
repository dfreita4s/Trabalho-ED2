#include "review.h"
#include <fstream>
#include <vector>

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
        void acessaRegistro(int);
        void inserirReview(Review *, Review *);
        void testeImportacao();
        void criarArquivoBinario(std::vector<Review>);
        void usaListaImportacao();
        void printTerminal();

    protected:
        bool abrirArquivo(const std::string&);
        
};