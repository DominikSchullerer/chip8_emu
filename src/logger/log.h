//
// Created by Dominik on 24.10.2025.
//

#ifndef CHIP8_EMU_LOG_H
#define CHIP8_EMU_LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;

typedef enum {
    LOG_MODE_OVERWRITE,
    LOG_MODE_APPEND
} LogMode;

// Initialising / Closing
int  log_init(const char *filename, LogLevel level, LogMode mode);
void log_close(void);

// Logging
void log_log(LogLevel level, const char *file, int line, const char *fmt, ...);

#define LOG_DEBUG(fmt, ...) log_log(LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  log_log(LOG_INFO,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  log_log(LOG_WARN,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log_log(LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif //CHIP8_EMU_LOG_H
