#include <stdio.h>

#include "os_win32/os_win32.h"

#define X_RES	640
#define Y_RES	320
#define TITLE	"Chip8 Emulator"

int main(void) {
	win32_ctx_t *win32_ctx = NULL;
	win32_status_t win32_status;

	win32_status = win32_ctx_create(&win32_ctx, X_RES, Y_RES, TITLE);
	
	if (win32_status != WIN32_STATUS_OK) {
		goto win32_error;
	}

	win32_ctx_start(win32_ctx);

	while (win32_ctx_is_running(win32_ctx))
	{
		win32_ctx_process_messages(win32_ctx);
	}

	win32_ctx_destroy(win32_ctx);

	return 0;

win32_error:
	printf("WIN32_STATUS: %d\n", win32_status);
	win32_ctx_destroy(win32_ctx);

	return -1;
}
