#include "Utils.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <ios>

//Here's the implementation for the functions
namespace Utils {

    //This creates a tottaly random number, in a form of 16-digits string, and returns it.
    std::string cardNumberGenerator() {
        std::string tempCardHolder = "";
        for (int index = 0; index < 16; index++) {
            //Random number from 0 to 9.
            int tempDigit = rand() % 10;
            tempCardHolder += std::to_string(tempDigit);
        }
        return tempCardHolder;
    }

    //It's just... Clearing console...
    void clearConsole() {
        system("cls");
    }
    
    //Solves the cin error
    void clearInputError() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}