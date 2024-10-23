#pragma once

#include <stdint.h>
#include <stdlib.h>


/**
 * @brief Gera um vetor de números aleatórios.
 *
 * Esta função aloca dinamicamente um vetor de uint8_t com o tamanho especificado
 * e preenche cada posição com um valor aleatório entre 1 e 100.
 *
 * @param tamanho O tamanho do vetor a ser gerado.
 * @return Um ponteiro para o vetor gerado. O usuário é responsável por liberar a memória alocada.
 */
uint8_t *random_generator(uint16_t tamanho) {
    uint8_t *vetor = (uint8_t *) malloc(tamanho * sizeof(uint8_t));
    for (uint16_t i = 0; i < tamanho; i++) {
        vetor[i] = rand() % 100 + 1;
    }
    return vetor;
}