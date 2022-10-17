#pragma once

#include "uList.h"


template<class Entry>
uList<Entry>::uList() {

	header = NULL;
	trailer = NULL;
	listSize = 0;
}

template<class Entry>
void uList<Entry>::add_node(Entry mEntry) {

	nodeM* temp = new nodeM(mEntry); // temp. node with an entry object
	temp->next = NULL;

	if (header == NULL) // if list is empty
	{
		header = temp;
		trailer = temp;
		listSize++; // increment the list size
	}
	else
	{
		trailer->next = temp;
		temp->prev = trailer;
		trailer = trailer->next;
		listSize++;
	}

}

template <class Entry>
void uList<Entry>::delete_nodeP(nodeM* mNode_before) {

	nodeM* temp = new nodeM;
	temp->next = NULL;
	temp->prev = NULL;
	temp = mNode_before->next;
	if (temp->next == NULL) // check if node is at the end
	{
		mNode_before->next = NULL;
	}
	else
	{
		mNode_before->next = temp->next;
		temp->next->prev = mNode_before;
	}

	listSize--;
	delete temp;
}

template <class Entry>
void uList<Entry>::delete_nodeC(nodeM* mNode) {

	nodeM* temp = new nodeM;
	temp->next = NULL;
	temp->prev = NULL;
	temp = mNode;;
	if (temp == trailer && temp == header) // check if the node is the trailer - thus assigning a new trailer to the list.
	{
		header = NULL;
		trailer = NULL;
	}
	else if (temp == header) // check if the node is the header - thus assigning a new header to the list.
	{
		header = temp->next;
		header->prev = NULL;
	}
	else if (temp == trailer)
	{
		trailer = trailer->prev;
		trailer->next = NULL;
	}
	listSize--;
	delete temp;
}

template<class Entry>
void uList<Entry>::display_nodes() {

	nodeM* temp = new nodeM();
	temp = header;

	int iterationPosition = 0; // keep count of position.

	while (temp != NULL && temp->nodeEntry.getKey() != "")
	{
		std::cout << "Entry[" << iterationPosition + 1 << "] "; // position in the list [+1]
		std::cout << "(Key: ";
		temp->nodeEntry.displayKey(); // displays the entry key
		std::cout << " - Value: ";
		temp->nodeEntry.displayValue(); // displays the entry value
		std::cout << ")" << " ";

		temp = temp->next;
		iterationPosition++;
	}

	delete temp;
}

template<class Entry>
void uList<Entry>::display_nodeKeys() {

	nodeM* temp = new nodeM();
	temp = header;

	int iterationPosition = 0; // keep count of position.

	while (temp != NULL && temp->nodeEntry.getKey() != "")
	{
		std::cout << "[index " << iterationPosition + 1 << "]: "; // position in the list [+1]
		std::cout << "[Username: ";
		temp->nodeEntry.displayKey(); // displays the entry key
		std::cout << "]" << " ";

		temp = temp->next;
		iterationPosition++;
	}

	delete temp;
}

template<class Entry>
int uList<Entry>::getListSize()
{
	return listSize;
}


template<class Entry>
bool const uList<Entry>::isEmpty()
{
	return getListSize() == 0;
}


template<class Entry>
typename uList<Entry>::nodeM* uList<Entry>::get_Header() {

	return (header);
}

template<class Entry>
typename uList<Entry>::nodeM* uList<Entry>::get_Trailer() {

	return (trailer);
}