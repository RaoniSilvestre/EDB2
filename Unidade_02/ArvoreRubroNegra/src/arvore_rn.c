#include "arvore_rn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERMELHO(no) (no != NULL && no->cor == RUBRO)
#define PRETO(no) (no != NULL && no->cor == NEGRO)

void rotacao_esq(arvore_rn_t **raiz, arvore_rn_t *temp) {
    arvore_rn_t *direita = temp->dir;

    // Atualiza a subárvore esquerda do nó à direita
    temp->dir = direita->esq;
    if (temp->dir != NULL) {
        temp->dir->pai = temp;
    }

    // Atualiza o pai do nó à direita
    direita->pai = temp->pai;
    if (temp->pai == NULL) {
        // Se não há pai, a nova raiz é o nó à direita
        *raiz = direita;
    } else if (temp == temp->pai->esq) {
        // Atualiza o filho esquerdo do pai
        temp->pai->esq = direita;
    } else {
        // Atualiza o filho direito do pai
        temp->pai->dir = direita;
    }

    // Atualiza as relações entre o nó atual e o nó à direita
    direita->esq = temp;
    temp->pai = direita;
}

void rotacao_dir(arvore_rn_t **raiz, arvore_rn_t *temp) {
    arvore_rn_t *esquerda = temp->esq;

    // Atualiza a subárvore direita do nó à esquerda
    temp->esq = esquerda->dir;
    if (temp->esq != NULL) {
        temp->esq->pai = temp;
    }

    // Atualiza o pai do nó à esquerda
    esquerda->pai = temp->pai;
    if (temp->pai == NULL) {
        // Se não há pai, a nova raiz é o nó à esquerda
        *raiz = esquerda;
    } else if (temp == temp->pai->esq) {
        // Atualiza o filho esquerdo do pai
        temp->pai->esq = esquerda;
    } else {
        // Atualiza o filho direito do pai
        temp->pai->dir = esquerda;
    }

    // Atualiza as relações entre o nó atual e o nó à esquerda
    esquerda->dir = temp;
    temp->pai = esquerda;
}

arvore_rn_t *corrigir_ins(arvore_rn_t *arvore) {
    if (arvore->esq == NULL && arvore->dir == NULL && arvore->pai == NULL) {
        arvore->cor = NEGRO;
    }
    // XXX Faltam mais casos!!
    return arvore;
}

arvore_rn_t *inserir_rn(arvore_rn_t *arvore, int chave) {
    if (arvore == NULL) {
        arvore = (arvore_rn_t *)malloc(sizeof(arvore_rn_t));
        arvore->chave = chave;
        arvore->esq = NULL;
        arvore->dir = NULL;
        arvore->pai = NULL;
        return arvore;
    } else if (chave < arvore->chave) {
        arvore->esq = inserir_rn(arvore->esq, chave);
        arvore->esq->pai = arvore;
    } else if (chave > arvore->chave) {
        arvore->dir = inserir_rn(arvore->dir, chave);
        arvore->dir->pai = arvore;
    }

    return arvore;
}

arvore_rn_t *inserir(arvore_rn_t *arvore, int chave) {
    arvore = inserir_rn(arvore, chave);
    arvore = corrigir_ins(arvore);
    arvore->cor = NEGRO;
    return arvore;
}

arvore_rn_t *buscar(arvore_rn_t *arvore, int chave) {
    if (arvore == NULL) {
        return 0;
    }

    if (chave < arvore->chave) {
        return buscar(arvore->esq, chave);
    }

    if (chave > arvore->chave) {
        return buscar(arvore->dir, chave);
    }

    if (chave == arvore->chave) {
        return arvore;
    }
    return NULL;
}

arvore_rn_t *find_min(arvore_rn_t *arvore) {
    while (arvore->esq != NULL) arvore = arvore->esq;
    return arvore;
}

arvore_rn_t *remover(arvore_rn_t *arvore, int chave) {
    if (arvore == NULL) return NULL;

    if (chave < arvore->chave) {
        arvore->esq = remover(arvore->esq, chave);
    } else if (chave > arvore->chave) {
        arvore->dir = remover(arvore->dir, chave);
    } else {
        if (arvore->esq == NULL) {
            arvore_rn_t *temp = arvore->dir;
            free(arvore);
            return temp;
        } else if (arvore->dir == NULL) {
            arvore_rn_t *temp = arvore->esq;
            free(arvore);
            return temp;
        }

        arvore_rn_t *rightMin = find_min(arvore->dir);
        arvore->chave = rightMin->chave;
        arvore->dir = remover(arvore->dir, rightMin->chave);
    }
    return arvore;
}

arvore_rn_t *construir_arvore(int *chaves, int inicio, int fim, arvore_rn_t *arvore) {
    if (inicio > fim) {
        return arvore;
    }

    int meio = (inicio + fim) / 2;

    arvore = inserir(arvore, chaves[meio]);

    // XXX Dá SegFault!!!
    arvore = construir_arvore(chaves, inicio, meio + 1, arvore);
    arvore = construir_arvore(chaves, meio - 1, fim, arvore);

    return arvore;
}

arvore_rn_t *lista_p_arvore(int *chaves, int tamanho) {
    arvore_rn_t *arvore = NULL;
    if (tamanho == 0) {
        return arvore;
    }
    arvore = construir_arvore(chaves, 0, tamanho - 1, arvore);
    return arvore;
}

arvore_rn_t *desalocar(arvore_rn_t *arvore) {
    if (arvore != NULL) {
        arvore->esq = desalocar(arvore->esq);
        arvore->dir = desalocar(arvore->dir);
        free(arvore);
    }
    return NULL;
}

void inorder(arvore_rn_t *arvore) {
    if (arvore != NULL) {
        inorder(arvore->esq);
        printf("%d ", arvore->chave);
        inorder(arvore->dir);
    }
}

void imprimir_sub_arvore(arvore_rn_t *arvore, int espaços) {
    if (arvore != NULL) {
        espaços += 5;
        imprimir_sub_arvore(arvore->dir, espaços);
        printf("\n");
        for (int i = 5; i < espaços; i++) {
            printf(" ");
        }
        if (VERMELHO(arvore)) {
            printf("\e[0;31m");
        } else if (PRETO(arvore)) {
            printf("\e[0;30m");
        }
        printf("%d\e[0m", arvore->chave);
        imprimir_sub_arvore(arvore->esq, espaços);
    }
}

void imprimir_arvore(arvore_rn_t *arvore) {
    imprimir_sub_arvore(arvore, 0);
}