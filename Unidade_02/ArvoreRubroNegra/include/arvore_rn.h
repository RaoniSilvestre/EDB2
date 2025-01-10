#pragma once

#include <stdlib.h>

typedef enum cor_t {
  RUBRO, NEGRO
} cor_t;

typedef struct arvore_rn_t {
  int chave;
  cor_t cor;
  struct arvore_rn_t *esq;
  struct arvore_rn_t *dir;
  struct arvore_rn_t *pai;
} arvore_rn_t;

extern arvore_rn_t *raiz;

// void inserir(arvore_rn_t **raiz, int chave);
void corrigir_balanceamento(arvore_rn_t *no);
arvore_rn_t *criar_no(int chave);
arvore_rn_t *inserir(arvore_rn_t *arvore, arvore_rn_t *no);
arvore_rn_t *remover(arvore_rn_t *arvore, int chave);
arvore_rn_t *lista_p_arvore(int *chaves, int tamanho);
arvore_rn_t *buscar(arvore_rn_t *arvore, int chave);

void inorder(arvore_rn_t* arvore);
void imprimir_arvore(arvore_rn_t *arvore);

arvore_rn_t *desalocar(arvore_rn_t *arvore);
