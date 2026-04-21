#pragma once
#include "BankDatabase.h"
#include "User.h"

//The ATM UI class.
//Here's the part the user actually sees.
class ATM_UI
{
private:
	//An object of BankDatabase.
	//We will need this object later :/
	BankDatabase database;

public:
	//The first screen the user sees when running the App. 
	void welcomeScreen();

	//The screen the user sees as a member, when they log in.
	void userScreen(User* currentUser);

	//Only admins are allowed to see this menu. Well.... Of course you can too.
	void adminScreen();
};