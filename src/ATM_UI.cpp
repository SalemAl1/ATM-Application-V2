#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <ios>
#include "ATM_UI.h"
#include "User.h"
#include "BankDatabase.h"
#include "Utils.h"

//Welcome screen... The first screen appears to the user.
void ATM_UI::welcomeScreen() {

    //What will the user choose?
    int inputChoice;

    do {
        //The main menu of our App.
        std::cout << "<-- Welcome to Bank-V2! -->\n\n";
        std::cout << "1- Log in\n";
        std::cout << "2- Sign up\n";
        std::cout << "3- Info & Help \n";
        std::cout << "4- Exit \n> ";

        //We here take an input for the user's choice, then clears the screen.
        std::cin >> inputChoice;
        Utils::clearConsole();

        //Fixes the problem where the user may type a letter.... Purposefully?
        if (std::cin.fail())
            Utils::clearInputError();

        //A normal swtich. Switches between the choices.
        switch (inputChoice) {

        //Login Prompt.
        case 1: {

            //Some variables to handle the login process.
            //isValid helps tracking the valid input.
            //goBack helps when a user suddenly rethinking their life choices and wants to go back.
            std::string inputCardNumber;
            std::string inputPassword;
            bool isValid = false;
            bool goBack = false;

            //Ignores any stray inputs here or there so we can start clean.
            std::cin.ignore();

            //A loop to trap the user to type a correct and valid card number.
            do {
                std::cout << "<-- Log in -->\n\n";
                std::cout << "Enter you card number:\n> ";
                std::getline(std::cin, inputCardNumber);

                //They want to get out. So we just break the.... loop.
                if (inputCardNumber == "-1") {
                    goBack = true;
                    Utils::clearConsole();
                    break;
                }

                //You can't sign in with an empty card number, obviously.
                if (!inputCardNumber.empty())
                    isValid = true;

                //Anything else leads to an error.
                else {
                    std::cout << Utils::RED << "\n[ERROR]: " << Utils::RESET << "Please enter your card number.\n\n";

                    system("pause");
                    Utils::clearConsole();
                }
                    
            //Our flag. If it's valid, we get out of the loop. Well, the user will do.
            } while (!isValid);

            //When the user decides to go back. This returns them to the main menu again.
            if (goBack) break;

            //This checks if this guy is really in our database or not. Looks sus for me.
            User* currentUser = database.find(inputCardNumber);

            //If it return a null pointer, this means that guy didn't exist in our database. Told you!
            if (currentUser == nullptr) {
                std::cout << Utils::RED << "[ERROR]: " << Utils::RESET << "Card number not found.\n\n";

                //We pause here so they can read the message they got. We give them a moment to admire that error.
                system("pause");
                Utils::clearConsole();
            }

            //If it's not a null pointer, then this guys really exists in our database. Wait did he? My bad...
            else {

                //We return the flag to it's original state.
                isValid = false;
                Utils::clearConsole();
                
                do {
                    //We add the previous interactions to make the UI/UX smoother.
                    std::cout << "<-- Log in -->\n\n";
                    std::cout << "Enter you card number:\n> " << inputCardNumber << '\n';

                    // The important part. THE PASSWORD.
                    std::cout << "Enter your password:\n> ";
                    std::getline(std::cin, inputPassword);

                    Utils::clearConsole();

                    //If the user decides to go back again. Really? This far?
                    if (inputPassword == "-1") {
                        goBack = true;
                        Utils::clearConsole();
                        break;
                    }

                    //Empty strings are not allowed
                    if (inputPassword.empty()) {
                        std::cout << Utils::RED << "[ERROR]: " << Utils::RESET << "Please Enter your password.\n\n";

                        system("pause");
                    }

                    //The user successfully made it to the login function.
                    //If the function returns a true, then the user entered their information correctly.
                    //They know get to see the userScreen. The second section in this code.
                    else if (currentUser->login(inputPassword)) {
                        userScreen(currentUser);
                        isValid = true;
                    }

                    //If not, They get the wrong password error.
                    else {
                        std::cout << Utils::RED << "[ERROR]: " << Utils::RESET << "Wrong password.\n\n";

                        system("pause");
                    }

                    Utils::clearConsole();

                    //It loops like this until either they enter their password correctly, or they go back.
                } while (!isValid);

                if (goBack) break;

            }

            break;
        }

        //Sign up prompt.
        case 2: {

            //Some variables to help handling the process of signing in.
            //isValid and goBack do the same job as we discussed before, handling the valid input and the go back thing.
            std::string newName;
            std::string newCardNumber;
            std::string newPassword;
            std::string confirmPassword;
            bool isValid = false;
            bool goBack = false;

            //Ignore anything unimportant.
            std::cin.ignore();

            //Loops to get the correct name from the user.
            do {
                std::cout << "<-- Sign up -->\n\n";
                std::cout << "Enter your full name:\n> ";
                std::getline(std::cin, newName);

                //What if the user wants to go back?
                if (newName == "-1") {
                    goBack = true;
                    Utils::clearConsole();
                    break;
                }

                //Everyone has a name, right?
                if (newName.empty()) {
                    std::cout << Utils::RED << "\n[ERROR]" << Utils::RESET << " Please enter your name.\n\n";

                    system("pause");
                }

                //The name better be less than 25. Well, it's a must.
                else if (newName.length() > 25) {
                    std::cout << Utils::RED << "\n[ERROR]" << Utils::RESET << " Names can\'t be longer than 25.\n\n";

                    system("pause");
                }

                //No commas are allowed. This will corrupt our database!!
                else if (newName.find(',') != std::string::npos) {
                    std::cout << Utils::RED << "\n[ERROR]" << Utils::RESET << " Names can\'t contain comma.\n\n";

                    system("pause");
                }

                //The input is approved. It's not empty, longer than 25, or has a comma.
                else
                    isValid = true;

                Utils::clearConsole();

            } while (!isValid);

            if (goBack) break;

            isValid = false;

            do {
                //Just smoothing out the UI/UX
                std::cout << "<-- Sign up -->\n\n";
                std::cout << "Enter your full name:\n> " << newName << '\n';

                std::cout << "Enter your password:\n> ";
                std::getline(std::cin, newPassword);

                //What if the user decided to go back now?
                if (newPassword == "-1") {
                    goBack = true;
                    Utils::clearConsole();
                    break;
                }

                std::cout << "Confirm your password:\n> ";
                std::getline(std::cin, confirmPassword);

                //What if the user decided to go back now after typing the password for the first time?
                if (confirmPassword == "-1") {
                    goBack = true;
                    Utils::clearConsole();
                    break;
                }

                Utils::clearConsole();

                //No empty's
                if (newPassword.empty() || confirmPassword.empty()) {
                    std::cout << Utils::RED << "[ERROR]: " << Utils::RESET << "Please Enter your password.\n\n";

                    system("pause");
                }

                //Of course they must match. It is called a confirm for a reason.
                else if (newPassword != confirmPassword) {
                    std::cout << Utils::RED << "[ERROR]: " << Utils::RESET << "Passwords don't match. Try again.\n\n";

                    system("pause");
                }

                //Hmmm. Why would they insert a comma?
                else if (newPassword.find(',') != std::string::npos) {
                    std::cout << Utils::RED << "\n[ERROR]" << Utils::RESET << " Passwords can\'t contain comma.\n\n";

                    system("pause");
                }

                //Approved again.
                else
                    isValid = true;

                Utils::clearConsole();

            } while (!isValid);

            if (goBack) break;

            //We need to conintue generating card numbers until we find a brand new one.
            //A card number that doesn't exist in our database.
            //Which is insanely common, but come on, what if the user is cursed or something?
            do {
                newCardNumber = Utils::cardNumberGenerator();

            } while (database.find(newCardNumber) != nullptr);

            //We got all the data needed to create our very new user!
            User newUser(newName, newCardNumber, newPassword);
            database.addUser(newUser);
            //We need our precious user's data to be saved.
            database.saveToFile();

            //The user finally gets to know the good news, they are a part of our bank now!
            //They must save this info or it's gone forever.
            //It's saved in the database, of course, but no way the customer would get access to it, right? Right??
            std::cout << "<-- Account created successfully! -->\n\n";
            std::cout << "Account Name: " << newName << '\n';
            std::cout << "Card Number: " << newCardNumber ;
            std::cout << Utils::YELLOW << "\n\n[WARNING]: " << Utils::RESET << "Please save your credentials.\n\n";

            //Now let them admire their beautiful info... THEN WIPE IT CLEAN.
            system("pause");
            Utils::clearConsole();

            break;
        }

        //Info Window
        case 3:

            //Some Info the user might need through their journey in our great App.
            std::cout << Utils::BLUE << "\n========================================\n";
            std::cout << "       SYSTEM INFORMATION & HELP        \n";
            std::cout << "========================================\n\n" << Utils::RESET;

            std::cout << "[ Navigation Shortcuts ]\n";
            std::cout << " * Prompts   : Type " << Utils::GREEN << "-1" << Utils::RESET << " and press Enter to go back.\n\n";

            std::cout << "[ Account & Security ]\n";
            std::cout << " * Daily Limits   : Withdrawals are capped at 8000.00EGP per transaction.\n";
            std::cout << " * Data Saving    : Your balance is securely auto-saved after every transaction.\n";
            std::cout << " * Privacy        : Bank personnel will never ask for your password.\n\n";

            std::cout << "[ Input Guidelines ]\n";
            std::cout << " * Names cannot contain commas (,).\n";
            std::cout << " * Currency inputs support two decimal places (e.g., 150.50).\n\n";

            std::cout << Utils::BLUE << "========================================\n\n" << Utils::RESET;

            //Good luck reading all of that.....
            system("pause");
            Utils::clearConsole();

            break;

        //Leaving already?
        case 4:

            std::cout << "Thanks for using the ATM!\n";
            database.saveToFile();
            break;

        //Admin mode only!
        case 9999: {

            std::string adminPassword;
            bool goBack = false;

            //The code needs for the super secret password to continue.
            std::cout << "--- RESTRICTED ACCESS ---\n\n";
            std::cout << "Enter admin password:\n> ";
            std::cin >> adminPassword;

            //I don't know why would admin rethink their life choices...
            if (adminPassword == "-1") {
                goBack = true;
                Utils::clearConsole();
                break;
            }

            //Takes the given password and compare it to our stored password.
            if (database.adminAuth(adminPassword)) {
                std::cout << "\n--- ACCESS GRANTED ---\n\n";

                system("pause");
                Utils::clearConsole();

                adminScreen();
            }
            
            //Otherwise, it triggers an alert. Are you really an admin?
            else {
                std::cout << Utils::RED << "[SECURITY ALERT]: " << Utils::RESET << "Incorrect password.";
                system("pause");
                Utils::clearConsole();
            }

            break;
        }

        //The-anything-else block. In case the user panicked and didn't know what to write.
        default:

            std::cout << Utils::RED << "[ERROR]: " << Utils::RESET << "Invalid input.\n\n";

            system("pause");
            Utils::clearConsole();

            break;
        }

    //I mean if it's 4, then it's the end, right?
    } while (inputChoice != 4);
}

//What will the user sees when they sign in with their real accounts?
void ATM_UI::userScreen(User* currentUser) {

    //Some variables to handle the process and making our life easier.
    int inputChoice;
    double amount;
    TransactionStatus currentStatus;

    do {
        //All the options the user have. What will it be, user?
        std::cout << "Welcome back, " << currentUser->getName() << "!\n";
        std::cout << "How can we help you today?\n\n";
        std::cout << "1- Check balance.\n";
        std::cout << "2- Withdraw money.\n";
        std::cout << "3- Deposit money.\n";
        std::cout << "4- Change currency.\n";
        std::cout << "5- Sign out.\n> ";
        std::cin >> inputChoice;
        Utils::clearConsole();

        //Handles the characters problem.
        if (std::cin.fail())
            Utils::clearInputError();

        //We want all numbers to be exactly two digits after the dot.
        std::cout << std::fixed << std::setprecision(2);

        switch (inputChoice) {

        //Checking their balance.
        case 1:

            std::cout << "<-- Balance -->\n\n";
            std::cout << "Your current balance is " << currentUser->getBalance() << "EGP.\n\n";

            system("pause");
            Utils::clearConsole();

            break;
        
        //Withdraw money
        case 2:
            
            std::cout << "<-- Withdraw -->\n\n";
            std::cout << "Enter amount to withdraw:\n> ";
            std::cin >> amount;

            //Again. Handles the characters problem.
            if (std::cin.fail())
                Utils::clearInputError();

            //Just in case they misclicked and they want to go back.
            if (amount == -1) {
                Utils::clearConsole();
                break;
            }
            
            //What happened to our transaction?
            currentStatus = currentUser->withdraw(amount);

            if (currentStatus == TransactionStatus::MAX_LIMIT_EXCEEDED)
                std::cout << Utils::RED << "\n[ERROR]: " << Utils::RESET << "Maximum withdraw limit is 8000EGP.\n\n";

            else if (currentStatus == TransactionStatus::INVALID_AMOUNT)
                std::cout << Utils::RED << "\n[ERROR]: " << Utils::RESET << "Amount must be greater than Zero.\n\n";

            else if (currentStatus == TransactionStatus::INSUFFICIENT_FUNDS)
                std::cout << Utils::RED << "\n[ERROR]: " << Utils::RESET << "Insufficient funds!\n\n";

            else if (currentStatus == TransactionStatus::SUCCESS) {
                std::cout << Utils::GREEN << "\n[SUCCESS]: " << Utils::RESET << "Your current balance is " << currentUser->getBalance() << "EGP.\n";
                std::cout << "Please take your money!\n\n";

                //We want to commit the changes after every successful transaction.
                //What if the user withdraws money then closes the App immediately? They would steal from us!
                database.saveToFile();
            }


            system("pause");
            Utils::clearConsole();

            break;

        //Deposit money
        case 3:

            std::cout << "<-- Deposit -->\n\n";
            std::cout << "Enter amount to deposit:\n> ";
            std::cin >> amount;

            //Handles characters problem.
            if (std::cin.fail())
                Utils::clearInputError();

            //They misclicked again? Maybe
            if (amount == -1) {
                Utils::clearConsole();
                break;
            }

            //What happened to our transaction?
            currentStatus = currentUser->deposit(amount);


            if (currentStatus == TransactionStatus::INVALID_AMOUNT)
                std::cout << Utils::RED << "[ERROR]: " << Utils::RESET << "Amount must be greater than Zero.\n\n";

            else if (currentStatus == TransactionStatus::SUCCESS) {
                currentUser->deposit(amount);
                std::cout << Utils::GREEN << "\n[SUCCESS]: " << Utils::RESET << "Your current balance is " << currentUser->getBalance() << "EGP.\n";

                //Just like what we did earlier.
                //But this time we would steal from them. It's not like I mind it tho.....
                database.saveToFile();
            }


            system("pause");
            Utils::clearConsole();

            break;
            
        //Change Currency
        case 4:
            
            std::cout << "<-- Change currency -->\n\n";
            std::cout << "Enter amount in EGP to convert to USD:\n> ";
            std::cin >> amount;

            //Characters problem....
            if (std::cin.fail())
                Utils::clearInputError();

            //Yeah. They just don't feel like it today.
            if (amount == -1) {
                Utils::clearConsole();
                break;
            }

            //We rely on withdraw function here. Why?
            //Because the money they will change the currecy from, will be dedcuted from their balance.
            //Just like what withdraw function does!
            currentStatus = currentUser->withdraw(amount);

            if (currentStatus == TransactionStatus::INVALID_AMOUNT)
                std::cout << Utils::RED << "\n[ERROR]: " << Utils::RESET << "Amount must be greater than Zero.\n\n";

            else if (currentStatus == TransactionStatus::INSUFFICIENT_FUNDS)
                std::cout << Utils::RED << "\n[ERROR]: " << Utils::RESET << "Insufficient funds!\n\n";

            else if (currentStatus == TransactionStatus::SUCCESS) {
                std::cout << Utils::GREEN << "\n[SUCCESS]: " << Utils::RESET << "The Converted amount is " << currentUser->changeCurrencyToUSD(amount) << "USD.\n";
                std::cout << "Please take your money!\n\n";

                //Same exact logic as the withdraw. We don't want them to steal from us.
                database.saveToFile();
            }


            system("pause");
            Utils::clearConsole();

            break;

        //Sign Out
        case 5:

            //Goodbye, user!
            std::cout << "See you later, " << currentUser->getName() << "! Have a great day.\n\n";

            system("pause");
            Utils::clearConsole();

            break;

        //The-garbage-collecter thing.
        default:
            
            //What are you trying to say, user?
            std::cout << Utils::RED << "[ERROR]: " << Utils::RESET << "Invalid input.\n\n";

            system("pause");
            Utils::clearConsole();

            break;
        }

        //This is the end...
    } while (inputChoice != 5);
}

//The admins screen.
void ATM_UI::adminScreen() {

    //What will the admin do tonight?
    int adminChoice;

    do {
        std::cout << "--- ADMIN CONTROL PANEL ---\n\n";
        std::cout << "1- VIEW STORED USERS DATA\n";
        std::cout << "2- TOTAL BANK VAULT CASH\n";
        std::cout << "3- EXIT TO MAIN MENU\n> ";
        std::cin >> adminChoice;
        Utils::clearConsole();

        //Yeah the admin can have the same characters problem.
        if (std::cin.fail())
            Utils::clearInputError();

        //We are talking about money here, so we need everything formatted correctly.
        std::cout << std::fixed << std::setprecision(2);

        switch (adminChoice) {

        //Viewing All Data
        case 1: {

            //We are grabbing a reference to all data we have.
            std::vector<User>& allData = database.getAllUsers();

            std::cout << "--- ALL REGISTERED ACCOUNTS ---\n\n";

            //Formating the table. The headers.
            std::cout << std::left;
            std::cout << std::setw(30) << "Name"
                      << std::setw(20) << "Card Number"
                      << std::setw(10) << "Balance\n";

            //Writing a full line of dashes (-) to seperate the headers.
            std::cout << std::string(61, '-')<<'\n';

            //Formating the table. The actual data.
            for (int index = 0; index < allData.size(); index++) {
                std::cout << std::setw(30) << allData[index].getName()
                          << std::setw(20) << allData[index].getCardNumber()
                          << std::setw(10) << allData[index].getBalance() << "EGP\n";
            }
            std::cout << '\n';

            system("pause");
            Utils::clearConsole();

            break;
        }

        //Total Vault Cash
        case 2: {

            //This returns how many total money in the bank.
            //They need an important report for the bank. I guess.
            std::cout << "--- TOTAL VAULT CASH ---\n\n";

            std::vector<User>& allData = database.getAllUsers();
            double totalVaultCash = 0.0;

            for (int index = 0; index < allData.size(); index++)
                totalVaultCash += allData[index].getBalance();

            std::cout << "Total Money in Bank Vault: " << totalVaultCash << "EGP\n\n";

            system("pause");
            Utils::clearConsole();

            break;
        }

        //Returning to the main menu.
        case 3:

            //The admin got more important things to do.
            std::cout << "RETURNING TO THE MAIN MENU\n\n";

            system("pause");
            Utils::clearConsole();

            break;
        
        //The-whatever-input-the-amdin-inputs
        default:

            //You are an admin....
            std::cout << Utils::RED << "[ERROR]: " << Utils::RESET << "Invalid input.\n\n";

            system("pause");
            Utils::clearConsole();

            break;
        }
    } while (adminChoice!=3);
}

//Congrats! You made it to the end.