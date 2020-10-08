// Ben Basten
// RBHelper.cpp performs a variety of essential functions that don't need to be tied to a class

#include "RBHelper.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "RBTreeNode.h"
using namespace std;

// gets the color of the node and handles the null case
bool getcolor(RBTreeNode* n) {
	if (n == nullptr) return true;
	else return n->isblack();
}

// uses the parent to find the sibling of the given node
RBTreeNode* getsibling(RBTreeNode* n, RBTreeNode* p) {
	if (p->getright() == n) return p->getleft();
	else return p->getright();
}

// performs necessary color changes and balancing after physical deletion of a node
void DelProcess(RBTreeNode* x, RBTreeNode* p) {
	if (!getcolor(x)) { // case 4
		x->setblack(true);
		return;
	} else if (!p) return; // case 5
	
	RBTreeNode* w = getsibling(x, p);

	if (!getcolor(w)) { // case 7
		w->rotate();
		DelProcess(x, p);
	} else if (getcolor(w->getright()) && getcolor(w->getleft())) { // case 8
		w->setblack(false);
		x = p;
		p = p->getparent();
		DelProcess(x, p);
	} else if (!getcolor(w->getdirect())) { // case 9
		w->getdirect()->setblack(true);
		w->rotate();
	} else { // case 10
		RBTreeNode* direct = w->getdirect();
		RBTreeNode* zig = getsibling(direct, w);
		for (int i = 0; i < 2; i++) zig->rotate();
		w->setblack(true);
	}
}
