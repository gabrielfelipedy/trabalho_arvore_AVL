#include <stdio.h>
#include <stdlib.h>

//criar nosso nó

#define MAX(a, b) (a > b) ? a : b

typedef struct Arvore
{
    int num;
    int altura;
    struct Arvore *esq, *dir;
} Arvore;

//*************
int height(Arvore* no)
{
    if(no == NULL) return 0;

    return no->altura;
}

int getBalance(Arvore* no)
{
    if(no == NULL) return 0;

    return height(no->dir) - height(no->esq);
}

//******************

//********
//Rotacoes
//********

//rotacao_esquerda

Arvore* rotacao_esquerda(Arvore* no)
{
    Arvore* aux1 = no->dir;
    Arvore* aux2 = aux1->esq;

    no->dir = aux2;
    aux1->esq = no;

    no->altura = MAX(
        height(no->dir), 
        height(no->esq)
    ) + 1;

    aux1->altura = MAX(
        height(no->dir),
        height(no->esq)
    ) + 1;

    return aux1;
}

//rotacao_direita

Arvore* rotacao_direita(Arvore* no)
{
    Arvore* aux1 = no->esq;
    Arvore* aux2 = no->esq->dir;

    no->esq = aux2;
    aux1->dir = no;

    no->altura = MAX(
        height(no->dir), 
        height(no->esq)
    ) + 1;

    aux1->altura = MAX(
        height(no->dir),
        height(no->esq)
    ) + 1;

    return aux1;
}

Arvore* rotacao_dreita_esquerda(Arvore* no)
{
    no->dir = rotacao_direita(no->dir);
    return rotacao_esquerda(no);
}

Arvore* rotacao_esquerda_direta(Arvore* no)
{
    no->esq = rotacao_esquerda(no->esq);
    return rotacao_direita(no);
}

//Balancear um único nó
Arvore* balanceamento(Arvore* no)
{
    int b_pai = getBalance(no);

    if(b_pai == 2)
    {
        int b_filho = getBalance(no->dir);

        if(b_filho >= 0)
        {
            no = rotacao_esquerda(no);
        }
        else//(b_filho == -1)
        {
            no = rotacao_dreita_esquerda(no);
        }
    }
    else if(b_pai == -2)
    {
        int b_filho = getBalance(no->esq);

        if(b_filho <= 0)
        {
            no = rotacao_direita(no);
        }
        else
        {
            no = rotacao_esquerda_direta(no);
        }
    }

    return no;
}

//Inserir

Arvore* inserir(Arvore* no, int valor)
{
    if(no == NULL)
    {
        Arvore* aux = (Arvore*)malloc(sizeof(Arvore));
        aux->num = valor;
        aux->altura = 1;
        aux->esq = NULL;
        aux->dir = NULL;

        no = aux;
    }
    else if(no->num < valor)
    {
        no->dir = inserir(no->dir, valor);
    }
    else if(no->num > valor)
    {
        no->esq = inserir(no->esq, valor);
    }
    else return no;

    no->altura = MAX(
        height(no->dir),
        height(no->esq)
    ) + 1;

    no = balanceamento(no);

    return no;
}

//deletar um no

Arvore* deletar_aux(Arvore* no, int valor)
{
    //eo número não existe
    if(no == NULL)
    {
        printf("Erro: Número não encontrado\n");
        return NULL;
    }

    //encontramos o nó
    else if(no->num == valor)
    {
        //O nó não tem filhos
        if(no->dir == NULL
        && no->esq == NULL)
        {
            free(no);
            return NULL;
        }
        //O nó tem filhos somente para a direita
        else if(no->esq == NULL
        && no->dir != NULL)
        {
            Arvore* aux_d = no->dir;
            free(no);
            return aux_d;
        }
        //O nó tem filhos somente para a esquerda
        else if(no->dir == NULL
        && no->esq != NULL)
        {
            Arvore* aux_e = no->esq;
            free(no);
            return aux_e;
        }
        //O nó tem filhos para ambos os lados
        else
        {
            Arvore* aux = no->dir;
            Arvore* aux_d = no->dir;

            while(aux->esq != NULL)
                aux = aux->esq;

            aux->esq = no->esq;
            free(no);
            return aux_d;
        }
    }
    else if(valor  > no->num)
    {
        no->dir = deletar_aux(no->dir, valor);
    }
    else //o nó está mais à direita na árvore
    {
        no->esq = deletar_aux(no->esq, valor);
    }

    return no;
}

Arvore* atualiza(Arvore* no)
{
    if(no == NULL) return NULL;

    no->esq = atualiza(no->esq);
    no->dir = atualiza(no->dir);

    no->altura = MAX(
        height(no->esq),
        height(no->dir)
    ) + 1;

    no = balanceamento(no);

    return no;
}

Arvore* desalocar(Arvore* raiz)
{
    if(!raiz) return NULL;

    raiz->esq = desalocar(raiz->esq);
    raiz->dir = desalocar(raiz->dir);
    free(raiz);
}

void mostrar_preordem(Arvore* no)
{
    if(!no) return;
    
    printf("%d ", no->num);
    mostrar_preordem(no->esq);
    mostrar_preordem(no->dir);
}

void mostrar_ordem(Arvore* no)
{
    if(!no) return;

    mostrar_ordem(no->esq);
    printf("%d ", no->num);
    mostrar_ordem(no->dir);
}

void mostrar_posordem(Arvore* no)
{
    if(!no) return;
    
    mostrar_posordem(no->esq);
    mostrar_posordem(no->dir);
    printf("%d ", no->num);
}

Arvore* deletar(Arvore* no, int valor)
{
    no = deletar_aux(no, valor);
    no = atualiza(no);

    return no;
}

int main()
{
    Arvore* raiz = NULL;

    raiz = inserir(raiz, 16);
    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 23);
    raiz = inserir(raiz, 7);

    raiz = deletar(raiz, 23);

    mostrar_preordem(raiz);

    return 0;
}