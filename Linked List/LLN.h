//Ben Basten
//LLN.h contains the method structure for the nodes of a linked list

#ifndef _LLN_
#define _LLN_

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class LLN {

private:

	LLN * next;
	string s;

public:

	/* constructor */
	LLN(LLN *n, string S);

	/* destructor */
	~LLN();

	/* returns the length of the longest string in the list */
	int longest();

	/* splits the list into 27 lists (stored in array lists) around
	   position pos */
	void split(int pos, LLN **lists);

	/* pastes b to the end of the current list */
	void paste(LLN * b);

	/* prints list */
	void print();

};
#endif
