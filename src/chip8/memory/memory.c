//
// Created by Dominik on 25.10.2025.
//

#include "memory.h"

#include <stdlib.h>

struct memory_data_t {
    size_t size;
    byte_t *data;
};

static status_t memory_destroy(memory_t *memory);

memory_t *memory_create(size_t size)
{
    memory_t *memory = NULL;
    mem_data_t *mem_data = NULL;
    byte_t *data = NULL;

    memory = calloc(1, sizeof(*memory));
    if (memory == NULL) {
        goto fail;
    }

    mem_data = calloc(1, sizeof(*mem_data));
    if (mem_data == NULL) {
        goto fail;
    }

    data = calloc(size, sizeof(*data));
    if (data == NULL) {
        goto fail;
    }

    memory->mem_data = mem_data;
    memory->mem_data->data = data;

    memory->mem_data->size = size;

    memory->destroy = memory_destroy;

    return memory;

    fail:
    free(data);
    free(mem_data);
    free(memory);
    return NULL;
}


static status_t memory_destroy(memory_t *memory)
{
    if (memory == NULL) {
        return STATUS_ERROR_NULL_POINTER;
    }

    free(memory->mem_data);
    free(memory);

    return STATUS_OK;
}
