#include <stdio.h>
#include <stdlib.h>

#define VAZIO NULL

typedef struct No
{
    int valor;
    struct No* direita;
    struct No* esquerda;
} No;

//adicionar coisas na arvore
void inserir(No** raiz, int valor)
{
    //criar um novo nó
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->direita = VAZIO;
    novo->esquerda = VAZIO;

    if(*raiz == VAZIO)
    {
        *raiz = novo;
        printf("Numero %d inserido na árvore\n", valor);
        return;
    }

    No* aux = *raiz; //usado só pra percorrer a arvore

    while(aux != VAZIO)
    {
        if(aux->valor <= valor)
            aux = aux->direita;
        else
            aux = aux->esquerda;
    }

    aux = novo;
    free(aux);
    printf("Numero %d inserido na árvore\n", valor);
}

//busca
void buscar(No* raiz, int valor)
{
    No* aux = raiz; //variavel auxiliar para percorrer a arvore
    int achou = 0;

    while(!achou && aux != VAZIO)
    {
        if(aux->valor == valor)
        {
            achou = 1;
            printf("O número %d existe na árvore\n", valor);
            return;
        }

        if(aux->valor <= valor)
        {
            aux = aux->direita;
        }
        else
            aux = aux->esquerda;
    }

    if(!achou)
    {
        printf("O número %d não existe na árvore\n", valor);
    }
}

//deleção

void delete(No** raiz, int valor)
{
    if(*raiz == VAZIO)
    {
        printf("A arvore está vazia\n");
        return;
    }

    //PRIMEIRAMENTE TEM QUE BUSCAR O VALOR NA ÁRVORE, BURRO!!!!!!!!!!!!!!!!!

    No* aux = *raiz;
    int achou = 0;

    while(!achou && aux != VAZIO)
    {
        if(aux->valor == valor) achou = 1;

        else if(aux->valor <= valor)
            aux = aux->direita;
        else    
            aux = aux->esquerda;
    }

    if(!achou)
    {
        printf("Número não foi encontrado\n");
        return;
    }

    if(aux == *raiz)
    {
        //nao tem filhos
        if(aux->direita == VAZIO && aux->esquerda == VAZIO)
        {
            free(aux);
            *raiz = VAZIO;
            return;
        }

        //tem filhos somente pra direita

        else if(aux->direita != VAZIO && aux->esquerda == VAZIO)
        {
            *raiz = aux->direita;
            free(aux);
            return;
        }


        //tem filhos somente pra esquerda

        else if(aux->direita == VAZIO && aux->esquerda != VAZIO)
        {
            *raiz = aux->esquerda;
            free(aux);
            return;
        }

        //tem filhos pros dois lados

        else
        {
            *raiz = aux->direita;
            No* aux2 = aux->esquerda;

            aux = *raiz;

            while(aux != VAZIO)
            {
                if(aux->valor <= aux2->valor)
                {
                    if(aux->direita == VAZIO)
                    {
                        aux->direita = aux2;
                        aux = VAZIO;
                    }
                    else
                        aux = aux->direita;
                }
                else
                {
                    if(aux->esquerda == VAZIO)
                    {
                        aux->esquerda = aux2;
                        aux = VAZIO;
                    }
                    else
                        aux = aux->esquerda;
                }
            }
        }
    }
    else
    {
        //Buscar o cara anterior

        No* anterior = *raiz;

        while(anterior->direita != aux && anterior->esquerda != aux)
        {
            if(anterior->valor <= valor)
            {
                anterior = anterior->direita;
            }
            else
            {
                anterior = anterior->esquerda;
            }
        }

        //Nó folha

        if(aux->direita == NULL && aux->esquerda == NULL)
        {
            if(anterior->direita <= aux)
                anterior->direita = NULL;
            else
                anterior->esquerda = NULL;

            free(aux);
            return;
        }
        

        //No do meio com filhos pra direta

        else if(aux->direita != NULL && aux->esquerda == NULL)
        {
            if(anterior->direita <= aux)
                anterior->direita = aux->direita;
            else
                anterior->esquerda = aux->direita;

            free(aux);
            return;
        }

        //No do meio com filhos pra esquerda

        else if(aux->direita == NULL && aux->esquerda != NULL)
        {
             if(anterior->direita <= aux)
                anterior->direita = aux->esquerda;
            else
                anterior->esquerda = aux->esquerda;

            free(aux);
            return;
        }

        //No do meio com filhos pros dois
        else
        {
            if(anterior->direita == aux)
            {
                anterior->direita = aux->direita;
            }
            else
                anterior->esquerda = aux->direita;

            No* aux2 = aux->esquerda;
            aux = anterior;

            while(aux != NULL)
            {
                if(aux->valor <= aux2->valor)
                {
                    if(aux->direita == NULL)
                    {
                        aux->direita = aux2;
                        aux = NULL;
                    }
                    else
                        aux = aux->direita;
                }
                else
                {
                    if(aux->esquerda == NULL)
                    {
                        aux->esquerda = aux2;
                        aux = NULL;
                    }
                    else
                        aux = aux->esquerda;
                }
            }
        }
    }
}

int main()
{
    No* raiz = VAZIO; //cria uma arvore vazia

    return 0;
}