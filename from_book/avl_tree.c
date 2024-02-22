#include <stdio.h>
#include <stdlib.h>

//Definindo os nós

typedef struct No
{
    int num, alt_d, alt_e;
    struct No *dir, *esq;
} No;

No* rotacao_esquerda(No* aux)
{
    No* aux1 = aux->dir;
    No* aux2 = aux1->esq;

    //***************   
    aux->dir = aux2;
    aux1->esq = aux;
    //***************

    //Atualizar a altura

    if(aux->dir == NULL)
    {
        aux->alt_d = 0;
    }
    else if(aux->dir->alt_e > aux->dir->alt_d)
    {
        aux->alt_d = aux->dir->alt_e + 1;
    }
    else
    {
        aux->alt_d = aux->dir->alt_d + 1;
    }

    if(aux1->esq->alt_e > aux1->esq->alt_d)
    {
        aux1->alt_e = aux1->esq->alt_e + 1;
    }
    else
    {
        aux1->alt_e = aux1->esq->alt_d + 1;
    }

    return aux1;
}

No* rotacao_direita(No* aux)
{
    No* aux1 = aux->esq;
    No* aux2 = aux1->dir;

    //***************
    aux->esq = aux2;
    aux1->dir = aux;
    //****************

    if(aux->esq == NULL)
    {
        aux->alt_e = 0;
    }
    else if(aux->esq->alt_d > aux->esq->alt_e)
    {
        aux->alt_e = aux->esq->alt_d + 1;
    }
    else
    {
        aux->alt_e = aux->esq->alt_e + 1;
    }

    if(aux1->dir->alt_d > aux1->dir->alt_e)
    {
        aux1->alt_d = aux1->dir->alt_d + 1;
    }
    else
    {
        aux1->alt_d = aux1->dir->alt_e + 1;
    }

    return aux1;
}

No* balanceamento(No* aux) //Balanceia somente um nó por vez
{
    int diferenca = aux->alt_d - aux->alt_e;

    if(diferenca == 2)
    {
        int diferenca_filho = aux->dir->alt_d - aux->dir->alt_e;

        if(diferenca_filho >= 0)
        {
            aux = rotacao_esquerda(aux);
        }
        else
        {
            aux->dir = rotacao_direita(aux->dir);
            aux = rotacao_esquerda(aux);
        }
    }

    else if(diferenca == -2)
    {
        int diferenca_filho = aux->esq->alt_d - aux->esq->alt_e;

        if(diferenca_filho <= 0)
        {
            aux = rotacao_direita(aux);
        }
        else
        {
            aux->esq = rotacao_esquerda(aux->esq);
            aux = rotacao_direita(aux);
        }
    }

    return aux;
}

//Inserir na árvore

No* insert(No* aux, int valor) {
    No* novo;
    
    if(aux == NULL)
    {
        novo = (No*)malloc(sizeof(No));
        novo->num = valor;
        novo->alt_d = 0;
        novo->alt_e = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        aux = novo;
    }

    else if(valor < aux->num)
    {
        aux->esq = insert(aux->esq, valor);

        //Atualizar as alturas
        if(aux->esq->alt_d > aux->esq->alt_e)
        {
            aux->alt_e = aux->esq->alt_d + 1;
        }
        else
        {
            aux->alt_e = aux->esq->alt_e + 1;
        }

        aux = balanceamento(aux);
    }
    else
    {
        aux->dir = insert(aux->dir, valor);

        if(aux->dir->alt_d > aux->dir->alt_e)
        {
            aux->alt_d = aux->dir->alt_d + 1;
        }
        else
        {
            aux->alt_d = aux->dir->alt_e + 1;
        }

        aux = balanceamento(aux);
    }

    return aux;
}

int consultar(No* aux, int num, int achou)
{
    if(aux != NULL && !achou)
    {
        if(aux->num == num) achou = 1;

        else if(num < aux->num)
        {
            achou = consultar(aux->esq, num, achou);
        }
        else
        {
            achou = consultar(aux->dir, num, achou);
        }
    }

    return achou;
}

void mostrar_pre_ordem(No* aux)
{
    if(aux != NULL)
    {
        printf("%d ", aux->num);
        mostrar_pre_ordem(aux->esq);
        mostrar_pre_ordem(aux->dir);
    }
}

void mostrar_ordem(No* aux) //traversal in order
{
    if(aux != NULL)
    {
        mostrar_ordem(aux->esq);
        printf("%d ", aux->num);
        mostrar_ordem(aux->dir);
    }
}

void mostrar_pos_ordem(No* aux)
{
    if(aux != NULL)
    {
        mostrar_pos_ordem(aux->esq);
        mostrar_pos_ordem(aux->dir);
        printf("%d ", aux->num);
    }
}

No* remover(No* aux, int num)
{
    if(aux->num == num)
    {
        //Se não tiver filhos, ou seja, é uma folha
        if(aux->esq == aux->dir)
        {
            free(aux);
            return NULL;
        }

        //tem filhos só pra direita
        else if(aux->esq == NULL)
        {
            No* aux_d = aux->dir;
            free(aux);
            return aux_d;
        }

        //tem filhos só pra esquerda
        else if(aux->dir == NULL)
        {
            No* aux_e = aux->esq;
            free(aux);
            return aux_e;
        }

        //tem filhos pros dois lados
        else
        {
            No* aux_d = aux->dir;
            No* aux2 = aux->dir;

            //procura uma posição vazia
            while(aux2->esq != NULL)
            {
                aux2 = aux2->esq;
            }

            aux2->esq = aux->esq;
            free(aux);
            return aux_d;
        }
    }
    else if(aux->num <= num)
    {
        aux->dir = remover(aux->dir, num);
    }
    else
    {
        aux->esq = remover(aux->esq, num);
    }

    return aux;
}

//Atualiza a árvore por completo
No* atualiza(No* aux)
{
    if(aux != NULL)
    {
        aux->esq = atualiza(aux->esq);

        if(aux->esq == NULL)
        {
            aux->alt_e= 0;
        }
        else if(aux->esq->alt_d > aux->esq->alt_e)
        {
            aux->alt_e = aux->esq->alt_d + 1;
        }
        else
        {
            aux->alt_e = aux->esq->alt_e + 1;
        }

        aux->dir = atualiza(aux->dir);

        if(aux->dir == NULL)
        {
            aux->alt_d=  0;
        }
        else if(aux->dir->alt_d > aux->dir->alt_e)
        {
            aux->alt_d = aux->dir->alt_d + 1;
        }
        else
        {
            aux->alt_d = aux->dir->alt_e + 1;
        }

        aux = balanceamento(aux);
    }

    return aux;
}

No* desalocar(No* aux)
{
    if(aux != NULL)
    {
        aux->esq = desalocar(aux->esq);
        aux->dir = desalocar(aux->dir);
        free(aux);
    }

    return NULL;
}

int main()
{
    No* raiz = NULL;

    raiz = insert(raiz, 16);
    raiz = insert(raiz, 6);
    raiz = insert(raiz, 23);
    raiz = insert(raiz, 7);

    raiz = remover(raiz, 23);
    raiz = atualiza(raiz);

    mostrar_pre_ordem(raiz);

    return 0;
}