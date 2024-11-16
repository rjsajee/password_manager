#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

#ifdef _WIN32
#include <windows.h>
inline void enableVirtualTerminalProcessing() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
inline void enableVirtualTerminalProcessing() {}
#endif

// Color codes
namespace Color {
    const std::string Reset = "\033[0m";
    const std::string Red = "\033[31m";
    const std::string Green = "\033[32m";
    const std::string Yellow = "\033[33m";
    const std::string Blue = "\033[34m";
    const std::string Magenta = "\033[35m";
    const std::string Cyan = "\033[36m";
    const std::string White = "\033[37m";
    const std::string Bold = "\033[1m";
    const std::string Underline = "\033[4m";
}

// Screen clear
inline void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#endif
