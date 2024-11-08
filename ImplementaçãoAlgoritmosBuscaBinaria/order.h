#pragma once 

#include <stdint.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(uint8_t*)a - *(uint8_t*)b);
}