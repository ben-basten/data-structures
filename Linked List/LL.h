//Ben Basten
//LL.h contains the method structure for the list

#ifndef _LL_
#define _LL_

#include <iostream>
#include <string>
#include <cstdlib>
#include "LLN.h"
using namespace std;

class LLN;

class LL {

private:
	LLN * head;

public:

	/* constructor */
	LL();

	/* destructor */
	~LL();

	/* adds a string to the head of the linked list */
	void add(string S);

	/* runs the radixsort.  Uses a loop to run split/paste for each
	   character position.  */
	void radixsort();

	/* prints out the linked list */
	void print();

	/* pastes all lists in the array of lists together and returns the head
    of the paste list.  Uses a loop to go through the array. */
	LLN * paste(LLN ** lists);
};


#endif
