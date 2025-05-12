#pragma once
#include <string>

using namespace std;

class Printer {
   private:
    void *buffer;
    void *old_buffer;

    int x = 0;
    int y = 0;

    int w = 0;
    int h = 0;

    void init_buffer(void **);
    void clear_buffer(void *);
    int compare_row(int);
    char &readBuff(void *buffer, int x, int y);

   public:
    Printer(int, int);

    void move_cursor(int);
    void move_cursor(int, int);

    void print(string);
    void println(string);
    void next_line();

    void clear_line(int);
    void clear();

    void render();
};
