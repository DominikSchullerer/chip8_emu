#ifndef _CHIP8_H_
#define _CHIP8_H_

#include "chip8_status.h"

typedef struct chip8_t chip8_t;

///////////////////////////////////////////////////////////////////////////////

chip8_status_t chip8_create(chip8_t** pout_chip8);

void chip8_destroy(chip8_t* chip8);

#endif // !_CHIP8_H_
