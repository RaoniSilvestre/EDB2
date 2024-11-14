#pragma once

typedef struct arvore_t {
    int chave;
    struct arvore_t *esq;
    struct arvore_t *dir;
} arvore_t;

arvore_t *inserir(arvore_t *arvore, int chave);
arvore_t *remover(arvore_t *arvore, int chave);
arvore_t *lista_p_arvore(int *chaves, int tamanho);
int buscar(arvore_t *arvore, int chave);

arvore_t *desalocar(arvore_t *arvore);