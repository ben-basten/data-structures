//Ben Basten
//StackNode.h defines the structure for the Nodes in the stack

#ifndef _STACKNODE_
#define _STACKNODE_

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class StackNode {
private:
	// each node contains an integer and a next value
	int S;
	StackNode* next;
public:
	// method structure for the constructor
	StackNode(int s, StackNode* n);
	// method structure for the destructor
	~StackNode();
	// method structure to get the value in the node
	int getS();
	// method structure for setting the next value of a node
	void setnext(StackNode* n);
	// method structure for getting the next value of a node
	StackNode* getnext();
};
#endif
