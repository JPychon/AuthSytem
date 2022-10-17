#pragma once

#include "uHash.h"
#include <iostream>

template<typename K, typename V>
class uAuthenticate : public uList<Entry<K, V>>
{

	public:

	typedef typename uList<typename Entry<K, V>::Entry>::nodeM* nodeIterator;

	uAuthenticate(int capacity, std::string fileName, int cHandling); // constructor for the authentication objects - initalizes the hashTable with the bucket-capacity, file-path, and collison handling method.
	void Initalize(); // handles the welcome-message as well as hash-table printout
	bool promptLogin(); // accepts user input for key/value then validates within the table and returns result as bool.


	private:

	uHash<K, V> DB_HashTable; // hash-table for the authentication object.



};

