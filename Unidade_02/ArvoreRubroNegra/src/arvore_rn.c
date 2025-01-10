#include "arvore_rn.h"

#include <stdio.h>

#define VERMELHO(no) (no != NULL && no->cor == RUBRO)
#define PRETO(no) (no != NULL && no->cor == NEGRO)

arvore_rn_t *raiz = NULL;

/**
 * Realiza uma rotação à esquerda na árvore rubro-negra.
 *
 * @param x Ponteiro para o nó onde a rotação será realizada.
 */
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

/**
 * Realiza uma rotação à direita na árvore rubro-negra.
 *
 * @param x Ponteiro para o nó onde a rotação será realizada.
 */
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

/**
 * Corrige o balanceamento da árvore rubro-negra após a inserção de um nó.
 *
 * @param no Ponteiro para o nó recém-inserido que pode ter causado o desbalanceamento.
 */
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

/**
 * @brief Insere um nó em uma árvore rubro-negra.
 *
 * Esta função insere um nó em uma árvore rubro-negra, mantendo a propriedade
 * da árvore. Se a árvore estiver vazia, o nó inserido se torna a nova raiz.
 * Caso contrário, a função insere o nó na posição correta com base na chave.
 *
 * @param arvore Ponteiro para a raiz da árvore rubro-negra.
 * @param no Ponteiro para o nó a ser inserido.
 * @return Ponteiro para a raiz da árvore rubro-negra após a inserção.
 */
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

/**
 * @brief Cria um novo nó para a árvore rubro-negra.
 *
 * Esta função aloca memória para um novo nó da árvore rubro-negra, inicializa
 * sua chave, define sua cor como rubro, e inicializa os ponteiros pai, esquerdo
 * e direito como NULL.
 *
 * @param chave A chave a ser armazenada no novo nó.
 * @return Um ponteiro para o novo nó criado.
 */
arvore_rn_t *criar_no(int chave) {
    arvore_rn_t *novo_no = (arvore_rn_t *)malloc(sizeof(arvore_rn_t));
    novo_no->chave = chave;
    novo_no->cor = RUBRO; // Nós recém-criados são rubros
    novo_no->pai = NULL;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    return novo_no;
}

/**
 * @brief Busca um nó na árvore rubro-negra com a chave especificada.
 *
 * Esta função percorre a árvore rubro-negra recursivamente para encontrar
 * um nó que contenha a chave fornecida. Se a chave for encontrada, o nó
 * correspondente é retornado. Caso contrário, a função retorna NULL.
 *
 * @param arvore Ponteiro para a raiz da árvore rubro-negra.
 * @param chave A chave a ser buscada na árvore.
 * @return Ponteiro para o nó que contém a chave, ou NULL se a chave não for encontrada.
 */
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

/**
 * Remove um nó com a chave especificada de uma árvore rubro-negra.
 *
 * @param arvore Ponteiro para a raiz da árvore rubro-negra.
 * @param chave A chave do nó a ser removido.
 * @return Ponteiro para a nova raiz da árvore após a remoção.
 *
 * A função remove o nó com a chave especificada da árvore rubro-negra,
 * ajustando os ponteiros dos nós conforme necessário. Se a chave não
 * for encontrada, a árvore original é retornada. Se o nó a ser removido
 * tiver dois filhos, o nó com a menor chave na subárvore direita é
 * encontrado e substitui o nó a ser removido.
 */
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

/**
 * @brief Desaloca a árvore rubro-negra recursivamente.
 *
 * Esta função percorre a árvore rubro-negra de forma recursiva e libera a memória
 * alocada para cada nó da árvore.
 *
 * @param arvore Ponteiro para a raiz da árvore rubro-negra a ser desalocada.
 * @return Retorna NULL após desalocar todos os nós da árvore.
 */
arvore_rn_t *desalocar(arvore_rn_t *arvore) {
    if (arvore != NULL) {
        arvore->esq = desalocar(arvore->esq);
        arvore->dir = desalocar(arvore->dir);
        free(arvore);
    }
    return NULL;
}

/**
 * @brief Realiza o percurso em ordem (inorder) em uma árvore rubro-negra.
 *
 * Esta função percorre a árvore rubro-negra em ordem, ou seja, visita
 * recursivamente o nó da subárvore esquerda, o nó raiz e o nó da subárvore
 * direita, nesta ordem. Durante a visita, a chave de cada nó é impressa.
 *
 * @param arvore Ponteiro para a árvore rubro-negra a ser percorrida.
 */
void inorder(arvore_rn_t *arvore) {
    if (arvore != NULL) {
        inorder(arvore->esq);
        printf("%d ", arvore->chave);
        inorder(arvore->dir);
    }
}

/**
 * @brief Imprime a sub-árvore da árvore rubro-negra de forma recursiva.
 *
 * Esta função imprime a sub-árvore da árvore rubro-negra, utilizando
 * recursão para percorrer os nós da árvore. A impressão é feita de forma
 * que a árvore é visualizada "deitada", com o nó raiz à esquerda e os nós
 * filhos à direita. A cor dos nós é representada por cores de fundo no
 * terminal: vermelho para nós vermelhos e preto para nós pretos.
 *
 * @param arvore Ponteiro para o nó raiz da sub-árvore a ser impressa.
 * @param espaços Número de espaços a serem impressos antes do valor do nó,
 *                utilizado para formatar a visualização da árvore.
 */
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

/**
 * @brief Imprime a árvore rubro-negra.
 *
 * Esta função imprime a árvore rubro-negra completa, chamando a função
 * imprimir_sub_arvore para realizar a impressão recursiva dos nós.
 *
 * @param raiz Ponteiro para o nó raiz da árvore a ser impressa.
 */
void imprimir_arvore(arvore_rn_t *raiz) {
    printf("Visualização da árvore deitada:\n");
    imprimir_sub_arvore(raiz, 0);
}