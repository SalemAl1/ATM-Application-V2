#pragma once
#include <string>

//This enum repreasent the status of any transaction you can find in this App.
enum class TransactionStatus
{
	SUCCESS,
	INVALID_AMOUNT,
	INSUFFICIENT_FUNDS,
	MAX_LIMIT_EXCEEDED
};

//THE USER CLASS
class User
{
	//Some basic information about the user.
	//Of course they are pivate. You don't want people to see you password, do you?
private:
	std::string name;
	std::string cardNumber;
	std::string password;
	double balance;

public:
	//Contructor. Just initiates everthing to empty/zero.
	User();
	//Parameterized ontructor. Assigns the given data to the user.
	User(std::string newName, std::string newCardNumber, std::string newPassword);

	//Just a bunch of getters.
	std::string getName() { return name; }
	std::string getCardNumber() { return cardNumber; }
	std::string getPassword() { return password; }
	double getBalance() { return balance; }

	//Another bunch of setters.
	void setName(std::string name) { this->name = name; }
	void setCardNumber(std::string cardNumber) { this->cardNumber = cardNumber; }
	void setPassword(std::string password) { this->password = password; }
	void setbalance(double balance) { this->balance = balance; }

	//Checks if the password matches the stored one.
	bool login(std::string loginPassword) const;

	//A deposit function. Given the amount of money and returns the status.
	TransactionStatus deposit(double amount);

	//A withdraw function. Given the amount of money and returns the status.
	TransactionStatus withdraw(double amount);

	//A currency changing function. Given the amount of money in EGP and returns the converted as USD.
	double changeCurrencyToUSD(double EGP);
};