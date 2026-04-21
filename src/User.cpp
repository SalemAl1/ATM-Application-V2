#include <string>
#include "User.h"

//Contructor sets everything initially.
User::User()
    :name(""), cardNumber(""), password(""), balance(0.0) {}

//Contructor sets the attributes to a given parameters.
User::User(std::string newName, std::string newCardNumber, std::string newPassword)
    :name(newName), cardNumber(newCardNumber), password(newPassword), balance(0.0){}


//Checks for the given password with the stored one
bool User::login(std::string loginPassword) const {
    return password == loginPassword;
}

//Given the amount, returns the status. Depends on the balance
TransactionStatus User::deposit(double amount) {
    if (amount <= 0)
        return TransactionStatus::INVALID_AMOUNT;
    else {
        balance += amount;
        return TransactionStatus::SUCCESS;
    }
}

//Given the amount, returns the status. Depends on the balance
TransactionStatus User::withdraw(double amount){
    //Limit per transaction
    if (amount > 8000) 
        return TransactionStatus::MAX_LIMIT_EXCEEDED;
    if (amount <= 0)
        return TransactionStatus::INVALID_AMOUNT;
    else if (amount > balance)
        return TransactionStatus::INSUFFICIENT_FUNDS;
    else {
        balance -= amount;
        return TransactionStatus::SUCCESS;
    }
}

//Changes the currency from EGP to USD.
//The value is real btw
double User::changeCurrencyToUSD(double EGP) {
    double USD = 0.019; //updated 21/4/2026
    return EGP * USD;
}