#include "arvore.h"
#include <stdlib.h>

arvore_t *inserir(arvore_t *arvore, int chave)
{
    if (arvore == NULL) {
        arvore = (arvore_t*) malloc(sizeof(arvore_t));
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

int buscar(arvore_t *arvore, int chave)
{
    if (arvore == NULL) {
        return 0;
    } else if (chave < arvore->chave) {
        return buscar(arvore->esq, chave);
    } else if (chave > arvore->chave) {
        return buscar(arvore->dir, chave);
    } else if (chave == arvore->chave) {
        return 1;
    }
    return 0;
}

arvore_t *desalocar(arvore_t *arvore) {
    if (arvore != NULL) {
        arvore->esq = desalocar(arvore->esq);
        arvore->dir = desalocar(arvore->dir);
        free(arvore);
    }
    return NULL;
}