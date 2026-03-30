#include "os_win32.h"

#include <stdint.h>
#include <stdbool.h>
#include <Windows.h>


#define MAIN_WINDOW_NAME	"main_window"


struct win32_ctx_t {
	uint32_t x_dim;
	uint32_t y_dim;

	HINSTANCE hinstance;
	HWND hwnd;

	bool is_running;
};


///////////////////////////////////////////////////////////////////////////////

static int create_window(win32_ctx_t *win32_ctx, const char *title);
LRESULT CALLBACK wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

///////////////////////////////////////////////////////////////////////////////


win32_status_t win32_ctx_create(
	win32_ctx_t **pout_win32_ctx,
	uint32_t x_dim,
	uint32_t y_dim,
	const char *title
)
{
	win32_status_t status = WIN32_STATUS_OK;

	win32_ctx_t *win32_ctx = calloc(1, sizeof(*win32_ctx));
	if (!win32_ctx) {
		status = WIN32_STATUS_OUT_OF_MEMORY;
		goto error;
	}

	win32_ctx->x_dim = x_dim;
	win32_ctx->y_dim = y_dim;

	if (create_window(win32_ctx, title) != 0) {
		goto error;
	}

	*pout_win32_ctx = win32_ctx;
	return status;

error:
	win32_ctx_destroy(win32_ctx);
	return status;
}


void win32_ctx_destroy(win32_ctx_t *win32_ctx)
{
	if (!win32_ctx) {
		return;
	}

	DestroyWindow(win32_ctx->hwnd);

	free(win32_ctx);
}


void win32_ctx_process_messages(win32_ctx_t* win32_ctx)
{
	MSG msg = { 0 };
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}


void win32_ctx_start(win32_ctx_t* win32_ctx)
{
	win32_ctx->is_running = true;
}


bool win32_ctx_is_running(const win32_ctx_t* win32_ctx)
{
	return win32_ctx->is_running;
}


///////////////////////////////////////////////////////////////////////////////

static int create_window(win32_ctx_t *win32_ctx, const char *title)
{
	win32_status_t status = WIN32_STATUS_OK;
	WNDCLASSA wc = { 0 };
	RECT r = { 0 };
	ATOM class_atom = 0;

	wc.lpfnWndProc = wndproc;
	wc.hInstance = win32_ctx->hinstance;
	wc.lpszClassName = MAIN_WINDOW_NAME;
	wc.hCursor = LoadCursorA(NULL, IDC_ARROW);

	class_atom = RegisterClassA(&wc);
	if (!class_atom) {
		status = WIN32_STATUS_CLASS_REGISTRATION_FAILED;
		goto error;
	}

	r.left = 0;
	r.top = 0;
	r.right = win32_ctx->x_dim;
	r.bottom = win32_ctx->y_dim;
	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);

	uint32_t width = r.right - r.left;
	uint32_t height = r.bottom - r.top;

	win32_ctx->hwnd = CreateWindowExA(
		0, MAIN_WINDOW_NAME,
		title,
		WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,

		NULL, NULL,
		win32_ctx->hinstance,
		win32_ctx
	);

	if (!win32_ctx->hwnd) {
		UnregisterClassA(MAIN_WINDOW_NAME, win32_ctx->hinstance);
		status = WIN32_STATUS_WINDOW_CREATION_FAILED;
		goto error;
	}

	SetWindowLongPtrA(win32_ctx->hwnd, GWLP_USERDATA, (LONG_PTR)win32_ctx);
	ShowWindow(win32_ctx->hwnd, SW_NORMAL);

	return status;

error:
	if (win32_ctx->hwnd) {
		DestroyWindow(win32_ctx->hwnd);
	}

	if (class_atom) {
		UnregisterClassA(MAIN_WINDOW_NAME, win32_ctx->hinstance);
	}

	return status;
}


LRESULT CALLBACK wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	win32_ctx_t *ctx = (win32_ctx_t *)GetWindowLongPtrA(hwnd, GWLP_USERDATA);

	switch (uMsg)
	{
		case WM_CLOSE:
			ctx->is_running = false;
			return 0;
	}

	return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}
