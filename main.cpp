#include <stdio.h>

#include "declaration.h"

int abc = 0;

int main() {
    printer.println("Welcome to the Hangman game!");
    printer.println("Please select your options!");

    printer.println("1. Play a hangman game");
    printer.println("2. View credits");
    printer.println("3. Exit game");

    while (true) {
        printer.render();
        Sleep(1000);
    }
}