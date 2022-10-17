#ifndef uLIST_H
#define uLIST_H

#include "Entry.h"


template<class Entry>
class uList
{

public:

	struct nodeM { // node structure for the doubly linked list - each node holds: [next & prev pointers - <Entry> object which holds the username/password]
		Entry nodeEntry; // entry object per node
		nodeM* next; // -> next pointer
		nodeM* prev; // <- previous pointer
		nodeM() {} // defualt constructor - initalizes an entry object with null values
		nodeM(Entry nodeEntry) : nodeEntry{ nodeEntry } {} // parametric constructor - initalizez an entry object provided through the arguments.

	};

	uList();
	void add_node(Entry mEntry); // adds a node to the end of the linked list [each node containing an entry object provided in the function parameters]
	void delete_nodeP(nodeM* mNode); // deletes a node from the list by providing the node-previous in the parameters
	void delete_nodeC(nodeM* mNode); // deletes a node from the list by providing the specfific node in the parameters [used for header/trailer]
	void display_nodes(); // displays all the nodes & their content within the list.
	void display_nodeKeys(); // displays all the node keys only within the list

	int getListSize(); // returns the size of the linked list.
	bool const isEmpty(); // returns true if the linked list is empty

	nodeM* get_Header(); // returns the header of the list
	nodeM* get_Trailer(); // retuirns the trailer of the list


	int listSize; // number of nodes within the list.
	nodeM* header;
	nodeM* trailer;
						 
};

	


#endif 