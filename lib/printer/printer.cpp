#include "printer.h"

void Printer::init_buffer(void** buffer) {
    if (this->w == 0 || this->h == 0) {
        return;
    }

    *buffer = malloc(this->w * this->h);
    this->clear_buffer(*buffer);
}

void Printer::clear_buffer(void* buffer) {
    if (this->w == 0 || this->h == 0) {
        return;
    }

    memset(buffer, ' ', this->w * this->h);
}

char& Printer::readBuff(void* buffer, int x, int y) {
    return ((char*)buffer)[y * this->w + x];
}

int Printer::compare_row(int row_num) {
    if (row_num >= this->h || row_num < 0) {
        return -1;
    }

    char* old = this->old_buffer[row_num];
    char* cur = this->buffer[row_num];

    return memcmp(old, cur, this->w);
}

void Printer::move_cursor(int y) {
    this->y = y;
}

void Printer::move_cursor(int y, int x) {
    this->y = y;
    this->x = x;
}

void Printer::next_line() {
    this->move_cursor(this->y + 1, 0);
}

void Printer::print(string str) {
    for (int i = 0; i < str.length(); i++) {
        int tx = this->x + i;
        int ty = this->y;

        if (tx >= this->w) {
            this->next_line();
        }

        readBuff(this->buffer, tx, ty) = str[i];
    }
}

void Printer::println(string str) {
    this->print(str);
    this->next_line();
};

void Printer::clear_line(int y) {
    memset(this->buffer + y * this->w, ' ', this->w);
};

void Printer::clear() {
    this->clear_buffer(this->buffer);
}

void Printer::render() {
    printf("\x1b[H");  // Reset cursor to 0,0

    for (int i = 0; i < this->h; i++) {
        if (this->compare_row(i) == 1) {
            continue;
        }

        printf("%.*s\n", this->w, rend);
    }
}

Printer::Printer(int w, int h) {
    this->w = w;
    this->h = h;

    this->init_buffer(&this->buffer);
    this->init_buffer(&this->old_buffer);
}