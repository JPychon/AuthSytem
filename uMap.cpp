#pragma once

#include "uMap.h"



template<typename K, typename V>
uMap<K, V>::uMap() {

	this->mapList;
}

template<typename K, typename V>
void uMap<K, V>::add_map_entry(EntryObj mapEntry) {

	this->mapList.add_node(mapEntry);
}

template<typename K, typename V>
typename uList<typename Entry<K, V>::Entry>::nodeM* uMap<K, V>::find(const K& k) {

	typename uList<Entry<K, V>>::nodeM* temp = new typename uList<Entry<K, V>>::nodeM;
	temp = this->mapList.header;

	while (temp != NULL) // loops through the list
	{
		if (temp->nodeEntry.getKey() == k) // compares the node-entry key with the one provided in the arguments
		{
			return temp; // if they match - return the nodeM pointer
		}
		else
		{
			temp = temp->next; // otherwise - move to the next
		}
	}

	std::cout << "[SYSTEM] Key not found" << std::endl; // if not found - send an error message
	delete temp; // delete the temp pointer to free memory.
	return NULL;
}

template<typename K, typename V>
void uMap<K, V>::display_map_entry() {
	this->mapList.display_nodes();
}

template<typename K, typename V>
void uMap<K, V>::display_map_entryKeys() {
	this->mapList.display_nodeKeys();
}

template <typename K, typename V>
void uMap<K, V>::put(const K& k, const V& v) {

	typename uList<Entry<K, V>>::nodeM* temp = new typename uList<Entry<K, V>>::nodeM;
	temp = this->mapList.header;
	bool valueReplaced = false; // flag for when the value is replaced to end the loop

	if (temp == NULL)
	{
		typename Entry<K, V>::Entry newEntry;
		newEntry.setKey(k);
		newEntry.setValue(v);
		this->mapList.add_node(newEntry);
		return;
	}

	while (temp != NULL || valueReplaced != true) // loop as long as temp is not null or the flag hasn't been checked
	{
		if (temp->nodeEntry.getKey() == k)
		{
			temp->nodeEntry.setValue(v); // sets the new value to the entry
			valueReplaced = true;
			return;
		}
		else
		{
			if (temp->next == NULL) // if the end of the list is reached - create a new node & place it at the end.
			{
				typename Entry<K, V>::Entry newEntry;
				newEntry.setKey(k);
				newEntry.setValue(v);
				this->mapList.add_node(newEntry);
				return;
			}
			else
			{
				temp = temp->next; // otherwise - keep going till the end of the list.
			}
		}
	}
}


template <typename K, typename V>
void uMap<K, V>::erase(const K& k) {

	typename uList<Entry<K, V>>::nodeM* temp = new typename uList<Entry<K, V>>::nodeM;
	temp = find(k); // uses the find function to return an iteratior/pointer to the location of the node with the provided key.
	if (temp == this->mapList.header || temp == this->mapList.trailer) // checks if the node is the head/trailer of the list
	{
		erase(temp); // if that's the case - use the erase fucntion down below to delete it
		return;
	}
	else
	{
		temp = temp->prev; // otherwise - set the temporary pointer to the node before the one we want to delete and call the deelte node function
		this->mapList.delete_nodeP(temp);
	}
}

template <typename K, typename V>
void uMap<K, V>::erase(nodeIterator mNode) { // deletes a node by providing a ndoe pointer in the arguments

	typename uList<Entry<K, V>>::nodeM* temp = new typename uList<Entry<K, V>>::nodeM;
	temp = mNode;
	this->mapList.delete_nodeC(temp);

}

template <typename K, typename V>
int uMap<K, V>::size() const {

	return this->mapList.getListSize();
}

template <typename K, typename V>
bool uMap<K, V>::isEmpty() const {

	return this->mapList.isEmpty();
}


template <typename K, typename V>
typename uList<typename Entry<K, V>::Entry>::nodeM* uMap<K, V>::begin() { // returns a node pointer at the header of the list.

	return this->mapList.get_Header();
}

template <typename K, typename V>
typename uList<typename Entry<K, V>::Entry>::nodeM* uMap<K, V>::end() { // returns a node pointer at the trailer of the list.

	return this->mapList.get_Trailer();
}


