
#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>

// Key: Numerical hashed value of the username
// Value: Numerical hashed value of the password
// Each entry object will represent a username/password combination stored within a node in a bucket within the bucket array.


template <typename K, typename V> // template class for generic types for each node.
class Entry
{

public:

	K key; // the key for each entry within the node 
	V value; // the value for each entry within the node 
	Entry() { } // default constructor
	Entry(K key, V value) : key(key), value(value) {} // parametric constructor for each entry object.
	void setKey(Entry<K, V> myEntry) { this->key = myEntry.key; } // sets a key of an entry object
	void setKey(K key) { this->key = key; } // sets a key provided through the arguments
	void setValue(Entry<K, V> myEntry) { this->value = myEntry.value; } // sets a value of an entry object
	void setValue(K value) { this->value = value; } // sets a value provided through the arguments
	K getKey() { return this->key; } // returns the object key. 
	V getValue() { return this->value; } // returns the object value 
	void displayKey() { std::cout << this->key; } // prints the object key
	void displayValue() { std::cout << this->value; } // prints the object value
};

#endif

