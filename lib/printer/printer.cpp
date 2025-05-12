#include "printer.h"

void Printer::init_buffer(Buffer& buff) {
    if (this->w == 0 || this->h == 0) {
        //should we throw error here?
        return;
    }

    char * temp = (char *) malloc(this->w * this->h);
    buff.setBuff(temp);
    this->clear_buffer(buff);
};

void Printer::clear_buffer(Buffer& buff) {
    if (this->w == 0 || this->h == 0) {
        //should we throw error here?
        return;
    }

    memset(buff[0], ' ', this->w * this->h);
};

int Printer::compare_row(int row_num) {
    if (row_num >= this->h || row_num < 0) {
        return -1;
    }

    char* old = this->old_buffer[row_num];
    char* cur = this->buffer[row_num];

    return memcmp(old, cur, this->w);
};

void Printer::move_cursor(int y) {
    this->y = y;
};

void Printer::move_cursor(int y, int x) {
    this->y = y;
    this->x = x;
};

void Printer::next_line() {
    this->move_cursor(this->y + 1, 0);
};

void Printer::print(string str) {
    for (int i = 0; i < str.length(); i++) {
        int tx = this->x + i;
        int ty = this->y;

        if (tx >= this->w) {
            this->next_line();
            tx = 0;
            ty = this->y;
        }


        this->buffer[ty][tx]  = str[i];
    }
};

void Printer::println(string str) {
    this->print(str);
    this->next_line();
};

void Printer::clear_line(int y) {
    memset(this->buffer[y], ' ', this->w);
};

void Printer::clear() {
    this->clear_buffer(this->buffer);
};

void Printer::render() {
    //also clear screen pls?
    printf("\x1b[H");  // Reset cursor to 0,0

    for (int i = 0; i < this->h; i++) {
        // if (this->compare_row(i) == 0) {
        //     continue;

        //     //instead of continue, jump cursor to next line
        //     //idk how, commented out for now
        // }

        printf("%.*s\n", this->w, buffer[i]);
    }
};

Printer::Printer(){
    Printer(0, 0);
};   

Printer::Printer(int w, int h){
    this->x = 0;
    this->y = 0;

    this->w = w;
    this->h = h;

    this->buffer = Buffer(this->w);
    this->old_buffer = Buffer(this->w);

    this->init_buffer(this->buffer);
    this->init_buffer(this->old_buffer);
};

Printer::~Printer(){
    delete &this->buffer;
    delete &this->old_buffer;
}