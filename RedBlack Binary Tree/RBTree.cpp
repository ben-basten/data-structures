// Ben Basten
// RBTree.cpp is the top level of the binary tree that contains root and a structure of 
 // operations that can be performed

#include <iostream>
#include <string>
#include <cstdlib>
#include "RBTree.h"
#include "RBTreeNode.h"
#include "DRT.h"
#include "Database.h"
using namespace std;

// initializes root to null when a new tree is created
RBTree::RBTree() { 
	root = NULL; 
	debug = false;
}

// deallocate root when a tree is deleted
RBTree::~RBTree() { delete root; }

// setter for the root
void RBTree::setroot(RBTreeNode* r) { root = r; }

// adds a new key to the tree
DRT* RBTree::add(string key, string data) { //very similar to sample code
	// if root doesn't exist, root needs to point to a new TreeNode
	if (!root) {
		root = new RBTreeNode(key, data, nullptr, nullptr, nullptr, this);
		root->AddProcess();
		return new DRT("", "", "");
	}
	// if root does exist, the TreeNodes will recursively determine where the new key goes
	return root->add(key, data, "", "");
}

// searches the tree for the given key
DRT* RBTree::searchnode(string key) {
	if (!root) return new DRT("", "", ""); // if there's not a root, you know that the data, next, and prev values don't exist
	else return root->searchnode(key, "", ""); // if there is a root, recursively search the TreeNodes for that key
}

//gets the key value of the first element in the tree
string RBTree::first() {
	RBTreeNode* first;

	// if root exists, recursively go left all the way down the tree
	if (root) first = root->first();
	else return "";

	// return the key value of that first TreeNode
	return first->getk();
}

//last key in the tree (right all the way down)
string RBTree::last() {
	RBTreeNode* last;

	// if root exists, recursively go right all the way down the tree
	if (root) last = root->last();
	else return "";

	// return the key value of that last TreeNode
	return last->getk();
}

// calls the TreeNodes to recursively delete the desired key
DRT* RBTree::remove(string key) { //removes an item from the list
	return root->remove(key, "", "");
}

// Database search method
DRT* RBTree::search(string key) {
	//checks to see if we're searching on the empty string, if so builds a DRT with first() and last (), otherwise calls searchnode
	if (!root) return new DRT("", "", "");
	else if (key == "") return new DRT("", first(), last());
	else return root->searchnode(key, "", "");
}

//Database modify method
DRT* RBTree::modify(string key, string data) {
	if (key == "") return new DRT("", first(), last()); // if the key is empty, it's PRINT or RPRINT looking for first and last nodes
	if (data == "") {
		DRT* res = remove(key); // if no data, delete
		// if the debugging flag is set, run the red/black tree validity checker
		if (debug) {
			if (!Valid()) {
				// quit if there is a problem
				cout << "Invalid Tree!" << endl;
				exit(0);
			}
		}
		return res;
	}
	DRT* res = add(key, data); //otherwise, let's add a new element to the db!
	if (debug) {
		if (!Valid()) { // if the debugging flag is set, run the red/black tree validity checker
			cout << "Invalid Tree!" << endl;
			exit(0);
		}
	}
	return res;
}

// checks the binary tree to see if it is a valid structure
int RBTree::Valid() {
	int r;

	if (!root) { // binary tree good if there's no nodes
		r = 1;
	} else {
		if (!root->isblack()) { // root is always black
			r = 0;
		} else { // check for all other conditions
			r = root->ValidNode() != -1;
		}
	}
	return r;
}
