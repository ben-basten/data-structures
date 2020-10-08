//Ben Basten
//operations for a stack that can perform PUSH, POP, and ISEMPTY

#include <iostream>
#include <string>
#include <cstdlib>
#include "LLStack.h"
#include "StackNode.h"
using namespace std;

//constructor for creating a new stack
LLStack::LLStack() {
	//by default, the head is empty since it is a new stack
	head = NULL;
}

//destructor for deallocating a stack
LLStack::~LLStack() {
	delete head;
}

//adds a new item to the top of the stack
void LLStack::PUSH(int s) {

	head = new StackNode(s, head);
}

//removes the most recent item from the stack
int LLStack::POP() {
	//switches the head to point to the second most recent item in the stack
	StackNode* h = head;
	int s = h->getS();
	head = h->getnext();
	h->setnext(NULL);
	delete h;
	return s;
}

//checks if there is anything in the stack
bool LLStack::ISEMPTY() {
	return !head;
}
