#include "chip8.h"

#include <stdlib.h>
#include <stdint.h>

#include "chip8_status.h"
#include "chip8_cpu.h"
#include "chip8_memory.h"


#define ROM_START_ADDRESS 0x200


struct chip8_t {
	chip8_cpu_t* cpu;
	chip8_memory_t* memory;
};

///////////////////////////////////////////////////////////////////////////////

chip8_status_t chip8_create(chip8_t** pout_chip8)
{
	chip8_status_t status = CHIP8_STATUS_OK;

	chip8_t* chip8 = calloc(1, sizeof(*chip8));
	if (!chip8) {
		status = CHIP8_STATUS_OUT_OF_MEMORY;
		goto error;
	}

	status = chip8_cpu_create(&chip8->cpu);
	if (status != CHIP8_STATUS_OK) {
		goto error;
	}

	status = chip8_memory_create(&chip8->memory);
	if (status != CHIP8_STATUS_OK) {
		goto error;
	}

	*pout_chip8 = chip8;
	return status;

error:
	chip8_destroy(chip8);
	return status;
}


void chip8_destroy(chip8_t* chip8)
{
	if (!chip8) {
		return;
	}

	chip8_memory_destroy(chip8->memory);
	chip8_cpu_destroy(chip8->cpu);

	free(chip8);
}


chip8_status_t chip8_ctx_load_rom(chip8_t* chip8, const uint8_t* rom_data, size_t rom_size)
{
	chip8_status_t status = CHIP8_STATUS_OK;

	status = chip8_memory_write(chip8->memory, ROM_START_ADDRESS, rom_data, rom_size);
	if (status != CHIP8_STATUS_OK) {
		goto error;
	}

	return status;

error:
	return status;
}
