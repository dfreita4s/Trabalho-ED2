#include<iostream>
#include "../inc/arvoreVP.h"



arvoreVP::arvoreVP()
{
    raiz = nullptr;
    nil = new NoVP("nil", -1000);
    nil->setColor(Preto);
}

arvoreVP::~arvoreVP()
{
    std::cout << "Destruindo Árvore.." << std::endl;
    auxDeleteNos(raiz);
    delete nil;
    std::cout << "Árvore destruída" << std::endl;
}

void arvoreVP::auxDeleteNos(NoVP* p)
{

    if (p == nil)
        return;

    auxDeleteNos(p->getNoEsq());
    auxDeleteNos(p->getNoDir());

    delete p;    
}

// Rotações
void arvoreVP::rotacaoEsquerda(NoVP *no)
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

void arvoreVP::rotacaoDireita(NoVP *no)
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
        q->getNoPai()->setNoEsq(q); // Se não for raiz, aponta nó direito para o novo nó

}

void arvoreVP::rotacaoDuplaEsquerda(NoVP *no)
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

void arvoreVP::rotacaoDuplaDireita(NoVP *no)
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

bool arvoreVP::arvoreVazia()
{
    if(raiz == nullptr)
        return true;
    return false;
}

void arvoreVP::inserir(std::string id, int posicao)
{  
    NoVP* novoNo = new NoVP(id, posicao);
    novoNo->setNoEsq(nil);
    novoNo->setNoDir(nil);
    novoNo->setColor(Vermelho);
    inserirNo(novoNo);
    insere_caso1(novoNo);
    // prettyPrint(); // Ver passo-a-passo
    // TO-DO: deletar esses nós no destrutor;
}

void arvoreVP::inserirNo(NoVP* no)
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
        if (no->getID() < q->getID())
            q = q->getNoEsq();
        else
            q = q->getNoDir();
    }

    no->setNoPai(p);

    if (p == nullptr)
    {
        raiz = no;
    }
    else if (no->getID() < p->getID())
    {
        p->setNoEsq(no);
    }
    else
    {
        p->setNoDir(no);
    }

    /*
    if (no->getNoPai() == nullptr)
    {
        no->setColor(Preto);
        return;
    }

    if (no->getNoPai()->getNoPai() == nullptr)
        return;
    */
}

void arvoreVP::arrumaArvore(NoVP * no)
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
                } else {
                    // SUBCASO 3.2:
                    no->getNoPai()->getNoPai()->setColor(Vermelho);
                    no->setColor(Preto);
                    rotacaoDuplaDireita(no->getNoPai()->getNoPai());
                }
            }
        }

        if(no->getNoPai() == nullptr)
            break;

        if(no->getNoPai() != raiz)
            no = no->getNoPai()->getNoPai();
    }
}

Color arvoreVP::getColor(NoVP * no)
{
    if (no == nullptr || no == nil)
        return Preto;
    else
        return no->getColor();
}

void arvoreVP::printHelper(NoVP* no, std::string indent, bool last) {
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
		   std::cout<<no->getID()<<"("<<sColor<<")"<<std::endl;
		   printHelper(no->getNoEsq(), indent, false);
		   printHelper(no->getNoDir(), indent, true);
		}
	}

void arvoreVP::prettyPrint() {
    if (raiz) {
        printHelper(raiz, "", true);
    }
}

void arvoreVP::imprimirNo(NoVP* no, bool esq)
{
    if(no == nil)
        return;
    std::string NoEsquerdo = esq ? "E:\t" : "D:\t";
    std::cout << NoEsquerdo;
    no->info();
    imprimirNo(no->getNoEsq(), true);
    imprimirNo(no->getNoDir(), false);
}

void arvoreVP::imprimirArvore()
{
    imprimirNo(raiz, 0);
}

void arvoreVP::buscaNo(arvoreVP *VP, std::string id)
{
    //int aux_id = stoi(id);
    NoVP *p;
    NoVP *q;
    NoVP *result;
    result = nullptr;
    p = nullptr;
    q = raiz;

    if (raiz == nullptr)
    {
        std::cout << "ID procurada nao encontrada, arvore vazia! " << std::endl;
    }
    else
    {
        while (q != nil)
        {
            p = q;
            if (id > p->getID())
            {
                q = p->getNoDir();
            }
            else if (id < p->getID())
            {
                q = p->getNoEsq();
            }
            else
            {
                result = p;
                std::cout << "ID" << " " << p->getID() << " " << "encontrada com sucesso, se encontra na posicao" << " " << p->getPosicao() << " " << "do arquivo binario" << std::endl;
                break;
            }
        }
        if (result == nullptr)
        {
            std::cout << "ID nao foi encontrada na arvore VP" << std::endl;
        }
    }
}

void arvoreVP::insere_caso1(NoVP *no)
{
    if (no->getNoPai() == nullptr)
    {
        no->setColor(Preto);
    }
    else
    {
        insere_caso2(no);       
    }
}

void arvoreVP::insere_caso2(NoVP *no)
{
    if (no->getNoPai()->getColor() == Preto)
    {
        return;
    }
    else
    {
        insere_caso3(no);       
    }
}

void arvoreVP::insere_caso3(NoVP *no)
{
    // checa se o pai do "no" está do lado direito do avô, caso sim, o tio estará do lado esquerdo do avô
    if (no->getNoPai()->getNoPai()->getNoDir() == no->getNoPai())
    {
        // checa se o tio é vermelho assim como o pai, em caso positivo, deve-se colorir pai, tio e avô
        if (no->getNoPai()->getNoPai()->getNoEsq()->getColor() == Vermelho)
        {
            no->getNoPai()->setColor(Preto);
            no->getNoPai()->getNoPai()->getNoEsq()->setColor(Preto);
            no->getNoPai()->getNoPai()->setColor(Vermelho);
            insere_caso1(no->getNoPai()->getNoPai());
        }
        else
        {
            insere_caso4(no);
        }
    }
    else
    {
        if (no->getNoPai()->getNoPai()->getNoDir()->getColor() == Vermelho)
        {
            no->getNoPai()->setColor(Preto);
            no->getNoPai()->getNoPai()->getNoDir()->setColor(Preto);
            no->getNoPai()->getNoPai()->setColor(Vermelho);
            insere_caso1(no->getNoPai()->getNoPai());                       
        }
        else
        {
            insere_caso4(no);
        }
    }    
}

void arvoreVP::insere_caso4(NoVP *no)
{
    // nesse caso o pai (vermelho) está à direita do avô, e o tio (preto), à esquerda do avô
    if (no->getNoPai()->getNoPai()->getNoDir() == no->getNoPai())
    {
        // nesse caso temos uma rotação simples para a esquerda
        if(no->getNoPai()->getNoDir() == no)
        {
            no->getNoPai()->setColor(Preto);
            no->getNoPai()->getNoPai()->setColor(Vermelho);
            novoRotacionaEsq(no->getNoPai()->getNoPai());
        }
        //nesse caso temos uma rotação dupla para a esquerda
        else
        {
            no->setColor(Preto);
            no->getNoPai()->getNoPai()->setColor(Vermelho);
            novoRotDuplaEsq(no->getNoPai()->getNoPai());
        }

    }

    // nesse caso o pai (vermelho) está à esquerda do avô, e o tio (preto), à direita do avô
    else
    {
        // nesse caso temos uma rotação simples para direita
        if (no->getNoPai()->getNoEsq() == no)
        {
            no->getNoPai()->setColor(Preto);
            no->getNoPai()->getNoPai()->setColor(Vermelho);
            novoRotacionaDir(no->getNoPai()->getNoPai());
        }
        //nesse caso temos uma rotação dupla para direita
        else
        {
            no->setColor(Preto);
            no->getNoPai()->getNoPai()->setColor(Vermelho);
            novoRotacionaEsq(no->getNoPai()->getNoPai());
        }
    }
}

void arvoreVP::novoRotacionaDir(NoVP *no)
{
    // se avô era raiz
    if(no->getNoPai() == nullptr)
    {
        //atualiza pai
        NoVP *aux = no->getNoEsq()->getNoDir();
        NoVP *aux2 = no->getNoEsq();
        no->getNoEsq()->setNoDir(no);
        no->setNoPai(nullptr);
        raiz = no->getNoEsq();

        //atualiza avô
        no->setNoEsq(aux);
        aux->setNoPai(no);
        no->setNoPai(aux2);

    }
    // se avô não era raiz
    else
    {
        NoVP *aux = no->getNoEsq()->getNoDir();
        NoVP *aux2 = no->getNoEsq();

        //atualiza pai
        no->getNoEsq()->setNoDir(no);
        no->getNoEsq()->setNoPai(no->getNoPai());
        if(no == no->getNoPai()->getNoEsq())
        {
            no->getNoPai()->setNoEsq(no->getNoEsq());
        }
        else
        {
            no->getNoPai()->setNoDir(no->getNoEsq());
        }
        //atualiza avô
        no->setNoEsq(aux);
        aux->setNoPai(no);
        no->setNoPai(aux2);
    }
}

void arvoreVP::novoRotacionaEsq(NoVP *no)
{
    if(no->getNoPai() == nullptr)
    {
        NoVP *aux = no->getNoDir()->getNoEsq();
        NoVP *aux2 = no->getNoDir();
        // atualiza pai
        no->getNoDir()->setNoEsq(no);
        no->getNoDir()->setNoPai(nullptr);
        raiz = no->getNoDir();

        //atualiza avô
        no->setNoDir(aux);
        aux->setNoPai(no);
        no->setNoPai(aux2);
    }
    else
    {
        NoVP *aux = no->getNoDir()->getNoEsq();
        NoVP *aux2 = no->getNoDir();
        //atualiza pai
        no->getNoDir()->setNoEsq(no);
        no->getNoDir()->setNoPai(no->getNoPai());
        if(no == no->getNoPai()->getNoEsq())
        {
            no->getNoPai()->setNoEsq(no->getNoDir());
        }
        else
        {
            no->getNoPai()->setNoDir(no->getNoDir());
        }
        //atualiza avô
        no->setNoDir(aux);
        aux->setNoPai(no);
        no->setNoPai(aux2);
    }
}

void arvoreVP::novoRotDuplaDir(NoVP *no)
{

    if (no->getNoPai() == nullptr)
    {
        NoVP *aux = no->getNoEsq()->getNoDir()->getNoEsq();
        NoVP *aux2 = no->getNoEsq()->getNoDir();
        NoVP *aux3 = no->getNoEsq()->getNoDir()->getNoDir();
        //atualiza no filho
        no->getNoEsq()->getNoDir()->setNoDir(no);
        no->getNoEsq()->getNoDir()->setNoEsq(no->getNoEsq());
        no->getNoEsq()->getNoDir()->setNoPai(nullptr);
        raiz = no->getNoEsq()->getNoDir();

        //atualiza no pai
        no->getNoEsq()->setNoDir(aux);
        aux->setNoPai(no->getNoEsq());
        no->getNoEsq()->setNoPai(aux2);

        //atualiza no avo
        no->setNoEsq(aux3);
        aux3->setNoPai(no);
        no->setNoPai(aux2);
    }
    else
    {
        NoVP *aux = no->getNoEsq()->getNoDir()->getNoEsq();
        NoVP *aux2 = no->getNoEsq()->getNoDir();
        NoVP *aux3 = no->getNoEsq()->getNoDir()->getNoDir();
        //atualiza no filho
        no->getNoEsq()->getNoDir()->setNoDir(no);
        no->getNoEsq()->getNoDir()->setNoEsq(no->getNoEsq());
        no->getNoEsq()->getNoDir()->setNoPai(no->getNoPai());
        if (no == no->getNoPai()->getNoDir())
        {
            no->getNoPai()->setNoDir(no->getNoEsq()->getNoDir());
        }       
        else
        {
            no->getNoPai()->setNoEsq(no->getNoEsq()->getNoDir());
        }
        //atualiza no pai
        no->getNoEsq()->setNoDir(aux);
        aux->setNoPai(no->getNoEsq());
        no->getNoEsq()->setNoPai(aux2);

        //atualiza no avo
        no->setNoEsq(aux3);
        aux3->setNoPai(no);
        no->setNoPai(aux2);
    }
}

void arvoreVP::novoRotDuplaEsq(NoVP *no)
{
    if (no->getNoPai() == nullptr)
    {
        NoVP *aux = no->getNoDir()->getNoEsq()->getNoDir();
        NoVP *aux2 = no->getNoDir()->getNoEsq();
        NoVP *aux3 = no->getNoDir()->getNoEsq()->getNoEsq();
        //atualiza no filho
        no->getNoDir()->getNoEsq()->setNoDir(no->getNoDir());
        no->getNoDir()->getNoEsq()->setNoEsq(no);
        no->getNoDir()->getNoEsq()->setNoPai(nullptr);
        raiz = no->getNoDir()->getNoEsq();

        //atualiza no pai
        no->getNoDir()->setNoEsq(aux);
        aux->setNoPai(no->getNoDir());
        no->getNoDir()->setNoPai(aux2);

        //atualiza avo
        no->setNoDir(aux3);
        aux3->setNoPai(no);
        no->setNoPai(aux2);
    }
    else
    {
        NoVP *aux = no->getNoDir()->getNoEsq()->getNoDir();
        NoVP *aux2 = no->getNoDir()->getNoEsq();
        NoVP *aux3 = no->getNoDir()->getNoEsq()->getNoEsq();
        //atualiza no filho
        no->getNoDir()->getNoEsq()->setNoDir(no->getNoDir());
        no->getNoDir()->getNoEsq()->setNoEsq(no);
        no->getNoDir()->getNoEsq()->setNoPai(no->getNoPai());
        if (no == no->getNoPai()->getNoDir())
        {
            no->getNoPai()->setNoDir(no->getNoDir()->getNoEsq());
        }
        else
        {
            no->getNoPai()->setNoEsq(no->getNoDir()->getNoEsq());
        }

        //atualiza no pai
        no->getNoDir()->setNoEsq(aux);
        aux->setNoPai(no->getNoDir());
        no->getNoDir()->setNoPai(aux2);

        //atualiza avo
        no->setNoDir(aux3);
        aux3->setNoPai(no);
        no->setNoPai(aux2);
    }
}