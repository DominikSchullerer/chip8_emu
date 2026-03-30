#ifndef _CHIP8_MEMORY_H_
#define _CHIP8_MEMORY_H_

#include "chip8_status.h"
#include <stdint.h>

typedef struct chip8_memory_t chip8_memory_t;

///////////////////////////////////////////////////////////////////////////////

chip8_status_t chip8_memory_create(chip8_memory_t** pout_memory);

void chip8_memory_destroy(chip8_memory_t* memory);

chip8_status_t chip8_memory_write(
	chip8_memory_t* memory, 
	uint16_t address, 
	const uint8_t* data, 
	size_t length
);

#endif // !_CHIP8_MEMORY_H_
