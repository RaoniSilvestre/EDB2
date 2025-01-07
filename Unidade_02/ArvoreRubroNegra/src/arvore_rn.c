#include "arvore_rn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERMELHO(no) (no != NULL && no->cor == RUBRO)
#define PRETO(no) (no != NULL && no->cor == NEGRO)

void troca_cores(arvore_rn_t *arvore) {
    arvore->cor = RUBRO;
    if (arvore->esq != NULL) {
        arvore->esq->cor = NEGRO;
    }
    if (arvore->dir != NULL) {
        arvore->dir->cor = NEGRO;
    }
}

arvore_rn_t *corrigir_ins(arvore_rn_t *arvore) {
    if (VERMELHO(arvore->esq) && VERMELHO(arvore->dir)) {
        troca_cores(arvore);
    }

    if (VERMELHO(arvore->esq) && VERMELHO(arvore->esq->esq)) {
        arvore = rotacao_dir(arvore);
    }

    if (PRETO(arvore->esq) && VERMELHO(arvore->dir)) {
        arvore = rotacao_esq(arvore);
    }

    return arvore;
}

arvore_rn_t *inserir_rn(arvore_rn_t *arvore, int chave) {
    if (arvore == NULL) {
        arvore = (arvore_rn_t *)malloc(sizeof(arvore_rn_t));
        arvore->chave = chave;
        arvore->cor = RUBRO;
        arvore->esq = NULL;
        arvore->dir = NULL;
        return arvore;
    } else if (chave < arvore->chave) {
        arvore->esq = inserir(arvore->esq, chave);
    } else if (chave > arvore->chave) {
        arvore->dir = inserir(arvore->dir, chave);
    }

    arvore = corrigir_ins(arvore);
    return arvore;
}

arvore_rn_t *inserir(arvore_rn_t *arvore, int chave) {
    arvore = inserir_rn(arvore, chave);
    arvore->cor = NEGRO;
    return arvore;
}

arvore_rn_t *rotacao_esq(arvore_rn_t *arvore) {
    if (arvore == NULL || arvore->dir == NULL) {
        return arvore;
    }

    arvore_rn_t *nova_raiz = arvore->dir;
    arvore->dir = nova_raiz->esq;
    nova_raiz->esq = arvore;
    nova_raiz->cor = arvore->cor;

    return nova_raiz;
}

arvore_rn_t *rotacao_dir(arvore_rn_t *arvore) {
    if (arvore == NULL || arvore->esq == NULL) {
        return arvore;
    }

    arvore_rn_t *nova_raiz = arvore->esq;
    arvore->esq = nova_raiz->dir;
    nova_raiz->dir = arvore;
    nova_raiz->cor = arvore->cor;

    return nova_raiz;
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

void imprimir_sub_arvore(arvore_rn_t *arvore, int espaços) {
    if (arvore != NULL) {
        espaços += 5;
        imprimir_sub_arvore(arvore->dir, espaços);
        printf("\n");
        for (int i = 5; i < espaços; i++) {
            prinf(" ");
        }
        printf("%d", arvore->chave);
        imprimir_sub_arvore(arvore->esq, espaços);
    }
}

void imprimir_arvore(arvore_rn_t *arvore) {
    imprimir_sub_arvore(arvore, 0);
}