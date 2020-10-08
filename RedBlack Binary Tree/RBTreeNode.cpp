// Ben Basten
// RBTreeNode.cpp contains the individual data of the database and can perform recursive operations on the data

#include <iostream>
#include <string>
#include <cstdlib>
#include "DRT.h"
#include "RBTreeNode.h"
#include "RBTree.h"
#include "RBHelper.h"
using namespace std;

// constructor - initializes new TreeNode
RBTreeNode::RBTreeNode(string key, string data, RBTreeNode* l, RBTreeNode* r, RBTreeNode* p, RBTree* T) {

	k = key;
	d = data;
	left = l;
	right = r;
	parent = p;
	t = T;
	black = false;
}

// also deletes the right and left nodes if a specific TreeNode is deleted (wipes out entire tree underneath)
RBTreeNode::~RBTreeNode() { //destructor

	delete left;
	delete right;
}

// recursively adds a new node to the tree
DRT* RBTreeNode::add(string key, string data, string n, string p) {
	DRT* temp = new DRT("", "", "");
	// if the new key equals an existing key, increment the data count for that node
	if (k == key) {
		int newCount = (d[0] + '1') - '0';
		d = (char)newCount;
		// if the new key is less than the existing key, it belongs in the left node
	} else if (key < k) {
		// if left is empty, that's the new home!
		if (left == nullptr) {
			left = new RBTreeNode(key, data, nullptr, nullptr, this, t);
			left->AddProcess(); // after physical addition, change colors/balance out the tree
			// if not empty, continue searching where the new key belongs on the left node
		} else {
			left->add(key, data, n, p);
		}
		// if the new key is more than the existing key, it belongs in the right node
	} else {
		// if right is empty, that's the new home!
		if (right == nullptr) {
			right = new RBTreeNode(key, data, nullptr, nullptr, this, t);
			right->AddProcess(); // after physical addition, change colors/balance out the tree
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
DRT* RBTreeNode::searchnode(string key, string n, string p) {
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
RBTreeNode* RBTreeNode::first() {
	RBTreeNode* first;
	if (left != nullptr) first = left->first();
	else return this;

	return first;
}

// recursively goes right all the way down the tree to find the last node
RBTreeNode* RBTreeNode::last() {
	RBTreeNode* last;
	if (right != nullptr) last = right->last();
	else return this;

	return last;
}

// getter for the key
string RBTreeNode::getk() { return k; }
// getter for the data
string RBTreeNode::getd() { return d; }
// getter for the right node
RBTreeNode* RBTreeNode::getright() { return right; }
// getter for the left node
RBTreeNode* RBTreeNode::getleft() { return left; }

// gets the next node in the tree, which is always the node to the right
string RBTreeNode::next() {
	RBTreeNode* next;
	if (right) next = right->first();
	else return "";

	return next->getk();
}

// gets the previous node in the tree - THIS CODE IS WRONG
string RBTreeNode::prev() {
	RBTreeNode* prev;
	if (left) prev = left->last();
	else return "";

	return prev->getk();
}

//similar to search; keeps track of nsf and psf
 //just works its down to the tree to find the node to remove
 //then calls remove ()
DRT* RBTreeNode::remove(string key, string n, string p) {
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
	}
	else {
		return left->remove(key, n, p);
	}
}

//the physical removal (decides whether it's 0, 1, or 2-child case and possibly copies key and data values and physically removes the deleted node
void RBTreeNode::remove() {
	bool isBlack = black;
	// need copy of parent and child nodes for after the 'delete this'
	RBTreeNode* p = parent;
	RBTreeNode* x;

	// if 2 children, go right one left all the way down and copy that data into the node to remove
	if (right && left) {
		RBTreeNode* next = right->first();
		k = next->getk();
		d = next->getd();

		if (right == next) right = nullptr;

		next->remove();
	} else if (right && !left) { // if one child, change the parents pointer to point to the child
		x = right;

		if (parent == nullptr) {
			t->setroot(right);
			right->setparent(nullptr);
		} else if (parent->getk() > k) parent->setleft(right);
		else parent->setright(right);

		// forgot to set the parent initially, created many bugs
		right->setparent(parent);

		// change pointers so the delete doesn't have ripple effect
		right = nullptr;
		left = nullptr;

		delete this;

		// after the physical deletion, perform necessary color changes and balancing
		if (isBlack) DelProcess(x, p);
	} else if (left && !right) { // if one child, change the parents pointer to point to the child
		x = left;

		if (parent == nullptr) {
			t->setroot(left);
			left->setparent(nullptr);
		}
		else if (parent->getk() > k) parent->setleft(left);
		else parent->setright(left);

		left->setparent(parent);

		// change pointers so the delete doesn't have ripple effect
		right = nullptr;
		left = nullptr;

		delete this;

		// after the physical deletion, perform necessary color changes and balancing
		if (isBlack) DelProcess(x, p);
	} else { // if no children, go ahead and just delete it
		x = nullptr;

		if (parent == nullptr) t->setroot(nullptr);
		else if (parent->getk() > k) parent->setleft(nullptr);
		else parent->setright(nullptr);

		// change pointers so the delete doesn't have ripple effect
		right = nullptr;
		left = nullptr;

		delete this;

		// after the physical deletion, perform necessary color changes and balancing
		if (isBlack) DelProcess(x, p);
	}
}

// setter for the parent
void RBTreeNode::setparent(RBTreeNode * p) { parent = p; }
// setter for the left
void RBTreeNode::setleft(RBTreeNode * l) { left = l; }
// setter for the right
void RBTreeNode::setright(RBTreeNode * r) { right = r; }

// getter for the parent
RBTreeNode* RBTreeNode::getparent() {
	return parent;
}

// getter for the node color
bool RBTreeNode::isblack() {
	return black;
}

// setter for the node color
void RBTreeNode::setblack(bool b) {
	black = b;
}

// gets the direct sibling of the current node as determined by the parent
RBTreeNode* RBTreeNode::getdirect() {
	if (parent->getright() == this) return right;
	else return left;
}

// determines if the node is a direct child
bool RBTreeNode::isdirect() {
	RBTreeNode* gp;
	if (parent && (gp = parent->getparent())) { // if there's a grandparent, determine the direction of lineage from there
		RBTreeNode* child;
		if ((child = gp->getright()) && child->getright() == this) return true;
		else if ((child = gp->getleft()) && child->getleft() == this) return true; // THANKS FOR THE HELP ANDY!
		else return false;
	} else { // if there is no grandparent, it's definitely a direct node
		return true;
	}
}

// performs rotations to balance out the binary tree
void RBTreeNode::rotate() {
	RBTreeNode* gp = parent->getparent();
	RBTreeNode* p = parent;
	RBTreeNode* z;

	// doing the necessary color changes
	bool tempColor = black;
	black = parent->isblack();
	parent->setblack(tempColor);

	// finding the zigzag child
	z = getsibling(this->getdirect(), this);

	// pointer change 1
	parent = gp;

	// pointer change 2
	if (!gp) t->setroot(this);
	else {
		if (gp->getright() == p) gp->setright(this);
		else gp->setleft(this);
	}

	// pointer change 3
	p->setparent(this);

	// pointer change 4 / 5
	if (p->getleft() == this) {
		right = p;
		p->setleft(z);
	} else {
		left = p;
		p->setright(z);
	}

	// pointer change 6
	if (z) z->setparent(p);
}

// performs the necessary color changes and balancing after a node is physically added
void RBTreeNode::AddProcess() {
	if (!parent) { // case 3
		black = true;
		return;
	} else if (getcolor(parent)) return; // case 4
	
	RBTreeNode* gp = parent->getparent();
	RBTreeNode* uncle = getsibling(parent, gp);
	
	if (!getcolor(uncle)) { // case 5
		parent->setblack(true);
		uncle->setblack(true);
		gp->setblack(false);
		gp->AddProcess();
	} else if (this->isdirect()) parent->rotate(); // case 6
	else for (int i = 0; i < 2; i++) this->rotate(); // case 7
}

// recursively performs a variety of checks to determine validity of tree
int RBTreeNode::ValidNode() {
	int lc, rc, r;

	if (!black && parent && !parent->isblack()) {
		r = -1;
		cout << "cannot be 2 reds in a row" << endl;
		cout << "child: " << k << ", parent: " << parent->getk() << endl;
	} else {
		if (left && left->getparent() != this) {
			r = -1;
			cout << "the left node doesn't point to the parent" << endl;
		} else {
			if (left && left->getk() >= k) {
				r = -1;
				cout << "left child should've been assigned to the right" << endl;
			} else {
				if (right && right->getparent() != this) {
					r = -1;
					cout << "the right child doesn't point to its parent" << endl;
				} else {
					if (right && right->getk() <= k) {
						r = -1;
						cout << "right child should've been assigned to the left" << endl;
					} else {
						if (left) {
							lc = left->ValidNode();
						} else {
							lc = 0;
						}
						if (lc == -1) {
							r = -1;
						} else {
							if (right) {
								rc = right->ValidNode();
							} else {
								rc = 0;
							}
							if (rc == -1) {
								r = -1;
							} else {
								if (lc != rc) {
									r = -1;
								} else {
									if (black) {
										r = lc + 1;
									} else {
										r = lc;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return r;
}


