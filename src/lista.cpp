#include "../inc/lista.h"
#include <string>
#include <fstream>

Lista::Lista(const std::string &caminhoArquivo)
{
    this->raiz = nullptr;
    this->abrirArquivo(caminhoArquivo);
}

Lista::~Lista()
{
    while(this->raiz != nullptr)
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
    catch(const std::exception& e)
    {
        std::cerr << "Houve um erro ao abrir o arquivo!" << std::endl << e.what() << '\n';
    }
    return false;
}

int Lista::obterTam(){
    int size=0;
    if(this->arquivo.is_open())
    {
        if(this->obterRaiz() != nullptr)
        {
            Review *No = this->raiz;
            while(No->obterProximo() != nullptr)
            {
                size++;
                No = No->obterProximo();
            }
            return size;
        }
        else{
            return 0;
        }
    }
    return -1;
}

bool Lista::obterReviews()
{
    if(this->arquivo.is_open())
    {
        std::string linha;

        getline(this->arquivo, linha); //Le cabecalho do arquivo

        Review *ultimo = nullptr;
        
        getline(this->arquivo, linha);

        int k=0; // contar registros

        while(!arquivo.eof() && linha != "")
        {
            /* Trata os registros que estão com '\n'
               Verifica se a última informação é do tipo ':SS' */
            
            while(!(isdigit(linha[linha.length()-1]) && (isdigit(linha[linha.length()-2])) && (linha[linha.length()-3]==':')))
            {
                std::string aux = linha;
                getline(this->arquivo, linha);
                aux.append(linha);
                linha = aux;
            }
            
            k++;

            int pos;
            pos = linha.find(",");
            std::string id = linha.substr(3, pos-3); // Inicio em 3 para retirar 'gp:'
            linha = linha.substr(pos+1, linha.length());
            
            pos = linha.find_last_of(",");
            std::string data = linha.substr(pos+1); // Obter a Data
            linha = linha.substr(0, pos);

            pos = linha.find_last_of(",");
            std::string versao = linha.substr(pos+1); // Obter a versão
            if(versao.length() == 0)
                versao = "NaN";
            linha = linha.substr(0, pos);

            pos = linha.find_last_of(",");
            int upvotes = stod(linha.substr(pos+1)); // Obter upvotes
            linha = linha.substr(0, pos);

            std::string texto = linha; // Obter o comentário
            if(texto.find("\"") != -1)
                texto = texto.substr(1, texto.length()-2); // Caso comece com esteja entre "", retirá-los

            Review *review = new Review(id, texto, upvotes, versao, data); // Cria o Review
            this->inserirReview(review, ultimo); // Insere na lista
            ultimo = review; // Atualiza ponteiro do último Review para o atual.
            
            getline(this->arquivo, linha);
        }
        std::cout << k-1 << " de registros foram importados com sucesso." << std::endl;
        criarArquivoBinario();
        return true;
    }
    std::cout << "Ocorreu um erro ao ler os dados." << std::endl;
    return false;
}

bool Lista::criarArquivoBinario(){

    std::fstream arq("tiktok.bin", std::ios::out | std::ios::binary);
    Review * raiz = obterRaiz();
    int k = obterTam();
    if(arq.is_open())
    {   
        for(int i=0; i<=k; i++){
            // std::string id = raiz->obterID();
            arq.write((char *)raiz, (sizeof(Review)));
            raiz=raiz->obterProximo();
        }
        std::cout << "criou arquivo!" << std::endl;
    } 
    else
        std::cout << "Deu errado";
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
    if(!(this->raiz == nullptr))
        return this->raiz;
    else
    {
        return nullptr;
        std::cout << "Lista vazia." << std::endl;
    }
}

// Listar todos Reviews presentes na Lista.
void Lista::listarTodas()
{
    if(this->arquivo.is_open())
    {
        if(this->obterRaiz() != nullptr)
        {
            Review *No = this->raiz;
            while(No->obterProximo() != nullptr)
            {
                std::cout << std::endl;
                No->exibeRegistro();
                No = No->obterProximo();
            }
        }
        else
            std::cout << "Lista vazia." << std::endl;
    }
    else
        std::cout << "Impossível listar. O arquivo não existe." << std::endl;
}

// Esboço da função para acessar o k-ésimo registro
bool Lista::acessaRegistro(int k)
{
    if(this->obterRaiz() != nullptr)
    {
        Review *No = this->raiz;
        for(int i=0; ((No != nullptr) && (i<=k)); i++)
        {
            if(i==k)
            {
                No->exibeRegistro();
                return true;
            }
            else
                No = No->obterProximo();
        }
        std::cout << std::endl << "Registro não encontrado." << std::endl;
        return false;
    }
    else
    {
        std::cout << "Nenhum registro encontrado." << std::endl;
        return false;
    }
}

void Lista::testeImportacao(){
    int resp, N = 0;
    std::cout<<"Deseja exibir a saída no console ou salvá-la em um arquivo texto? 1 para no console 2 para salvar. "<<std::endl;
    std::cin>>resp;
    if(resp == 1){
        //escolha saida em console N = 10
        N = 10;
        for(int i = N; i>=0; i--){
         acessaRegistro(rand() % 3646475 + 0);
        }
    }else if(resp == 2){
        //escolha salvar em um arquivo texto
        N = 100;
        //fazer
    }else {
        std::cout<<"Por favor digite uma resposta válida!"<<std::endl;
        testeImportacao();
    }
}