#include <stdio.h>
#include <stdlib.h>

//definir a árvore

typedef struct No
{
    int valor;
    struct No *dir, *esq;
    int altura;
} No;

//rotações

#define MAX(a, b) ((a > b) ? (a) : (b))

int altura(No* no)
{
    if(no == NULL) return 0;

    return no->altura;
}

int fator_balanceamento(No* no)
{
    if(no == NULL) return 0;

    return altura(no->dir) - altura(no->esq);
}

No* rotacao_esquerda(No* no)
{
    No* aux1 = no->dir;
    No* aux2 = aux1->esq;

    no->dir = aux2;
    aux1->esq = no;

    no->altura = MAX(
        altura(no->dir),
        altura(no->esq)
    ) + 1;

    aux1->altura = MAX(
        altura(aux1->dir),
        altura(aux1->esq)
    ) + 1;

    return aux1;
}

No* rotacao_direita(No* no)
{
    No* aux1 = no->esq;
    No* aux2 = aux1->dir;

    no->esq = aux2;
    aux1->dir = no;

    no->altura = MAX(
        altura(no->dir),
        altura(no->esq)
    ) + 1;

    aux1->altura = MAX(
        altura(aux1->dir),
        altura(aux1->esq)
    ) + 1;

    return aux1;
}

No* rotacao_direita_esquerda(No* no)
{
    no->dir = rotacao_direita(no->dir);
    return rotacao_esquerda(no);
}

No* rotacao_esquerda_direita(No* no)
{
    no->esq = rotacao_esquerda(no->esq);
    return rotacao_direita(no);
}

No* balancear(No* no)
{
    int bal_pai = fator_balanceamento(no);

    if(bal_pai == 2)
    {
        int bal_filho = fator_balanceamento(no->dir);

        if(bal_filho >= 0)
        {
            return rotacao_esquerda(no);
        }
        else
        {
            return rotacao_direita_esquerda(no);
        }
    }

    else if(bal_pai == -2)
    {
        int bal_filho = fator_balanceamento(no->esq);

        if(bal_filho <= 0)
        {
            return rotacao_direita(no);
        }
        else
        {
            return rotacao_esquerda_direita(no);
        }
    }

    return no;
}

No* inserir(No* no, int valor)
{
    if(no == NULL)
    {
        No* novo = (No*)malloc(sizeof(No));
        novo->valor = valor;
        novo->altura = 1;
        novo->esq = NULL;
        novo->dir = NULL;

        no = novo;
    }
    else if(valor > no->valor)
    {
        no->dir = inserir(no->dir, valor);
    }
    else if(valor < no->valor)
    {
        no->esq = inserir(no->esq, valor);
    }
    else return no;

    no->altura = MAX(
        altura(no->dir),
        altura(no->esq)
    ) + 1;

    return balancear(no);
}

No* deletar_aux(No* no, int valor)
{
    if(no == NULL)
    {
        printf("Nó não encontrado\n");
        return NULL;
    }

    if(no->valor == valor)
    {
        if(no->dir == NULL
        && no->esq == NULL)
        {
            free(no);
            return NULL;
        }
        else if(no->dir != NULL
        && no->esq == NULL)
        {   
            No* aux = no->dir;
            free(no);
            return aux;
        }
        else if(no->dir == NULL
        && no->esq != NULL)
        {
            No* aux = no->esq;
            free(no);
            return aux;
        }
        else
        {
            No* aux = no->dir;
            No* aux_d = no->dir;

            while(aux->esq != NULL)
                aux = aux->esq;

            aux->esq = no->esq;

            free(no);
            return aux_d;
        }
    }
    else if(valor > no->valor)
    {
        no->dir = deletar_aux(no->dir, valor);
    }
    else
    {
        no->esq = deletar_aux(no->esq, valor);
    }

    return no;
}

No* atualiza(No* no)
{
    if(no == NULL) return NULL;

    no->esq = atualiza(no->esq);
    no->dir = atualiza(no->dir);

    no->altura = MAX(
        altura(no->dir),
        altura(no->esq)
    ) + 1;

    return balancear(no);
}

int busca(No* no, int valor, int achou)
{
    if(no != NULL && !achou)
    {
        if(no->valor == valor) achou = 1;

        else if(valor >= no->valor)
        {
            achou = busca(no->dir, valor, achou);
        }
        else
        {
            achou = busca(no->esq, valor, achou);
        }
    }

    return achou;
}

No* desalocar(No* no)
{
    if(!no) return NULL;

    no->esq = desalocar(no->esq);
    no->dir = desalocar(no->dir);
    free(no);
}

void mostrar_pre_ordem(No* no)
{
    if(!no) return;

    printf("%d ", no->valor);
    mostrar_pre_ordem(no->esq);
    mostrar_pre_ordem(no->dir);
}

void mostrar_ordem(No* no)
{
    if(!no) return;

    mostrar_ordem(no->esq);
    printf("%d ", no->valor);
    mostrar_ordem(no->dir);
}

void mostrar_pos_ordem(No* no)
{
    if(!no) return;

    mostrar_pos_ordem(no->esq);
    mostrar_pos_ordem(no->dir);
    printf("%d ", no->valor);
}

No* deletar(No* no, int valor)
{
    no = deletar_aux(no, valor);
    return atualiza(no);
}

int main()
{
    No* raiz = NULL;
    raiz = inserir(raiz, 1);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 19);
    raiz = inserir(raiz, 3);
    raiz = inserir(raiz, 18);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 17);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 16);
    raiz = inserir(raiz, 6);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 7);
    raiz = inserir(raiz, 14);
    raiz = inserir(raiz, 8);
    raiz = inserir(raiz, 13);
    raiz = inserir(raiz, 9);
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 11);
    
    mostrar_pre_ordem(raiz);

    return 0;
}