#include "printer.h"
#include <errno.h>

void Printer::init_buffer(Buffer& buff) {
    if (this->w <= 0 || this->h <= 0) {
        //unintended, can happen if user stupid
        _set_errno(EINVAL);
        perror("Width or Height of printer is invalid");
        return;
    }

    int s = this->w * this->h;
    char * temp = (char *) malloc(s);
    memset(temp, ' ', s);
    buff.setBuff(temp);
};

void Printer::clear_buffer(Buffer& buff) {
    if (this->w == 0 || this->h == 0) {
        //unintended, can happen if user stupid
        _set_errno(EINVAL);
        perror("Width or Height of printer is invalid");
        return;
    }

    memset(buff[0], ' ', this->w * this->h);
};

void Printer::transferBuffer(Buffer& dest, Buffer& origin){
    memcpy((void*) dest.buff, (void*) origin.buff, this->h * this->w);
}

int Printer::compare_row(int row_num) {
    if (row_num >= this->h || row_num < 0) {
        _set_errno(EINVAL);
        perror("Width or Height of printer is invalid");
        return -2;
    }

    char* old = this->old_buffer[row_num];
    char* cur = this->buffer[row_num];

    for(int i = 0; i < this->w; i++){
        if(old[i] == cur[i]) continue;
        return i;
    }
    return -1;
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
    for (int i = 0; i <= str.length(); i++) {
        if(i != 0) this->x++;
        if (this->x >= this->w) this->next_line();
        if(i != str.length()) this->buffer[this->y][this->x] = str[i];
    }
    this->changedFlag = true;
};

void Printer::print(char * str, int len) {
    for (int i = 0; i <= len; i++) {
        if(i != 0) this->x++;
        if (this->x >= this->w) this->next_line();
        if(i != len) this->buffer[this->y][this->x] = str[i];
    }
    this->changedFlag = true;
};

void Printer::println(string str) {
    this->print(str);
    this->next_line();
};

void Printer::clear_line(int y) {
    memset(this->buffer[y], ' ', this->w);
    this->changedFlag = true;
};

void Printer::clear() {
    this->clear_buffer(this->buffer);
    this->changedFlag = true;
    this->old_buffer.unset = true;
};

void Printer::getInput(int len, bool readSpace, bool doFlush){
    int i = 0;
    bool stopped = false;
    int actualLen = 0;
    for(; i < len; i++){
        char r = (char) getchar();
        if(r == '\n'){
            stopped = true;
            break;
        }
        if(!readSpace && r == ' ') break;
        this->inputBuffer[i] = r;
        actualLen++;
    }
    //flush part
    //fflush doenst work with stdin
    //so this is manually flush
    //it just reads until it found a \n
    if(!stopped && doFlush){
        char r = (char) getchar();
        while(r != '\n'){
            char r = (char) getchar();
        }
    }

    this->lastInputLen = actualLen;
}

void Printer::render(bool insertEndl) {

    if(this->old_buffer.unset) printf("\x1b[2J"); //clear screen

    if(!changedFlag) return;

    for (int i = 0; i < this->h; i++) {
        int c = this->compare_row(i);
        if (c >= 0) {
            //move cursor to c, line i
            printf("\x1b[%d;%dH", i+1, c+1);
            int k = c;

            unsigned int cumulativeSame = 0;
            while(true){
                if(this->old_buffer[i][k] != this->buffer[i][k]){
                    if(cumulativeSame != 0) printf("\x1b[%dC", cumulativeSame);
                    putchar(this->buffer[i][k]);
                    this->old_buffer[i][k] = this->buffer[i][k];
                    cumulativeSame = 0;
                } else if(this->old_buffer.unset){
                    putchar(' ');
                } else {
                    cumulativeSame++;
                }
                k++;
                if(k >= this->w) break;
            }
        }
    }

    //move to next line
    if(insertEndl) printf("\x1b[E");
    else {
        //move cursor to expected
        printf("\x1b[%d;%dH", this->y + 1, this->x + 1);
    }

    this->changedFlag = false;
    this->old_buffer.unset = false;
};

Printer::Printer(int w, int h){
    this->x = 0;
    this->y = 0;

    this->w = w;
    this->h = h;

    this->inputBuffer = (char *) malloc(w + 1);
    memset(this->inputBuffer, '\0', w + 1);

    this->buffer = Buffer(w);
    this->old_buffer = Buffer(w, true);
    this->changedFlag = false;

    this->init_buffer(this->buffer);
    this->init_buffer(this->old_buffer);
};

Printer::~Printer(){
    if(this->inputBuffer != nullptr) free(this->inputBuffer);
    delete &this->buffer;
    delete &this->old_buffer;
}