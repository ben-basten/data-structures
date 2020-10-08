// Ben Basten
// HashNode.cpp contains the individual node-level operations to add, remove, and find a key

#include <iostream>
#include <string>
#include <cstdlib>
#include "HashNode.h"
#include "DRT.h"
using namespace std;

HashNode::HashNode(string key, string data) {
	k = key; d = data; next = NULL;
}

HashNode::~HashNode() { //destructor
	delete next;
}


DRT* HashNode::searchnode(string key) {

	if (k == key) return new DRT(d, "", "");
	if (!next) return new DRT("", "", "");
	return next->searchnode(key);
}

DRT* HashNode::addnode(string key, string data) {
	if (key == k) d = data;
	else if (next == nullptr) next = new HashNode(key, data);
	else next->addnode(key, data);

	return new DRT(key, "", "");
}

string HashNode::getk() { return k; }
string HashNode::getd() { return d; }

DRT* HashNode::remove(string key, HashNode* p, HashNode*& listhead) {
	if (k == key) {
		DRT* ret = new DRT(d, "", "");
		if (!p) {
			listhead = next;
			next = nullptr;
			delete this;
		} else {
			p->setnext(next);
			next = nullptr;
			delete this;
		}
		return ret;
	} else if (next) return next->remove(key, this, listhead); 
	else return new DRT("", "", ""); // good catch!
}


void HashNode::setnext(HashNode* p) { next = p; }