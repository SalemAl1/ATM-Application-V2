#pragma once
#include<string>
#include <vector>
#include "User.h"

//A class that supposed to handle the database.
class BankDatabase
{
private:
	//The vector used to store the users.
	std::vector<User> UsersData;

	//Just saves the file's name.
	std::string FILE_NAME = "data/database.txt";

public:

	//Constructor :/
	BankDatabase();

	//Checks for the admin password.
	bool adminAuth(std::string inputPassword);

	//Adds a new user to the users' vector.
	void addUser(User newUser);

	//Checks if the queried card number exists in the database or not.
	User* find(std::string queryCardNumber);

	//Get's all users.
	//This one is useful when signing in as an admin.
	std::vector<User>& getAllUsers() { return UsersData; }

	//Overwrites the database.txt file to update it.
	void saveToFile();
};
