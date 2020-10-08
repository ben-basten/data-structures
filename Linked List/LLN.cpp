//Ben Basten
//LLN.cpp contains the data of single nodes of a linked list and logic
//to recursively perform a few functions with this data

#include <iostream>
#include <string>
#include <cstdlib>
#include "LLN.h"
using namespace std;

// constructor for creating a new node
LLN::LLN(LLN* n = nullptr, string l = "") {
	s = l;
	next = n;
}

// recursively deletes all successive nodes
LLN::~LLN() {
	delete next;
}

// recursively finds the longest string data in a LL node
int LLN::longest() {	
	int max;
	int length = s.length();
	// goes to end of list and backtracks to find the maximum
	if (next) max = next->longest();
	else return length;

	// if current length is bigger than the max, that is the new max
	if (max < length) return length;
	// the existing max is bigger; return that
	else return max;
}

// splits the list into 27 lists based on the current letter position
void LLN::split(int pos, LLN ** lists) {
	int length = s.length();
	if (next) next->split(pos, lists);
	// if the position is greater than the length of the word, add it to the empty list
	if ((length - 1) < pos) {
		next = lists[0];
		lists[0] = this;
	//find the position of the letter in the alphabet and put it into the corresponding index of list
	} else {
		int letterNum = (s[pos] - 'A') + 1;
		next = lists[letterNum];
		lists[letterNum] = this;
	}
}

// pastes the node in the argument to the end of the current list
void LLN::paste(LLN* b) { 
	if (!next) next = b;
	else next->paste(b);
}

//prints out the value of the current node
void LLN::print() {
	cout << s << endl;
	if (next) next->print();
}
