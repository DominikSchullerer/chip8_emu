#include "chip8_cpu.h"

#include <stdlib.h>
#include <stdint.h>

#include "chip8_status.h"


struct chip8_cpu_t {
	uint16_t pc;
	uint16_t i;
	uint8_t registers[16];
};

///////////////////////////////////////////////////////////////////////////////

chip8_status_t chip8_cpu_create(chip8_cpu_t** pout_chip8_cpu)
{
	chip8_status_t status = CHIP8_STATUS_OK;

	chip8_cpu_t* chip8_cpu = calloc(1, sizeof(*chip8_cpu));
	if (!chip8_cpu) {
		status = CHIP8_STATUS_OUT_OF_MEMORY;
		goto error;
	}

	*pout_chip8_cpu = chip8_cpu;
	return status;

error:
	chip8_cpu_destroy(chip8_cpu);
	return status;
}

void chip8_cpu_destroy(chip8_cpu_t* chip8_cpu)
{	
	if (!chip8_cpu) {
		return;
	}

	free(chip8_cpu);
}
