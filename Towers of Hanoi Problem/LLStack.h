//Ben Basten
//contains the method structure for a stack

#ifndef _LLSTACK_
#define _LLSTACK_

#include <iostream>
#include <string>
#include <cstdlib>
#include "StackNode.h"
using namespace std;

//uses the StackNode class, so include it
class StackNode;
class LLStack {
private:
	StackNode* head;
public:
	//method structure to push a new item to the stack
	void PUSH(int s);
	//method structure to pop an item from the stack
	int POP();
	//method structure to check if the stack is empty
	bool ISEMPTY();
	//method structure for the constructor
	LLStack();
	//method structure for the destructor
	~LLStack();
};






#endif
