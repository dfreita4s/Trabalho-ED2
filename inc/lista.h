#include "review.h"
#include "tabelaHash.h"
#include <fstream>
#include <vector>

class Lista
{
public:
    Review *raiz;
    std::ifstream arquivo;

    Lista();
    Lista(const std::string &);
    ~Lista();

    int obterTam();
    bool obterReviews();
    Review *obterRaiz();
    void listarTodas();

    void inserirReview(Review *, Review *);

    bool criarArquivoBinario();
    void usaListaImportacao();
    void insereTabelaHash(int);
    void populaTabela(int,int);
    int acessaVersao(int, int);
    int pegaVersao(int, int);
    int funcaoHash(int);
    void fazHash(int,int);
    void criaTabelaHash();
    //void recebeVetor(int*);

protected:
    bool abrirArquivo(const std::string &);
};