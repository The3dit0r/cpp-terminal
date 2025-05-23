#include <stdio.h>
#include "declaration.h"

int abc = 0;

int main() {
    //printer.debug();
    printer.println("Welcome to the Hangman game!");
    printer.println("Please select your options!");

    printer.println("1. Play a hangman game");
    printer.println("2. View credits");
    printer.println("3. Exit game");
    printer.print("> ");

    printer.render(false);
    printer.getInput(1);

    printer.clear();
    printer.move_cursor(0, 0);
    printer.render();

    printer.print("Your input was: ");
    printer.print(printer.inputBuffer, printer.lastInputLen);
    printer.println("");
    printer.render();
}