#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int num;
    struct No *esq, *dir;
} No;

//Estrutura auxiliar para consultas em ordem, pre ordem e pos ordem

typedef struct Arvore
{
    No* num;
    struct Arvore* next;
} Arvore;

void insert(No** raiz, int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->num = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(!*raiz) {
        *raiz = novo;
        printf("Numero %d inserido na árvore\n", valor);
        return;
    }
    
    No* aux = *raiz;
    int achou = 0;

    while(!achou)
    {
        if(valor < aux->num)
        {
            if(aux->esq == NULL) 
            {
                aux->esq = novo;
                achou = 1;
            }
            else aux = aux->esq;
        }
        else if(valor >= aux->num) {
            if(aux->dir == NULL) 
            {
                aux->dir = novo;
                achou = 1;
            }
            else aux = aux->dir;
        }
    }
    free(aux);
    printf("Numero %d inserido na árvore\n", valor);
}

void delete(No** raiz, int valor) {
    if(*raiz == NULL) {
        printf("Arvore vazia\n");
        return;
    }

    No* aux = *raiz;
    int achou = 0;

    while(!achou && aux != NULL)
    {
        if(aux->num == valor) achou = 1;

        else if(aux->num > valor) // O numero esta na esquerda
            aux = aux->esq;
        else //O numero esta na direita
            aux = aux->dir;
        
    }

    if(!achou) {
        printf("Numero não encontrado\n");
        return;
    }

    if(aux != *raiz) { //O no nao eh a raiz
        //Sera necessario achar o ponteiro anterior
        No* anterior = *raiz;

        while(anterior->dir != aux &&
                anterior->esq != aux)
        {
            if(anterior->num > valor)
                anterior = anterior->esq;
            else 
                anterior = anterior->dir;
        }

        //Verificar se é um nó folha
        if(aux->dir == NULL && aux->esq == NULL)
        {
            if(anterior->dir == aux)
                anterior->dir = NULL;
            else 
                anterior->esq = NULL;

            free(aux);
            return;
        }

        //Agora verificamos o tipo de nó que vamos excluir

        //Se for um nó que possui somente filhos para a direta:

        else if(aux->dir != NULL && aux->esq == NULL)
        {
            if(anterior->dir == aux)
                anterior->dir = aux->dir;
            else
                anterior->esq = aux->dir;

            free(aux);
            return;
        }

        //Se for um nó que possui somente filhos para a esquerda:

        else if(aux->esq != NULL && aux->dir == NULL)
        {
            if(anterior->dir == aux)
                anterior->dir = aux->esq;
            else
                anterior->esq = aux->esq;

            free(aux);
            return;
        }

        //Se for um nó que possui filhos pra ambos os lados
        else
        {
            No* aux2 = NULL; //terá o pedaço de árvore que faltou

            if(anterior->dir == aux)
                anterior->dir = aux->dir;

            else
                anterior->esq = aux->dir;

            aux2 = aux->esq;

            //Vamos recolocar o pedaço de árvore faltante

            aux = anterior;
            while(aux != NULL)
            {
                if(aux->num < aux2->num) //Sera inserido na direita
                {
                    if(aux->dir == NULL)
                    {
                        aux->dir = aux2;
                        aux = NULL;
                    }
                    else
                        aux = aux->dir;
                }
                else
                {
                    if(aux->esq == NULL)
                    {
                        aux->esq = aux2;
                        aux = NULL;
                    }
                    else
                        aux = aux->esq;
                }
            }
        }
    }
    else { //Vamos excluir a raiz
        if(aux->dir == NULL && aux->esq == NULL)
        {
            free(aux);
            *raiz = NULL;
        }
        //Voltamos aos 3 casos:

        //Raiz com filhos para a direita

        else if(aux->dir != NULL && aux->esq == NULL)
        {
            *raiz = aux->dir;
            free(aux);
        }
        //Raiz com filhos para a esquerda
        else if(aux->esq != NULL && aux->dir == NULL)
        {
            *raiz = aux->esq;
            free(aux);
        }
        //Raiz com filhos para ambos os lados
        else
        {
            *raiz = aux->dir;
            No* aux2 = aux->esq;

            aux = *raiz;

            while(aux != NULL)
            {
                if(aux->num < aux2->num) 
                {
                    if(aux->dir == NULL)
                    {
                        aux->dir = aux2;
                        aux = NULL;
                    }
                    else
                        aux = aux->dir;
                }
                else
                {
                    if(aux->esq == NULL)
                    {
                        aux->esq = aux2;
                        aux = NULL;
                    }
                    else
                        aux = aux->esq;
                }
            }
        }
    }
}

//Funcoes de busca numa arvore binaria

//consulta singular

No* buscar(No** raiz, int valor)
{
    if(raiz == NULL)
    {
        printf("Árvore vazia\n");
        return NULL;
    }

    No* aux = *raiz;

    while(aux != NULL)
    {
        if(aux->num == valor) return aux;

        if(aux->num >= valor)
            aux = aux->dir;
        else
            aux = aux->esq;
    }
    

    return NULL;
}

//consulta em pré-ordem

void consulta_pre_ordem(No* raiz)
{
    No* aux = raiz;
    Arvore* topo = NULL;

    do
    {
        Arvore* aux_pilha = NULL;

        while(aux != NULL)
        {
            aux_pilha = (Arvore*)malloc(sizeof(Arvore));
            printf("%d ", aux->num);
            aux_pilha->num = aux;
            aux_pilha->next = topo;
            topo = aux_pilha;

            aux = aux->esq;    
        }

        if(topo != NULL)
        {
            aux_pilha = topo;
            topo = topo->next;
            aux = aux_pilha->num->dir;
        }
    } while (topo != NULL || aux != NULL);
    
}

//consulta em ordem

void consulta_em_ordem(No* raiz)
{
    No* aux = raiz;
    Arvore* topo = NULL;

    do
    {
        Arvore* aux_pilha = NULL;

        while(aux != NULL)
        {
            aux_pilha = (Arvore*)malloc(sizeof(Arvore));
            aux_pilha->num = aux;
            aux_pilha->next = topo;
            topo = aux_pilha;

            aux = aux->esq;
        }

        if(topo != NULL)
        {
            aux_pilha = topo;
            printf("%d ", aux_pilha->num->num);
            aux = topo->num->dir;

            topo = topo->next;
        }
    } while (topo != NULL || aux != NULL);
}

//consulta em pós ordem

void consulta_pos_ordem(No* raiz)
{
    No* aux = raiz;
    Arvore* topo = NULL;

    do
    {
        do
        {
            while(aux != NULL)
            {
                Arvore* aux_pilha = (Arvore*)malloc(sizeof(Arvore));
                aux_pilha->num = aux;
                aux_pilha->next = topo;
                topo = aux_pilha;

                aux = aux->esq;
            }

            if(topo->num->dir != NULL)
            {
                aux = topo->num->dir;
            }
        } while(aux != NULL);

        if(topo != NULL)
        {
            printf("%d ", topo->num->num);

            if(topo->next != NULL)
            {
                if(topo->next->num->dir != NULL
                && topo->next->num->dir != topo->num)
                {
                    aux = topo->next->num->dir;
                    topo = topo->next;
                }
                else
                {
                    while(topo->next != NULL
                    && topo->next->num->dir == topo->num)
                    {
                        topo = topo->next;
                        printf("%d ", topo->num->num);
                    }

                    topo = topo->next;

                    if(topo != NULL)
                    {
                        aux = topo->num->dir;
                    }
                    else
                    {
                        aux = NULL;
                    }
                }
            }
            else
            {
                topo = topo->next;
                aux = NULL;
            }
        }
    } while (topo != NULL || aux != NULL);   
}

//esvaziar a árvore

void empty(No** raiz)
{
    No* aux = *raiz;
    Arvore* topo = NULL;

    Arvore* aux_pilha = NULL;

    do
    { 
        while(aux != NULL)
        {
            aux_pilha = (Arvore*)malloc(sizeof(Arvore));
            aux_pilha->num = aux;
            aux_pilha->next = topo;
            topo = aux_pilha;

            aux = aux->esq;
        }

        if(topo != NULL)
        {
            aux_pilha = topo;
            topo = topo->next;
            aux = aux_pilha->num->dir;
        }
    } while (topo != NULL || aux != NULL);

    aux_pilha = topo;
    while(aux_pilha != NULL)
    {
        topo = topo->next;
        free(topo->num);
        free(aux_pilha);
        aux_pilha = topo;
    }


    *raiz = NULL;
}

int main()
{
    No* raiz = NULL;

    return 0;
}