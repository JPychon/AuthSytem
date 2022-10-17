
#ifndef uMap_H
#define uMap_H

#include "uList.h"
#include <iostream>
#include <string>


template<typename K, typename V>
class uMap : public uList<Entry<K, V>> // Entry class inheritance.
{
public:


	struct nodeM; // forward declaration for the nodeM struct.
	typedef typename uList<typename Entry<K, V>::Entry>::nodeM* nodeIterator;
	typedef typename Entry<K, V>::Entry EntryObj;

	uMap();
	void add_map_entry(EntryObj mapEntry); // adds a new entry/node to the map
	void display_map_entry(); // displays a list of the nodes along with their entries in the map-list
	void display_map_entryKeys(); // displays a list of the nodes along with their keys in the map-list
	nodeIterator find(const K& k); // find entry with key k
	void put(const K& k, const V& v); // insert/replace pair (k,v>
	void erase(const K& k); // remove entry with key K
	void erase(nodeIterator mNode); // removes an entry with specified node-pointer
	int size() const; // number of entries in the map
	bool isEmpty() const; // returns true if map is empty


	nodeIterator begin(); // iterator to the head of the list
	nodeIterator end(); // iterator to the trailer of the list.


private:

	uList<Entry<K, V>> mapList; // doubly linked list object per each map structure



};

#endif

