#pragma once

#include <stdlib.h>
/**
 * @file arvore_rn.h
 * @brief Definições de tipos para a implementação de uma Árvore Rubro-Negra.
 */

/**
 * @enum cor_t
 * @brief Enumeração para representar as cores dos nós na Árvore Rubro-Negra.
 * 
 * @var cor_t::RUBRO
 * Nó de cor vermelha.
 * @var cor_t::NEGRO
 * Nó de cor preta.
 */
typedef enum cor_t {
  RUBRO, NEGRO
} cor_t;


/**
 * @struct arvore_rn_t
 * @brief Estrutura que representa um nó na Árvore Rubro-Negra.
 * 
 * @var:chave
 * Chave associada ao nó.
 * @var:cor
 * Cor do nó, podendo ser RUBRO ou NEGRO.
 * @var:esq
 * Ponteiro para o nó filho à esquerda.
 * @var:dir
 * Ponteiro para o nó filho à direita.
 * @var:pai
 * Ponteiro para o nó pai.
 */
typedef struct arvore_rn_t {
  int chave;
  cor_t cor;
  struct arvore_rn_t *esq;
  struct arvore_rn_t *dir;
  struct arvore_rn_t *pai;
} arvore_rn_t;

extern arvore_rn_t *raiz;

arvore_rn_t *inserir(arvore_rn_t *arvore, arvore_rn_t *no);
arvore_rn_t *remover(arvore_rn_t *arvore, int chave);
arvore_rn_t *lista_p_arvore(int *chaves, int tamanho);
arvore_rn_t *buscar(arvore_rn_t *arvore, int chave);

void inorder(arvore_rn_t* arvore);
void imprimir_arvore(arvore_rn_t *arvore);

arvore_rn_t *desalocar(arvore_rn_t *arvore);
