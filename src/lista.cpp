#include "../inc/lista.h"
#include <string>

Lista::Lista(const std::string &caminhoArquivo)
{
    this->abrirArquivo(caminhoArquivo);
}

Lista::~Lista()
{
    while (this->raiz != nullptr)
    {
        Review *novaRaiz = raiz->obterProximo();
        delete this->raiz;
        this->raiz = novaRaiz;
    }
    this->arquivo.close();
}

bool Lista::abrirArquivo(const std::string &caminhoArquivo)
{
    try
    {
        this->arquivo.open(caminhoArquivo, std::ios::in);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Houve um erro ao abrir o arquivo!" << std::endl
                  << e.what() << '\n';
    }
    return false;
}

bool Lista::obterReviews()
{
    if (this->arquivo.is_open())
    {
        std::string linha;

        getline(this->arquivo, linha); //Le cabecalho do arquivo

        Review *ultimo = nullptr;

        getline(this->arquivo, linha);

        while (!arquivo.eof() && linha != "")
        {
            int pos = 0;
            pos = linha.find(",");
            std::string id = linha.substr(3, pos - 3); // Inicio em 3 para retirar 'gp:'
            linha = linha.substr(pos + 1, linha.length());

            pos = linha.find_last_of(",");
            std::string data = linha.substr(pos + 1); // Obter a Data
            linha = linha.substr(0, pos);

            pos = linha.find_last_of(",");
            std::string versao = linha.substr(pos + 1); // Obter a versão
            linha = linha.substr(0, pos);

            pos = linha.find_last_of(",");
            int upvotes = stod(linha.substr(pos + 1)); // Obter upvotes
            linha = linha.substr(0, pos);

            std::string texto = linha; // Obter o comentário
            if (texto.find("\"") != -1)
                texto = texto.substr(1, texto.length() - 1); // Caso comece com esteja entre "", retirá-los

            Review *review = new Review(id, texto, upvotes, versao, data); //Cria o Review
            this->inserirReview(review, ultimo);                           // Insere na lista
            ultimo = review;                                               // Atualiza ponteiro do último Review para o atual.

            getline(this->arquivo, linha);

            /* Trata os registros que estão com '\n'
               Verifica se a última informação é do tipo ':SS' */
            if (!(isdigit(linha[linha.length() - 2]) && (isdigit(linha[linha.length() - 3])) && (linha[linha.length() - 4] == ':')))
            {
                do
                {
                    std::string aux = linha;
                    getline(this->arquivo, linha);
                    aux.append(linha);
                    linha = aux;
                } while (!isdigit(linha[linha.length() - 2]));
            }
        }
        return true;
    }
    return false;
}

void Lista::inserirReview(Review *rev, Review *ultimo)
{
    if (!(this->raiz == nullptr))
        ultimo->setarProximo(rev);
    else
        this->raiz = rev;
}

Review *Lista::obterRaiz()
{
    if (!(this->raiz == nullptr))
        return this->raiz;
    else
        std::cout << "Lista vazia." << std::endl;
}

// Listar todos Reviews presentes na Lista.
void Lista::listarTodas()
{
    Review *No = this->raiz;
    while (No->obterProximo() != nullptr)
    {
        std::cout << std::endl;
        No->exibeRegistro();
        No = No->obterProximo();
    }
    std::cout << "Lista vazia." << std::endl;
}

// Esboço da função para acessar o k-ésimo registro
bool Lista::acessaRegistro(int k)
{
    Review *No = this->raiz;
    for (int i = 0; ((No != nullptr) && (i <= k)); i++)
    {
        if (i == k)
        {
            No->exibeRegistro();
            return true;
        }

        else
            No = No->obterProximo();
    }
    std::cout << std::endl
              << "Registro não encontrado." << std::endl;
    return false;
}