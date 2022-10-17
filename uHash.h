#pragma once

#include "uMap.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

template<typename K, typename V>
class uHash : public uList<Entry<K, V>>
{

public:

	typedef typename uList<typename Entry<K, V>::Entry>::nodeM* nodeIterator;

	uHash(); // default constructor
	uHash(int capacity, std::string fileName, int cHandling); // class constructor - initalizes the bucket vector capacity based on the arguments & calls initalize_BucketData();
	int hash_Key(const K key);  // hash function - polynomial hash function to hash/compress the usernames to be inserted into the bucket vector
	std::vector<std::string> splitString(std::string str, std::string delimiter); // function used to split the data-stream into 2 strings [username/password]
	void initalize_BucketData(std::string fileName); // loads the data from a text file into bucket array after hashing.
	int get_cHandlingMethod();


	//---------------------------------------------------[ SEPERATE CHAINING ]---------------------------------------------------------------//

	void put(K k, V v); // inserts a new key/value pair into the bucket vector by hashing the key & finding it's right location then inserting it. [replaces if duplicates - adds node if index used]
	void erase(K k); // erases a node within the hash map that has a matching key provided in the arguments
	void printHashTable(); // prints the data of the bucket array.
	nodeIterator find(K k); // finds an entry object within the matching key provided in the arguments - returns a node iterator.
	bool match_KeyAndValue(K username, V password); // bool function to search the hash table for matching values for authentication purposes.

	//---------------------------------------------------[ LINEAR PROBING ]-------------------------------------------------------------------//

	int findP(K k); // finds a key within the bucket vector
	bool putP(K k, V v); // inserts a new key/value pair into the bucket vector by hashing the key & finding it's right index then inserting it [replaces if duplicate - finds next empty index if used]
	bool eraseP(K k); // erases an element in the bucket vector
	bool match_KeyAndValueP(K username, V password); // bool function to search the bucket vector for matching values for authentication purposes
	void printHashTableP(); // prints the content of the bucket vector




private:

	int bucketCapacity; // int value representing the capacity of the bucket array [size]
	int bucketSize; // int value representing the total amount nodes present within the vector.
	int cHandling_; // int value representing the collision handling to be used for the bucket array. [0 = seperate chaining - 1 = linear probing]
	std::fstream dataFile; // fstream object to handle stream input/output for the username/password.
	std::vector<uMap<K, V>*> uBucket; // vector that represents the bucket array - each index contains a map object [seperate chaining]
	std::vector<Entry<K,V>*> uBucketP; // vector that represents the bucket array - each index contains an entry object [linear probing]
};

