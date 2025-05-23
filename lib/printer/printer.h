#pragma once
#include <string>
#include <errno.h>

using namespace std;

class Printer {
   private:

    //Purposes: 
    // mask 1d array to 2d array, make buffer[x][y] to function like a 2d arrays

    class Buffer{
        friend class Printer;
        private:
            char * buff = nullptr; // 1 dimentional array
            int row_size;
            bool unset;
        public:
            Buffer(int x = 0, bool isUnset = false) : row_size(x), unset(isUnset){};
            void setBuff(char * _b){this->buff = _b;};
            char* operator[](int index){
                //internal type, type safety begone
                //this should only be called with a normal index
                //if(this->x == 0 || this->y == 0 || this->buff == nullptr) return nullptr;
                return &this->buff[index * row_size];
            }
            ~Buffer(){
                if(this->buff != nullptr) free(this->buff);
            }
    };

    Buffer buffer;
    Buffer old_buffer;
    bool changedFlag;
    
    int x;
    int y;
    
    int w;
    int h;
    
    void init_buffer(Buffer&);
    void clear_buffer(Buffer&);
    void transferBuffer(Buffer& dest, Buffer& origin);
    
    //compares buffer old and new
    //returns index of first change
    //-1 means same
    //-2 means error, it should prints the error
    int compare_row(int);
    
    public:
    char * inputBuffer = nullptr;
    int lastInputLen = -1;
    //Default init is invalid and unusable, this option should not exist
    //Printer();
    Printer(int, int);
    ~Printer();

    void move_cursor(int);
    void move_cursor(int, int);

    void print(char *, int);
    void print(string);
    void println(string);
    void next_line();

    void clear_line(int);
    void clear();

    //get input at cursor position, up till len
    //if doReadSpace is false, the input is stopped and flush after the first space
    void getInput(int len, bool doReadSpace = false, bool doFlushInput = true);

    void render(bool insertEndl = true);

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
