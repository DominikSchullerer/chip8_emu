cmake_minimum_required(VERSION 4.0)
project(chip8_emu C)

set(CMAKE_C_STANDARD 11)

add_executable(chip8_emu main.c
        src/logger/log.c
        src/logger/log.h
        src/chip8/memory/memory.c
        src/chip8/memory/memory.h
        src/chip8/status.h
        src/chip8/types.h)
