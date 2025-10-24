#include <stdio.h>

#include "src/logger/log.h"

int main(void) {
    if (log_init("test.log", LOG_DEBUG, LOG_MODE_OVERWRITE) != 0) {
        return 1;
    }

    LOG_INFO("Main started");
    printf("Hello, World!\n");
    LOG_DEBUG("Printed");
    LOG_WARN("Warn test");
    LOG_ERROR("Error test");
    return 0;
}
