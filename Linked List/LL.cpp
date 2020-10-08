//Ben Basten
//LL.cpp contains a list and has functionality to sort/print/paste lists together

#include <iostream>
#include <string>
#include <cstdlib>
#include "LL.h"
using namespace std;

// constructor to create a new linked list
LL::LL() {
	head = nullptr;
}

// starts a chain of deletions to deallocate the whole linked list
LL::~LL() {
	delete head;
}

// adds a new node to the front of the list
void LL::add(string l) {
	head = new LLN(head, l);
}

// sorts the list by dividing it into alphabetical lists letter by letter and pastes the lists together
void LL::radixsort() {
	if (!head) return;
	int length = head->longest();
	for (int i = length - 1; i >= 0; i--) {
		// create the 27 lists for the words to be sorted into
		LLN **lists = new LLN*[27];
		for (int j = 0; j < 27; j++) {
			lists[j] = nullptr;
		}
		// splits the current list into alphabetical and <empty> lists
		head->split(i, lists);
		// changes the head to the newly sorted list
		head = paste(lists);
		// deallocate the 27 lists so there's no data leftover next time the loop runs
		delete[] lists;
	}
}

// starts a recursive chain of nodes printing out their data
void LL::print() {
	if (head) head->print();
	cout << endl;
}

// goes through the 27 lists and merges them into a single linked list
LLN * LL::paste(LLN ** lists) {
	LLN * newHead = nullptr;
	for (int i = 0; i < 27; i++) {
		if (lists[i] != nullptr) {
			// use the paste method to merge the new list with one of the 27 lists
			if (newHead == nullptr) newHead = lists[i];
			else newHead->paste(lists[i]);
		}
	}
	return newHead;
}
