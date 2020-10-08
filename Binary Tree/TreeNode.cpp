// Ben Basten
// TreeNode.cpp contains the data of the database and can perform recursive operations on the data

#include <iostream>
#include <string>
#include <cstdlib>
#include "DRT.h"
#include "TreeNode.h"
using namespace std;

// constructor - initializes new TreeNode
TreeNode::TreeNode(string key, string data, TreeNode* l, TreeNode* r, TreeNode* p, Tree* T) {

	k = key; 
	d = data; 
	left = l;
	right = r; 
	parent = p; 
	t = T;
}

// also deletes the right and left nodes if a specific TreeNode is deleted (wipes out entire tree underneath)
TreeNode::~TreeNode() { //destructor

	delete left;
	delete right;
}

// recursively adds a new node to the tree
DRT* TreeNode::add(string key, string data, string n, string p) {
	DRT* temp = new DRT("", "", "");
	// if the new key equals an existing key, increment the data count for that node
	if (k == key) {
		int newCount = (d[0] + '1') - '0';
		d = (char)newCount;
	// if the new key is less than the existing key, it belongs in the left node
	} else if (key < k) {
		// if left is empty, that's the new home!
		if (left == nullptr) {
			left = new TreeNode(key, data, nullptr, nullptr, this, t);
		// if not empty, continue searching where the new key belongs on the left node
		} else {
			left->add(key, data, n, p);
		}
	// if the new key is more than the existing key, it belongs in the right node
	} else {
		// if right is empty, that's the new home!
		if (right == nullptr) {
			right = new TreeNode(key, data, nullptr, nullptr, this, t);
		}
		// if right is not empty, continue searching where the new key belongs on the right node
		else {
			right->add(key, data, n, p);
		}
	}

	// not really sure why the add method isn't 'void'
	return temp;
}

// recursively searches for a given key
DRT* TreeNode::searchnode(string key, string n, string p) {
	if (k == key) { // we found the desired node!
		string next, prev;
		if (!right) next = n;
		else next = right->first()->getk();
		if (!left) prev = p;
		else prev = left->last()->getk();
		return new DRT(d, next, prev); // send the data with the determined next and prev values
	}
	if (k < key) {
		if (right) return right->searchnode(key, n, k); // current key is now the previous so far
		return new DRT("", n, k);
	}
	if (left) return left->searchnode(key, k, p); // current key is now the next so far
	return new DRT("", k, p);
}

// recursively goes left all the way down the tree to find the first node
TreeNode* TreeNode::first() {
	TreeNode* first;
	if (left != nullptr) first = left->first();
	else return this;

	return first;
}

// recursively goes right all the way down the tree to find the last node
TreeNode* TreeNode::last() { 
	TreeNode* last;
	if (right != nullptr) last = right->last();
	else return this;

	return last;
}

// getter for the key
string TreeNode::getk() { return k; }
// getter for the data
string TreeNode::getd() { return d; }
// getter for the right node
TreeNode* TreeNode::getright() { return right; }
// getter for the left node
TreeNode* TreeNode::getleft() { return left; }

// gets the next node in the tree, which is always the node to the right
string TreeNode::next() {
	TreeNode* next;
	if (right) next = right->first();
	else return "";

	return next->getk();
}

// gets the previous node in the tree - THIS CODE IS WRONG
string TreeNode::prev() {
	TreeNode* prev;
	if (left) prev = left->last();
	else return "";

	return prev->getk();
}

//similar to search; keeps track of nsf and psf
 //just works its down to the tree to find the node to remove
 //then calls remove ()
DRT* TreeNode::remove(string key, string n, string p) {
	if (k == key) { // if the current node's key matches the desired key, perform removal
		string prev;
		if (left) prev = left->getk();
		else if (parent) prev = parent->getk();
		else prev = "";

		DRT* removed;

		// if the data count is more than 1, the data only needs to be decremented
		int count = d[0] - '0';
		if (count > 1) {
			d = to_string(stoi(d) - 1);
			removed = new DRT(d, right ? right->getk() : "", prev);
			return removed;
		}

		// if the data count is 1, the whole Node needs to be removed
		removed = new DRT("0", right ? right->getk() : "", prev);
		this->remove();

		return removed;
	}
	// if the current node's key is less than the desired key, search for the node to remove on the right
	else if (k < key) {
		return right->remove(key, n, p);
	// if the current node's key is greater than the desired key, search for the node to remove on the left
	} else {
		return left->remove(key, n, p);
	}
}

//the physical removal (decides whether it's 0, 1, or 2-child case and possibly copies key and data values and physically removes the deleted node
void TreeNode::remove() {
	// if 2 children, go right one left all the way down and copy that data into the node to remove
	if (right && left) {
		TreeNode* next = right->first();
		k = next->getk();
		d = next->getd();

		if (right == next) right = nullptr;
		
		next->remove();
	// if one child, change the parents pointer to point to the child
	} else if (right && !left) {
		if (parent == nullptr) {
			t->setroot(right);
			right->setparent(nullptr);
		}
		else if (parent->getk() > k) parent->setleft(right);
		else parent->setright(right);

		// forgot to set the parent initially, created many bugs
		right->setparent(parent);

		right = nullptr;
		left = nullptr;

		delete this;
	// if one child, change the parents pointer to point to the child
	} else if (left && !right) {
		if (parent == nullptr) {
			t->setroot(left);
			left->setparent(nullptr);
		}
		else if (parent->getk() > k) parent->setleft(left);
		else parent->setright(left);

		left->setparent(parent);

		right = nullptr;
		left = nullptr;

		delete this;
	// if no children, go ahead and just delete it
	} else {  
		if (parent == nullptr) t->setroot(nullptr);
		else if (parent->getk() > k) parent->setleft(nullptr);
		else parent->setright(nullptr);

		right = nullptr;
		left = nullptr;

		delete this;
	}
}

// setter for the parent
void TreeNode::setparent(TreeNode* p) { parent = p; }
// setter for the left
void TreeNode::setleft(TreeNode* l) { left = l; }
// setter for the right
void TreeNode::setright(TreeNode* r) { right = r; }


