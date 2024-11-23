#pragma once

typedef struct arvore_t {
  int chave;
  struct arvore_t *esq;
  struct arvore_t *dir;
} arvore_t;

arvore_t *inserir(arvore_t *arvore, int chave);
arvore_t *remover(arvore_t *arvore, int chave);
arvore_t *lista_p_arvore(int *chaves, int tamanho);
arvore_t *buscar(arvore_t *arvore, int chave);
void inorder(arvore_t* arvore);

arvore_t *desalocar(arvore_t *arvore);
