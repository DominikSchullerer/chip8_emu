#include "chip8_memory.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "chip8_status.h"

#define MEMORY_SIZE 4096

struct chip8_memory_t {
	uint8_t data[MEMORY_SIZE];
	size_t size;
};

///////////////////////////////////////////////////////////////////////////////

static bool is_out_of_bounds(uint16_t address, size_t size, size_t length);

///////////////////////////////////////////////////////////////////////////////

chip8_status_t chip8_memory_create(chip8_memory_t** pout_memory)
{
	chip8_status_t status = CHIP8_STATUS_OK;

	chip8_memory_t* memory = calloc(1, sizeof(*memory));
	if (!memory) {
		status = CHIP8_STATUS_OUT_OF_MEMORY;
		goto error;
	}

	memory->size = MEMORY_SIZE;

	*pout_memory = memory;
	return status;

error: 
	chip8_memory_destroy(memory);
	return status;
}


void chip8_memory_destroy(chip8_memory_t* memory)
{
	if (!memory) {
		return;
	}

	free(memory);
}


chip8_status_t chip8_memory_write(
	chip8_memory_t* memory, 
	uint16_t address, 
	const uint8_t* data, 
	size_t length
)
{
	chip8_status_t status = CHIP8_STATUS_OK;

	if (is_out_of_bounds(address, memory->size, length)) {
		status = CHIP8_STATUS_OUT_OF_BOUNDS;
		goto error;
	}

	memcpy(memory->data + address, data, length);

	return status;

error:
	return status;
}

///////////////////////////////////////////////////////////////////////////////

static bool is_out_of_bounds(uint16_t address, size_t size, size_t length)
{
	return (length > size || address > size - length);
}