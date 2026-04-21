#include<string>
#include <vector>
#include <fstream>
#include "BankDatabase.h"
#include "User.h"

//The implementation for the database class.

//The constructor of the class.
//This constructor reads from the file, database.txt, and saves the records into the users' vector.
//If it happens to the file to not be there, it will just skip the loop.
//Skipping the loops causes the vector to start completely empty.
BankDatabase::BankDatabase() {
	//Opens an input file stream.
	std::ifstream readFromFile(FILE_NAME);

	//Just some temporary holders for the data.
	std::string tempName;
	std::string tempCardNumber;
	std::string tempPassword;
	std::string tempBalanceString;
	double tempBalance;

	//A loop runs through the file.
	//It stores the 'tokens' into its corresponding holder.
	//It seperates them with a comma.
	while (std::getline(readFromFile, tempName, ',')) {

		std::getline(readFromFile, tempCardNumber, ',');
		std::getline(readFromFile, tempPassword, ',');
		std::getline(readFromFile, tempBalanceString, '\n');

		//Just converting a string to a double.
		tempBalance = std::stod(tempBalanceString);

		User loadedUser(tempName, tempCardNumber, tempPassword);
		loadedUser.setbalance(tempBalance);

		UsersData.push_back(loadedUser);
	}

	//Closes the file to free system resources.
	readFromFile.close();
}

//Takes the password from the user and compare it with the already set one.
bool BankDatabase::adminAuth(std::string inputPassword){
	//Bet no one would guess that :P
	std::string adminPassword = "SuperUltimateSecret123";
	return inputPassword==adminPassword;
}

//Pushes the new user's data into the vector.
void BankDatabase::addUser(User newUser) {
	UsersData.push_back(newUser);
}

//Searches for the queried card number.
//If it finds it, it returns a pointer to the whole user's record (name, cardNumber, etc.)
User* BankDatabase::find(std::string queryCardNumber) {
	for (int index = 0; index < UsersData.size(); index++) 
		//It compares the queried card number with each card number stored in our database.
		//When it finds a match, it returns th whole thing as an address.
		if (queryCardNumber == UsersData[index].getCardNumber())
			return &UsersData[index];
	//If not, it returns an null pointer.
	return nullptr;
}

//The exact opposite of our constructor's job.
//This function saves the users' vector into the database.txt.
//It overwrites the whole file everytime this function is called.
//If the file, database.txt, doesn't exist, it simply creates it.
void BankDatabase::saveToFile() {
	//Opens an output file stream.
	std::ofstream writeToFile(FILE_NAME);

	//Iterates over our vector and store each information separated by a single comma.
	//Doing this so we can read the file again in our constructor.... Plot twist.
	for (int index = 0; index < UsersData.size(); index++) {
		writeToFile << UsersData[index].getName() << ','
					<< UsersData[index].getCardNumber() << ','
					<< UsersData[index].getPassword() << ','
					<< UsersData[index].getBalance() << '\n';
	}

	//Saves and closes the file.
	writeToFile.close();
}