#pragma once
#include <string>

using namespace std;

class Printer {
   private:

    class Buffer{
        friend class Printer;
        private:
            char * buff = nullptr; // 1 dimentional array
            int row_size;
        public:
            Buffer(int x = 0) : row_size(x){};
            void setBuff(char * _b){this->buff = _b;};
            char* operator[](int index){
                //internal type, type safety begone
                //if(this->x == 0 || this->y == 0 || this->buff == nullptr) return nullptr;
                return &this->buff[index * row_size];
            }
            ~Buffer(){
                if(this->buff != nullptr) free(this->buff);
            }
    };

    Buffer buffer;
    Buffer old_buffer;

    int x;
    int y;

    int w;
    int h;

    void init_buffer(Buffer&);
    void clear_buffer(Buffer&);

    //compares buffer old and new
    //0 means same
    //anything else means not same
    //-1 means bullshit happened
    //imo we shoudl just go with a flag instead of storing the extra copy
    //since every change to buffer is done through an API function already
    int compare_row(int);

   public:
    Printer();
    Printer(int, int);
    ~Printer();

    void move_cursor(int);
    void move_cursor(int, int);

    void print(string);
    void println(string);
    void next_line();

    void clear_line(int);
    void clear();

    void render();

    void debug(){
        printf("------------------------------------");
        printf("Testing the new buffer system\n");
        this->buffer[0][0] = 'A';
        this->buffer[0][1] = 'B';
        printf("%c %c\n", this->buffer[0][0], this->buffer[0][1]);
        printf("%.2s\n", this->buffer[0]);
        printf("------------------------------------");
    }

};
