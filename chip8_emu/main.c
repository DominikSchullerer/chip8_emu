#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "os_win32/os_win32.h"
#include "chip8/chip8.h"
#include "chip8/chip8_status.h"

#define X_RES	640
#define Y_RES	320
#define TITLE	"Chip8 Emulator"
#define ROM_PATH ".\\..\\chip8_test_suite\\1-chip8-logo.ch8"


static int load_rom(const char* path, chip8_t* chip8);

///////////////////////////////////////////////////////////////////////////////

int main(void) {
	win32_ctx_t *win32_ctx = NULL;
	win32_status_t win32_status = WIN32_STATUS_OK;
	chip8_t* chip8 = NULL;
	chip8_status_t chip8_status = CHIP8_STATUS_OK;

	win32_status = win32_ctx_create(&win32_ctx, X_RES, Y_RES, TITLE);
	if (win32_status != WIN32_STATUS_OK) {
		goto error;
	}

	chip8_status = chip8_create(&chip8);
	if (chip8_status != CHIP8_STATUS_OK) {
		goto error;
	}

	if (load_rom(ROM_PATH, chip8) != 0) {
		goto error;
	}

	win32_ctx_start(win32_ctx);

	while (win32_ctx_is_running(win32_ctx))
	{
		win32_ctx_process_messages(win32_ctx);
	}

	win32_ctx_destroy(win32_ctx);

	return 0;

error:
	printf("WIN32_STATUS: %d\n", win32_status);
	printf("CHIP8_STATUS: %d\n", chip8_status);
	chip8_destroy(chip8);
	win32_ctx_destroy(win32_ctx);

	return -1;
}


static int load_rom(const char* path, chip8_t* chip8)
{
	printf("load_rom: %s\n", path);
	FILE* rom_file = fopen(path, "rb");
	if (!rom_file) {
		printf("Failed to open ROM file: %s\n", path);
		return -1;
	}

	fseek(rom_file, 0L, SEEK_END);
	long rom_size = ftell(rom_file);
	fseek(rom_file, 0L, SEEK_SET);

	uint8_t* rom_data = malloc(rom_size);
	if (!rom_data) {
		printf("Failed to allocate memory for ROM data\n");
		fclose(rom_file);
		return -1;
	}

	size_t read_bytes = fread(rom_data, sizeof(uint8_t), rom_size, rom_file);
	if (read_bytes != rom_size) {
		printf("Failed to read ROM data\n");
		free(rom_data);
		fclose(rom_file);
		return -1;
	}


	fclose(rom_file);

	// TODO: Load ROM data into Chip8 memory

	return 0;
}