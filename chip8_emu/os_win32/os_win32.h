#ifndef OS_WIN32_H_
#define OS_WIN32_H_

#include <stdint.h>


typedef enum win32_status_t {
	WIN32_STATUS_OK,
	WIN32_STATUS_OUT_OF_MEMORY,
	WIN32_STATUS_CLASS_REGISTRATION_FAILED,
	WIN32_STATUS_WINDOW_CREATION_FAILED
} win32_status_t;


typedef struct win32_ctx_t win32_ctx_t;

///////////////////////////////////////////////////////////////////////////////

win32_status_t win32_ctx_create(
	win32_ctx_t **pout_win32_ctx,
	uint32_t x_dim,
	uint32_t y_dim,
	char *title
);


void win32_ctx_destroy(win32_ctx_t *win32_ctx);


#endif // !OS_WIN32_H_
