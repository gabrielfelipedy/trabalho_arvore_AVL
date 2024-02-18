#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define ERROR -1

//Definindo o nó da árvore

typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
    int balanceamento; //fator que vai de (0, 1 ou -1)
} No;

//Função que cria um novo nó:

No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->valor = valor;
    novo->balanceamento = 0;

    return novo;
}

//Função que calcula a altura de uma árvore ou sub-árvore

int altura(No* no) {
    if(!no) return ERROR;

    else return 1 + MAX(altura(no->esquerda), altura(no->direita));
}

//Funcao que verifica se uma árvore é AVL

bool ehAVL(No* no) {
    int alt_esquerda, alt_direta;
    bool ok = true;

    if(no) {
        ok = ehAVL(no->esquerda);

        //Se passou no primeiro teste
        if(ok) ok = ehAVL(no->direita);

        if(ok) {
            alt_direta = altura(no->direita);
            alt_esquerda = altura(no->esquerda);

            if(alt_esquerda - alt_direta > 1 || alt_esquerda - alt_direta < -1) return false;
        }
    }
    return true;
}

bool ehAVL2(No* no, int* altura) {
    if(!no) {
        *altura = -1;
        return true;
    }

    bool res;
    int alt_esquerda, alt_direta;

    res = ehAVL2(no->direita, &alt_direta);
    if(!res) return false;

    res = ehAVL2(no->esquerda, &alt_esquerda);
    if(!res) return false;

    if(alt_direta - alt_esquerda != no->balanceamento)
        printf("Errou o campo bal de %i, otário!", no->valor);

    if((alt_direta - alt_esquerda < -1) || (alt_direta - alt_esquerda > 1)) return false;


    *altura = MAX(alt_direta, alt_esquerda) + 1;
    return true;
}

int atualizarBalanceamento(No* raiz) {
    if(!raiz) return 0;

    int direita = atualizarBalanceamento(raiz->direita);
    int esquerda = atualizarBalanceamento(raiz->esquerda);

    raiz->balanceamento = direita - esquerda;

    return MAX(direita, esquerda) + 1;
}

//********
//ROTAÇÕES
//********