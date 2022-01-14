#include<iostream>
#include "../inc/vermelhaPreta.h"

vermelhaPreta::vermelhaPreta()
{
    raiz = nullptr;
    nil = new NoVP("nil", -1000);
    nil->setColor(Preto);
}

vermelhaPreta::~vermelhaPreta()
{
    delete raiz;
    delete nil;
    std::cout << "Destruindo Árvore.." << std::endl;
}

// Rotações
void vermelhaPreta::rotacaoEsquerda(NoVP *no)
{
    NoVP* q;

    q = no->getNoDir();
    no->setNoDir(q->getNoEsq());
    q->setNoEsq(no);

    // Atualiza Pai
    q->setNoPai(no->getNoPai());
    no->setNoPai(q);

    if (q->getNoPai() == nullptr) // q virou raiz
        raiz = q;
    else
        q->getNoPai()->setNoDir(q); // Se não for raiz, aponta nó direito para o novo nó
}

void vermelhaPreta::rotacaoDireita(NoVP *no)
{
    NoVP* q;

    q = no->getNoEsq();
    no->setNoEsq(q->getNoDir());
    q->setNoDir(no);

    // Atualiza Pai
    q->setNoPai(no->getNoPai());
    no->setNoPai(q);

    if (q->getNoPai() == nullptr) // q virou raiz
        raiz = q;
    else
        q->getNoPai()->setNoDir(q); // Se não for raiz, aponta nó direito para o novo nó

}

void vermelhaPreta::rotacaoDuplaEsquerda(NoVP *no)
{
    NoVP* q;
    NoVP* r;

    q = no->getNoDir();
    r = q->getNoEsq();
    no->setNoDir(r->getNoEsq());
    q->setNoEsq(r->getNoDir());
    r->setNoEsq(no);
    r->setNoDir(q);

    // Atualiza pais
    r->setNoPai(no->getNoPai());
    q->setNoPai(r);
    no->setNoPai(r);

    // Atualiza filhos
    if (r->getNoPai() != nullptr) // Se for null é a raiz
        if (r->getNoPai()->getNoEsq() == no)
            r->getNoPai()->setNoEsq(r);
        else
            r->getNoPai()->setNoDir(r);
    else
        raiz = r; // Atualiza raiz

}

void vermelhaPreta::rotacaoDuplaDireita(NoVP *no)
{
    NoVP* q;
    NoVP* r;

    // Faz a rotação
    q = no->getNoEsq();
    r = q->getNoDir();
    no->setNoEsq(r->getNoDir());
    q->setNoDir(r->getNoEsq());
    r->setNoDir(no);
    r->setNoEsq(q);

    // Atualiza pais
    r->setNoPai(no->getNoPai());
    q->setNoPai(r);
    no->setNoPai(r);

    // Atualiza filhos
    if (r->getNoPai() != nullptr) // Se for null é a raiz
        if (r->getNoPai()->getNoDir() == no)
            r->getNoPai()->setNoDir(r);
        else
            r->getNoPai()->setNoEsq(r);
    else
        raiz = r; // Atualiza raiz

}

bool vermelhaPreta::arvoreVazia()
{
    if(raiz == nullptr)
        return true;
    return false;
}

void vermelhaPreta::inserir(std::string id, int val)
{  
    NoVP* novoNo = new NoVP(id, val);
    novoNo->setNoEsq(nil);
    novoNo->setNoDir(nil);
    novoNo->setColor(Vermelho);
    inserirNo(novoNo);
    arrumaArvore(novoNo);
    // prettyPrint(); // Ver passo-a-passo
    // TO-DO: deletar esses nós no destrutor;
}

void vermelhaPreta::inserirNo(NoVP* no)
{
    // CASO 1: Nó é raiz
    if(raiz == nullptr)
    {
        raiz = no;
        return;
    }

    NoVP* p = nullptr;
    NoVP* q = raiz;

    while(q != nil)
    {
        p = q;
        if (no->getValor() < q->getValor())
            q = q->getNoEsq();
        else
            q = q->getNoDir();
    }

    no->setNoPai(p);

    if (p == nullptr)
        raiz = no;
    else if (no->getValor() < p->getValor())
            p->setNoEsq(no);
        else
            p->setNoDir(no);

    if (no->getNoPai() == nullptr)
    {
        no->setColor(Preto);
        return;
    }

    if (no->getNoPai()->getNoPai() == nullptr)
        return;
}

void vermelhaPreta::arrumaArvore(NoVP * no)
{
    // CASO 1: Colori nó para preto
    if ( no == raiz ) {
        no->setColor(Preto);
        return;
    }

    while (getColor(no->getNoPai()) == Vermelho) {

        if(no->getNoPai()->getNoPai()->getNoDir() == no->getNoPai()){
        // PAI NO DIREITA            
            NoVP* tio = no->getNoPai()->getNoPai()->getNoEsq();
            if(getColor(tio) == Vermelho) {
            // CASO 2: TIO VERMELHO
                tio->setColor(Preto);
                no->getNoPai()->setColor(Preto);
                if(no->getNoPai()->getNoPai()->getNoPai() != nullptr) // Raiz
                    no->getNoPai()->getNoPai()->setColor(Vermelho);
            } else {
                // CASO 3: PAI VERMELHO E TIO PRETO
                // SUBCASO 3.1: TIO PRETO
                if (no == no->getNoPai()->getNoDir()) {

                    no->getNoPai()->getNoPai()->setColor(Vermelho);
                    no->getNoPai()->setColor(Preto);
                    no->setColor(Vermelho);
                    rotacaoEsquerda(no->getNoPai()->getNoPai());
                    no = no->getNoPai()->getNoPai();
                } else {
                    // SUBCASO 3.2:
                    no->getNoPai()->getNoPai()->setColor(Vermelho);
                    no->setColor(Preto);
                    rotacaoDuplaEsquerda(no->getNoPai()->getNoPai());
                }
            }
        } else {
        // PAI DO NO A ESQUERDA
            NoVP* tio = no->getNoPai()->getNoPai()->getNoDir();
            if(getColor(tio) == Vermelho) {
            // CASO 2: TIO VERMELHO
                tio->setColor(Preto);
                no->getNoPai()->setColor(Preto);
                if(no->getNoPai()->getNoPai()->getNoPai() != nullptr) // Raiz
                    no->getNoPai()->getNoPai()->setColor(Vermelho);
            } else {
                // CASO 3: PAI VERMELHO E TIO PRETO
                // SUBCASO 3.1: TIO PRETO
                if (no == no->getNoPai()->getNoEsq()) {
                    no->getNoPai()->getNoPai()->setColor(Vermelho);
                    no->getNoPai()->setColor(Preto);
                    no->setColor(Vermelho);
                    rotacaoDireita(no->getNoPai()->getNoPai());
                    no = no->getNoPai()->getNoPai();
                } else {
                    // SUBCASO 3.2:
                    no->getNoPai()->getNoPai()->setColor(Vermelho);
                    no->setColor(Preto);
                    rotacaoDuplaDireita(no->getNoPai()->getNoPai());
                }
            }
        }

        if(no == nullptr)
            break;
        arrumaArvore(no);
    }
}

Color vermelhaPreta::getColor(NoVP * no)
{
    if (no == nullptr || no == nil)
        return Preto;
    else
        return no->getColor();
}

void vermelhaPreta::printHelper(NoVP* no, std::string indent, bool last) {
		// print the tree structure on the screen
	   	if (no != nil) {
		   std::cout<<indent;
		   if (last) {
            if(no->getNoPai() == nullptr)
		      std::cout<<"----";
            else
		      std::cout<<"R----";
		      indent += "     ";
		   } else {
		      std::cout<<"L----";
		      indent += "|    ";
		   }
            
           std::string sColor = getColor(no) ? "BLACK" : "RED";
		   std::cout<<no->getValor()<<"("<<sColor<<")"<<std::endl;
		   printHelper(no->getNoEsq(), indent, false);
		   printHelper(no->getNoDir(), indent, true);
		}
	}

void vermelhaPreta::prettyPrint() {
    if (raiz) {
        printHelper(raiz, "", true);
    }
}

void vermelhaPreta::imprimirNo(NoVP* no, bool esq)
{
    if(no == nil)
        return;
    std::string NoEsquerdo = esq ? "E:\t" : "D:\t";
    std::cout << NoEsquerdo;
    no->info();
    imprimirNo(no->getNoEsq(), true);
    imprimirNo(no->getNoDir(), false);
}

void vermelhaPreta::imprimirArvore()
{
    imprimirNo(raiz, 0);
}