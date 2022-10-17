#pragma once

#include "uHash.h"


template <typename K, typename V>
uHash<K, V>::uHash() { }

template<typename K, typename V>
uHash<K, V>::uHash(int capacity, std::string fileName, int cHandling)
{
	this->cHandling_ = cHandling;
	bucketCapacity = capacity;
	bucketSize = 0;

	if (cHandling_ == 0) // seperate chaining
	{
		uBucket.resize(bucketCapacity);
		for (int i = 0; i < bucketCapacity; ++i)
		{
			uBucket[i] = new uMap<K, V>(); // initalize the bucket-vector with map objects within each index.
		}
	}
	else if (cHandling_ == 1) // linear probing
	{
		uBucketP.resize(bucketCapacity);
		for (int i = 0; i < bucketCapacity; ++i)
		{
			uBucketP[i] = new Entry<K, V>(); // initalize the bucket-vector with entry objects within each index.
		}
	}

	this->dataFile; // initialize the fstream object to handle the data-stream.
	initalize_BucketData(fileName); // load the text-file content into the array after initalizing it.
}


template<typename K, typename V>
int uHash<K, V>::hash_Key(const K key) // polynomial hash function - hash consant: 1
{
	/*int n = key.length();
	long long sum = 0;
	int hashConstant = 1;

	for (size_t i = 0; i < key.length(); i++)
	{
		sum = sum + (key[i] * (std::pow(hashConstant, n - 1)));
		n--;
	}

	int hashKey = sum % 11;
	return hashKey;*/

	return (std::abs((3 * key) + 5) % 11);
	
}


template <typename K, typename V>
std::vector<std::string> uHash<K, V>::splitString(std::string str, std::string delimiter) // to split the stream into username/password
{
	std::vector<std::string> splitStrings; // vector to hold the split strings
	int start = 0;
	int end = str.length();
	int whiteSpacePos = str.find(delimiter);
	if (end != -1)
	{
		splitStrings.push_back(str.substr(start, whiteSpacePos - start)); // start to space
		splitStrings.push_back(str.substr(whiteSpacePos + 1, end - whiteSpacePos)); // space to end
	}

	return splitStrings;
}

template<typename K, typename V>
void uHash<K, V>::initalize_BucketData(std::string fileName)
{
	std::string temp_credStream; // local variable to hold 1 line of text from the file.
	std::vector<std::string> credStreamDataVector;
	K temp_username;
	V temp_password;

	dataFile.open(fileName, std::ios::in);
	if (dataFile.is_open())
	{
		while (std::getline(dataFile, temp_credStream))
		{
			credStreamDataVector = splitString(temp_credStream, " ");
			temp_username = credStreamDataVector[0];
			temp_password = credStreamDataVector[1];

			if (this->cHandling_ == 0) // seperate chaining
			{
				this->put(temp_username, temp_password);
			}
			else if (this->cHandling_ == 1) // linear probing
			{
				this->putP(temp_username, temp_password);
			}
		}

		dataFile.close();
	}
}

template <typename K, typename V>
int uHash<K, V>::get_cHandlingMethod() {
	return this->cHandling_;
}

// ----------------------------------------------------------------------------- [ SEPERATE CHAINING ] ------------------------------------------------------------------------------- //

template <typename K, typename V>
void uHash<K, V>::put(K k, V v)
{
	int HashIndex = hash_Key(k);
	uBucket.at(HashIndex)->put(k, v);
	bucketSize++;
}

template <typename K, typename V>
typename uList<typename Entry<K, V>::Entry>::nodeM* uHash<K, V>::find(K k)
{
	int HashIndex = hash_Key(k);
	typename uList<typename Entry<K, V>::Entry>::nodeM* result = uBucket.at(HashIndex)->find(k);
	return result;
}

template <typename K, typename V>
bool uHash<K, V>::match_KeyAndValue(K username, V password) {

	int HashIndex = hash_Key(username);
	typename uList<typename Entry<K, V>::Entry>::nodeM* result = uBucket.at(HashIndex)->find(username);

	if (result == NULL) // username doesnt exist.
	{
		return false;
	}
	else
	{
		if (result->nodeEntry.getValue() == password) // if password matches the username
		{
			return true;
		}
		else // if password doesnt match the username
		{
			return false;
		}
	}
}

template <typename K, typename V>
void uHash<K, V>::erase(K k)
{
	int HashIndex = hash_Key(k);
	uBucket.at(HashIndex)->erase(k);
}

template <typename K, typename V>
void uHash<K, V>::printHashTable()
{
	for (int i = 0; i < bucketCapacity; ++i)
	{
		{
			std::cout << "[" << i << "]: ";
			uBucket.at(i)->display_map_entryKeys();
		}
		std::cout << "\n";
	}
}

// ------------------------------------------------------------------------------- [ LINEAR PROBING ] -------------------------------------------------------------------------------- //

template <typename K, typename V>
bool uHash<K, V>::putP(K k, V v) {

	int HashIndex = hash_Key(k);
	bool valueInserted = false;

	for (int i = 0; !valueInserted && i < bucketCapacity; ++i)
	{
		if (uBucketP.at((HashIndex + i) % bucketCapacity)->getKey() == "") // index empty.
		{
			uBucketP.at((HashIndex + i) % bucketCapacity)->setKey(k); // set key
		}

		if (uBucketP.at((HashIndex + i) % bucketCapacity)->getKey() == k) // matching key
		{
			uBucketP.at((HashIndex + i) % bucketCapacity)->setValue(v); // set value
			valueInserted = true;
		}
	}

	return valueInserted;
}


template <typename K, typename V>
int uHash<K, V>::findP(K k) {

	int HashIndex = hash_Key(k);
	int entryIndex = -1;

	for (int i = 0; i < bucketCapacity; ++i)
	{
		if (uBucketP.at(i)->getKey() == k) 
		{
			entryIndex = i;
			return entryIndex;
		}
	}

	return entryIndex; // returns the index for which the value was found - returns -1 if key doesnt exist.
}

template <typename K, typename V>
bool uHash<K, V>::match_KeyAndValueP(K username, V password) {

	int HashIndex = hash_Key(username);
	bool valueMatches = false;
	for (int i = 0; i < bucketCapacity; ++i)
	{
		if (uBucketP.at(i)->getKey() == username)
		{
			if (uBucketP.at(i)->getValue() == password)
			{
				valueMatches = true;
			}
		}
	}
	
	return valueMatches;
}


template <typename K, typename V>
void uHash<K, V>::printHashTableP() {

	for (int i = 0; i < bucketCapacity; ++i)
	{
		std::string tempKey;
		tempKey = uBucketP.at(i)->getKey();
		if (tempKey == "") // if entry object within index has no key/value
		{
			std::cout << "[" << i << "]" << std::endl;
		}
		else // if entry object within index has key/value
		{
			std::cout << "[" << i << "] [username: " << tempKey << "]" << std::endl;
		}
	}
}

template <typename K, typename V>
bool uHash<K, V>::eraseP(K k) {

	int entryIndex = -1;
	entryIndex = findP(k);
	if (entryIndex != -1)
	{
		uBucketP.at(entryIndex).setKey() = ""; // sets the key to nothing to trigger the put function to use this index if needed.
		uBucketP.at(entryIndex).setValue() = ""; // sets the value to nothing to trigger the put function to use this index if needed.
	}
	else
	{
		std::cout << "[SYSTEM] Key not found" << std::endl;
	}
}


