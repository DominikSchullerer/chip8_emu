#ifndef _CHIP8_H_
#define _CHIP8_H_

#include "chip8_status.h"
#include <stdint.h>

typedef struct chip8_t chip8_t;

///////////////////////////////////////////////////////////////////////////////

chip8_status_t chip8_create(chip8_t** pout_chip8);

void chip8_destroy(chip8_t* chip8);

chip8_status_t chip8_ctx_load_rom(chip8_t* chip8, const uint8_t* rom_data, size_t rom_size);

#endif // !_CHIP8_H_
