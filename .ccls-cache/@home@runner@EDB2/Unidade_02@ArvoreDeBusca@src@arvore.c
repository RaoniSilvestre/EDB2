#include "arvore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

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

arvore_t *find_min(arvore_t *arvore) {
  while (arvore->esq != NULL)
    arvore = arvore->esq;
  return arvore;
}

arvore_t *remover(arvore_t *arvore, int chave) {
  if (arvore == NULL)
    return NULL;

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

arvore_t *construir_arvore(int *chaves, int inicio, int fim, arvore_t *arvore) {
  if (inicio > fim) {
    return arvore;
  }

  int meio = (inicio + fim) / 2;

  arvore = inserir(arvore, chaves[meio]);

  arvore = construir_arvore(chaves, inicio, meio - 1, arvore); // Lado esquerdo
  arvore = construir_arvore(chaves, meio + 1, fim, arvore);    // Lado direito

  return arvore;
}

arvore_t *lista_p_arvore(int *chaves, int tamanho) {
  arvore_t *arvore = NULL;
  if (tamanho == 0) {
    return arvore;
  }
  arvore = construir_arvore(chaves, 0, tamanho - 1, arvore);
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

void mostrarEmOrdem(arvore_t *arvore) {

  if (arvore != NULL) {
    mostrarEmOrdem(arvore->esq);
    printf("  %d", arvore->chave);
    mostrarEmOrdem(arvore->dir);
  }
}

void mostrarPreOrdem(arvore_t *arvore) {

  if (arvore != NULL) {
    printf("  %d", arvore->chave);
    mostrarPreOrdem(arvore->esq);
    mostrarPreOrdem(arvore->dir);
  }
}

void mostrarPosOrdem(arvore_t *arvore) {

  if (arvore != NULL) {
    mostrarPosOrdem(arvore->esq);
    mostrarPosOrdem(arvore->dir);
    printf("  %d", arvore->chave);
  }
}

void gerar_dot(FILE *arquivo, arvore_t *raiz) {
  if (raiz) {
    if (raiz->esq) {
      fprintf(arquivo, "  %d -> %d;\n", raiz->chave, raiz->esq->chave);
      gerar_dot(arquivo, raiz->esq);
    }
    if (raiz->dir) {
      fprintf(arquivo, "  %d -> %d;\n", raiz->chave, raiz->dir->chave);
      gerar_dot(arquivo, raiz->dir);
    }
  }
}

void exportar_para_dot(arvore_t *raiz, const char *nome_arquivo) {
  const char *pasta = "../outputDOT";
  struct stat st = {0};
  if (stat(pasta, &st) == -1) {
    if (mkdir(pasta, 0700) != 0) {
      fprintf(stderr, "Erro ao criar a pasta %s\n", pasta);
      exit(1);
    }
  }

  FILE *arquivo = fopen(nome_arquivo, "w");
  if (arquivo == NULL) {
    fprintf(stderr, "Erro ao abrir o arquivo %s\n", nome_arquivo);
    exit(1);
  }

  fprintf(arquivo, "digraph G {\n");
  gerar_dot(arquivo, raiz);
  fprintf(arquivo, "}\n");
  fclose(arquivo);
}
