#include "arvore_rn.h"

#include <stdio.h>

#define VERMELHO(no) (no != NULL && no->cor == RUBRO)
#define PRETO(no) (no != NULL && no->cor == NEGRO)

arvore_rn_t *raiz = NULL;

void rotacao_esq(arvore_rn_t *x) {
    arvore_rn_t *y = x->dir;
    x->dir = y->esq;
    if (y->esq != NULL)
        y->esq->pai = x;

    y->pai = x->pai;
    if (x->pai == NULL)
        raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;

    y->esq = x;
    x->pai = y;
}

void rotacao_dir(arvore_rn_t *x) {
    arvore_rn_t *y = x->esq;
    x->esq = y->dir;
    if (y->dir != NULL)
        y->dir->pai = x;

    y->pai = x->pai;
    if (x->pai == NULL)
        raiz = y;
    else if (x == x->pai->dir)
        x->pai->dir = y;
    else
        x->pai->esq = y;

    y->dir = x;
    x->pai = y;
}

void corrigir_balanceamento(arvore_rn_t *no) {
    arvore_rn_t *pai = NULL;
    arvore_rn_t *avo = NULL;

    while (no != raiz && no->cor == RUBRO && no->pai->cor == RUBRO) {
        pai = no->pai;
        avo = pai->pai;

        if (pai == avo->esq) {
            arvore_rn_t *tio = avo->dir;

            if (tio != NULL && tio->cor == RUBRO) {
                avo->cor = RUBRO;
                pai->cor = NEGRO;
                tio->cor = NEGRO;
                no = avo;
            } else {
                if (no == pai->dir) {
                    rotacao_esq(pai);
                    no = pai;
                    pai = no->pai;
                }
                rotacao_dir(avo);
                cor_t temp = pai->cor;
                pai->cor = avo->cor;
                avo->cor = temp;
                no = pai;
            }
        } else {
            arvore_rn_t *tio = avo->esq;

            if (tio != NULL && tio->cor == RUBRO) {
                avo->cor = RUBRO;
                pai->cor = NEGRO;
                tio->cor = NEGRO;
                no = avo;
            } else {
                if (no == pai->esq) {
                    rotacao_dir(pai);
                    no = pai;
                    pai = no->pai;
                }
                rotacao_esq(avo);
                cor_t temp = pai->cor;
                pai->cor = avo->cor;
                avo->cor = temp;
                no = pai;
            }
        }
    }

    raiz->cor = NEGRO;
}

arvore_rn_t *inserir(arvore_rn_t *arvore, arvore_rn_t *no) {
    if (arvore == NULL) {
        return no;
    } else if (no->chave < arvore->chave) {
        arvore->esq = inserir(arvore->esq, no);
        arvore->esq->pai = arvore;
    } else if (no->chave > arvore->chave) {
        arvore->dir = inserir(arvore->dir, no);
        arvore->dir->pai = arvore;
    }

    return arvore;
}

arvore_rn_t *criar_no(int chave) {
    arvore_rn_t *novo_no = (arvore_rn_t *)malloc(sizeof(arvore_rn_t));
    novo_no->chave = chave;
    novo_no->cor = RUBRO; // Nós recém-criados são rubros
    novo_no->pai = NULL;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    return novo_no;
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

arvore_rn_t *lista_p_arvore(int *chaves, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        arvore_rn_t *novo_no = criar_no(chaves[i]);
        raiz = inserir(raiz, novo_no);
        corrigir_balanceamento(novo_no);
    }
    return raiz;
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
            printf("\e[0;41m");
        } else if (PRETO(arvore)) {
            printf("\e[0;40m");
        }
        printf("%d\e[0m", arvore->chave);
        imprimir_sub_arvore(arvore->esq, espaços);
    }
}

void imprimir_arvore(arvore_rn_t *arvore) {
    printf("Visualização da árvore deitada:\n");
    imprimir_sub_arvore(arvore, 0);
}