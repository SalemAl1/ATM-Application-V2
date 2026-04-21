#pragma once
#include <string>

//A utility namespace.
//Here I throw some usefull utilities for the App.
namespace Utils {

    //Adding some colors to the console output.
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";

    //Resets the color to the default white 
    const std::string RESET = "\033[0m";

    //Generates the card number of the user, randomly
    std::string cardNumberGenerator();

    //Clears console
    void clearConsole();

    //Solves the cin errors
    //This error occurs when a user try to input a string into a number data type.
    void clearInputError();
}