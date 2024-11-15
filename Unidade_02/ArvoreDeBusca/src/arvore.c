#include "arvore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

arvore_t *inserir(arvore_t *arvore, int chave) {
    if (arvore == NULL) {
        arvore = (arvore_t *)malloc(sizeof(arvore_t));
        arvore->chave = chave;
        arvore->esq = NULL;
        arvore->dir = NULL;
    } else if (chave < arvore->chave) {
        arvore->esq = inserir(arvore->esq, chave);
    } else if (chave > arvore->chave) {
        arvore->dir = inserir(arvore->dir, chave);
    }
    return arvore;
}

arvore_t *buscar(arvore_t *arvore, int chave) {
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

arvore_t *remover(arvore_t *arvore, int chave) {
    if (arvore == NULL) return NULL;

    if (chave < arvore->chave) {
        arvore->esq = remover(arvore->esq, chave);
    } else if (chave > arvore->chave) {
        arvore->dir = remover(arvore->dir, chave);
    } else {
        if (arvore->esq == NULL) {
            arvore_t *temp = arvore->dir;
            free(arvore);
            return temp;
        } else if (arvore->dir == NULL) {
            arvore_t *temp = arvore->esq;
            free(arvore);
            return temp;
        }

        arvore_t *rightMin = find_min(arvore->dir);
        arvore->chave = rightMin->chave;
        arvore->dir = remover(arvore->dir, rightMin->chave);
    }
    return arvore;
}

arvore_t *find_min(arvore_t *arvore) {
    while (arvore->esq != NULL) arvore = arvore->esq;
    return arvore;
}

arvore_t *desalocar(arvore_t *arvore) {
    if (arvore != NULL) {
        arvore->esq = desalocar(arvore->esq);
        arvore->dir = desalocar(arvore->dir);
        free(arvore);
    }
    return NULL;
}

void inorder(arvore_t *arvore) {
    if (arvore != NULL) {
        inorder(arvore->esq);
        printf("%d ", arvore->chave);
        inorder(arvore->dir);
    }
}
