#include "global.h"

Terminal::Terminal() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    this->width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    this->height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
