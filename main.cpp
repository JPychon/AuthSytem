// CSCI 230 - Project 1
// Author: John Hanna
// Project Title: Authentication System
/* Structure:
	Entry.h: Template class of an object holdihg a pair of two values representing the username/password
	uList.h: Template class of a doubly linked list containing the node structure where each node holds an entry object.
	uMap.h: Template class of a map that holds a doubly linked list which is used within each bucket.
	uHash.h: Template class that handles the hashing algorithm as well as initalization of the BucketArray which contains a map within each bucket.
	uAuthenticate.h:: Template class that handles the user authentication process.
	main.cpp: Main thread of the program used to debug & test the classes.
*/
// The program is a simple authentication system that currently handles logins only - the username/password is loaded
// from a text file where the usernames are hased within the hashFunction & then added into the BucketArray. Once the 
// user tries to login - the fucntion compared the input [username/password] to the existing list & succeeds if match
// is found or fails/retries if no match found. 

// the program has 2 collision handling methods available to use - on start the user is able to select which method will be used for the map
// [0] -> initalizes the hashTable collision handling with seperate chaining
// [1] -> initalizes the hashTable collision handling with lienar probing

// P.S: Update FileDirectory path-string [main.cpp: line 39].

#include <iostream>

#include "uMap.h"
#include "ulist.h"
#include "Entry.h"
#include "uHash.h"
#include "uAuthenticate.h"

#include "uMap.cpp"
#include "uList.cpp"
#include "uHash.cpp"
#include "uAuthenticate.cpp"


int main()
{
	std::string fileDirectory = "PLEASE CHANGE ME"; // file path <---------- CHANGE

	int cHandling = -1;
	std::cout << "[SYSTEM] COLLISION HANDLING SETTINGS" << std::endl;
	std::cout << "[SYSTEM] Please input [0] for Seperate Chaining" << std::endl;
	std::cout << "[SYSTEM] Please input [1] for Lienar Probing" << std::endl;

	std::cin >> cHandling; // set collision handling method
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (cHandling != 0 && cHandling != 1) // range from 0 to 1
	{
		std::cout << "[SYSTEM] Please input a number between 0 and 1 - try again..." << std::endl;
		std::cin >> cHandling;
	}
	

	uAuthenticate<std::string, std::string> userAuthentication(11, fileDirectory, cHandling); // authentication object

	userAuthentication.Initalize(); //
}
