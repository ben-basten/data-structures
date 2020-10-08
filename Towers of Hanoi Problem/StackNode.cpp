//Ben Basten
//StackNode.cpp contains the necessary operations for a node in a stack

#include <iostream>
#include <string>
#include <cstdlib>
#include "StackNode.h"
using namespace std;

//the constructor makes a stacknode with the passed in value and next value
StackNode::StackNode(int s, StackNode* n) {
	S = s;
	next = n;
}

//the destructor recursively deallocates the stack nodes
StackNode::~StackNode() {
	delete next;
}

//gets the current value of the stack node
int StackNode::getS() {
	return S;
}

// gets the next value of the stack node
StackNode* StackNode::getnext() {
	return next;
}

// sets the next value of the stack node
void StackNode::setnext(StackNode* n) {
	next = n;
}
