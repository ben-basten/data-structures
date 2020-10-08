// Ben Basten
// Tree.cpp is the top level of the binary tree that contains the root,
 // and it can perform operations with the TreeNodes.

#include <iostream>
#include <string>
#include <cstdlib>
#include "Tree.h"
#include "DRT.h"
#include "TreeNode.h"
using namespace std;

// initializes root to null when a new tree is created
Tree::Tree() { root = NULL; }

// deallocate root when a tree is deleted
Tree::~Tree() { delete root; }

// setter for the root
void Tree::setroot(TreeNode* r) { root = r; }

// adds a new key to the tree
DRT* Tree::add(string key, string data) { //very similar to sample code
	// if root doesn't exist, root needs to point to a new TreeNode
	if (!root) {
		root = new TreeNode(key, data, nullptr, nullptr, nullptr, this);
		return new DRT("", "", "");
	}
	// if root does exist, the TreeNodes will recursively determine where the new key goes
	return root->add(key, data, "", "");
}

// searches the tree for the given key
DRT* Tree::searchnode(string key) { 
	if (!root) return new DRT("", "", ""); // if there's not a root, you know that the data, next, and prev values don't exist
	else return root->searchnode(key, "", ""); // if there is a root, recursively search the TreeNodes for that key
}

//gets the key value of the first element in the tree
string Tree::first() {
	TreeNode* first;

	// if root exists, recursively go left all the way down the tree
	if (root) first = root->first();
	else return "";

	// return the key value of that first TreeNode
	return first->getk();
}

//last key in the tree (right all the way down)
string Tree::last() { 
	TreeNode* last;

	// if root exists, recursively go right all the way down the tree
	if (root) last = root->last();
	else return "";

	// return the key value of that last TreeNode
	return last->getk();
}

// calls the TreeNodes to recursively delete the desired key
DRT* Tree::remove(string key) { //removes an item from the list
	return root->remove(key, "", "");
}

// Database search method
DRT* Tree::search(string key) { 
	  //checks to see if we're searching on the empty string, if so builds a DRT with first() and last (), otherwise calls searchnode
	if (!root) return new DRT("", "", "");
	else if (key == "") return new DRT("", first(), last());
	else return root->searchnode(key, "", "");
}

//Database modify method
DRT* Tree::modify(string key, string data) { 
	if (key == "") return new DRT("", first(), last()); // if the key is empty, it's PRINT or RPRINT looking for first and last nodes
	if (data == "") return remove(key); // if no data, delete
	return add(key, data); // if there is a key and data, add to the tree
}
