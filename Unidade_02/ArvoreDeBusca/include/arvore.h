#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct arvore_t {
  int chave;
  struct arvore_t *esq;
  struct arvore_t *dir;
} arvore_t;

arvore_t *inserir(arvore_t *arvore, int chave);
arvore_t *remover(arvore_t *arvore, int chave);
arvore_t *construir_arvore(int *chaves, int inicio, int fim, arvore_t *arvore);
arvore_t *lista_p_arvore(int *chaves, int tamanho);
arvore_t *buscar(arvore_t *arvore, int chave);

void mostrarEmOrdem(arvore_t *arvore);
void mostrarPreOrdem(arvore_t *arvore);
void mostrarPosOrdem(arvore_t *arvore);


arvore_t *desalocar(arvore_t *arvore);

void gerar_dot(FILE *arquivo, arvore_t *raiz);
void exportar_para_dot(arvore_t *raiz, const char *nome_arquivo);
