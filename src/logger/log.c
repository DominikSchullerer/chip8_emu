//
// Created by Dominik on 24.10.2025.
//

#include "log.h"

static LogLevel current_level = LOG_DEBUG;
static FILE *log_file = NULL;

int log_init(const char *filename, LogLevel level, LogMode mode) {
    if (log_file) fclose(log_file);

    const char *open_mode = (mode == LOG_MODE_APPEND) ? "a" : "w";
    log_file = fopen(filename, open_mode);
    if (!log_file) return -1;

    current_level = level;
    return 0;
}

void log_close(void) {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}


void log_log(LogLevel level, const char *file, int line, const char *fmt, ...) {
    if (!log_file || level < current_level) return;

    const char *level_names[] = {"DEBUG", "INFO", "WARN", "ERROR"};

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_buf[20];
    strftime(time_buf, sizeof(time_buf), "%H:%M:%S", t);

    fprintf(log_file, "[%s] %7s (%s:%d): ", time_buf, level_names[level], file, line);

    va_list args;
    va_start(args, fmt);
    vfprintf(log_file, fmt, args);
    va_end(args);

    fprintf(log_file, "\n");
    fflush(log_file);
}
