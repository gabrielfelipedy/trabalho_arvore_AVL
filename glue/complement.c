#include <stdio.h>

#define MAX(a, b) ((a > b) ? (a) : (b))

typedef struct No
{
    int valor;
    struct No *dir, *esq;
    int altura;
} No;

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