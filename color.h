#ifndef COLOR_H
#define COLOR_H

#include <string>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
inline void enableColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) return;

    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
}
#else
inline void enableColors() {}
#endif

const std::string RESET = "\033[0m";
const std::string RED   = "\033[31m";
const std::string GREEN = "\033[32m";

#endif
