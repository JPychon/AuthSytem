#pragma once


#include "uAuthenticate.h"


template<typename K, typename V>
uAuthenticate<K, V>::uAuthenticate(int capacity, std::string fileName, int cHandling) : DB_HashTable(capacity, fileName, cHandling) {
	Initalize();
}

template<typename K, typename V>
void uAuthenticate<K, V>::Initalize() {

	bool loginStatus = false;

	std::cout << "\n\n\n";
	std::cout << "[SYSTEM] Welcome to credentinals authentication page" << "\n";
	std::cout << "[SYSTEM] The system only accepts letters as a valid form of input - any other input will be rejected by the system" << "\n";
	std::cout << "[SYSTEM] Please follow the instructions to successfully login." << "\n\n\n";

	if (this->DB_HashTable.get_cHandlingMethod() == 0) // seperate chaining
	{
		this->DB_HashTable.printHashTable();
	}
	else if (this->DB_HashTable.get_cHandlingMethod() == 1) // linear probing
	{
		this->DB_HashTable.printHashTableP();
	}
	

	std::cout << "\n\n";

	promptLogin();
	// loginStatus = promptLogin(); - commented for debugging purposes to keep the loop repeating - uncomment to end the application after a succesfull login.
	while(loginStatus == false)
	{
		std::string response;
		std::cout << "[SYSTEM] Would you like to try again? [Y] to continue - [N] to exit" << std::endl;
		std::getline(std::cin, response);
		if (response == "Y")
		{
			promptLogin();
		}
		else if (response == "N")
		{
			exit(0);
		}
	}
}

template<typename K, typename V>
bool uAuthenticate<K,V>::promptLogin()
{
	bool validationFlag = false; // set to true if input username/password match an entry in the bucket array
	std::string temp_username;
	std::string temp_password;

	std::cout << "[SYSTEM] Please insert your username" << "\n";
	std::getline(std::cin, temp_username);

	std::cout << "[SYSTEM] Please insert your password" << "\n";
	std::getline(std::cin, temp_password);

	if (this->DB_HashTable.get_cHandlingMethod() == 0) // seperate chaining
	{
		validationFlag = DB_HashTable.match_KeyAndValue(temp_username, temp_password);
	}
	else if (this->DB_HashTable.get_cHandlingMethod() == 1) // linear probing
	{
		validationFlag = DB_HashTable.match_KeyAndValueP(temp_username, temp_password);
	}


	if (!validationFlag)
	{
		std::cout << "[SYSTEM] Authorization failure" << "\n\n";
		return false;
	}
	else
	{
		std::cout << "[SYSTEM] Authorization successful" << "\n\n";
		return true;
	}
}