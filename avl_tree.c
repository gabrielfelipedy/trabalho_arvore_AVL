#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int num;
    struct No *esq, *dir;
} No;

No* inserir(No* no, int valor)
{
    if(no == NULL)
    {
        No* novo = (No*)malloc(sizeof(No));
        novo->num = valor;
        novo->dir = NULL;
        novo->esq = NULL;

        no = novo;
    }
    else if(valor >= no->num)
    {
        no->dir = inserir(no->dir, valor);
    }
    else
    {
        no->esq = inserir(no->esq, valor);
    }

    return no;
}

int busca(No* no, int valor, int achou)
{
    if(no != NULL && !achou)
    {
        if(no->num == valor) achou = 1;

        else if(valor >= no->num)
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

No* deletar(No* no, int valor)
{
    if(no == NULL)
    {
        printf("Nó %d não existe na árvore\n", valor);
        return NULL;
    }

    if(no->num == valor)
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
        & no->esq != NULL)
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
            free(aux);
            return aux_d;
        }
    }
    else if(valor >= no->num)
    {
        no->dir = deletar(no->dir, valor);
    }
    else
    {
        no->esq = deletar(no->esq, valor);
    }

    return no;
}

No* desalocar(No* no)
{
    if(no == NULL) return NULL;

    no->esq = desalocar(no->esq);
    no->dir = desalocar(no->dir);

    free(no);
    return NULL;
}

void mostrar_pre_ordem(No* no)
{
    if(no == NULL) return;

    printf("%d ", no->num);
    mostrar_pre_ordem(no->esq);
    mostrar_pre_ordem(no->dir);
}

void mostrar_ordem(No* no)
{
    if(no == NULL) return;

    mostrar_ordem(no->esq);
    printf("%d ", no->num);
    mostrar_ordem(no->dir);
}

void mostrar_pos_ordem(No* no)
{
    if(no == NULL) return;

    mostrar_pos_ordem(no->esq);
    mostrar_pos_ordem(no->dir);
    printf("%d ", no->num);
}

int main()
{
    No* raiz = NULL;

    return 0;
}