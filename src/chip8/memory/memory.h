//
// Created by Dominik on 25.10.2025.
//

#ifndef CHIP8_EMU_MEMORY_H
#define CHIP8_EMU_MEMORY_H

#include "./../status.h"
#include "./../types.h"

typedef struct memory_t memory_t;
typedef struct memory_data_t mem_data_t;

typedef status_t (*mem_destroy_fn)(memory_t *memory);

struct memory_t{
    mem_data_t *mem_data;
    mem_destroy_fn destroy;
};

memory_t *memory_create(size_t size);

#endif //CHIP8_EMU_MEMORY_H
