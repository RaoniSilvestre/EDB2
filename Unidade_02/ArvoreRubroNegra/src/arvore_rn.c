#include "arvore_rn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

arvore_rn_t *inserir(arvore_rn_t *arvore, int chave) {
    if (arvore == NULL) {
        arvore = (arvore_rn_t *)malloc(sizeof(arvore_rn_t));
        arvore->chave = chave;
        arvore->cor = RUBRO;
        arvore->esq = NULL;
        arvore->dir = NULL;
    } else if (chave < arvore->chave) {
        arvore->esq = inserir(arvore->esq, chave);
    } else if (chave > arvore->chave) {
        arvore->dir = inserir(arvore->dir, chave);
    }
    return arvore;
}

arvore_rn_t *rotacao_esq(arvore_rn_t *arvore) {
    if (arvore == NULL || arvore->dir == NULL) {
        return arvore;
    }

    arvore_rn_t *nova_arvore = arvore->dir;
    arvore_rn_t *subarvore_dir = nova_arvore->esq;

    nova_arvore->esq = arvore;
    arvore->dir = subarvore_dir;

    return arvore;
}

arvore_rn_t *rotacao_dir(arvore_rn_t *arvore) {
    if (arvore == NULL || arvore->esq == NULL) {
        return arvore;
    }

    arvore_rn_t *nova_arvore = arvore->esq;
    arvore_rn_t *subarvore_esq = nova_arvore->dir;

    nova_arvore->dir = arvore;
    arvore->esq = subarvore_esq;

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

    arvore = construir_arvore(chaves, inicio, meio + 1, arvore);
    arvore = construir_arvore(chaves, meio - 1, fim, arvore);

    return arvore;
}

arvore_rn_t *lista_p_arvore(int *chaves, int tamanho) {
    arvore_rn_t *arvore = NULL;
    if (tamanho = 0) {
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
