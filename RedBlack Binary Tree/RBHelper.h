// Ben Basten
// RBHelper.h contains the structure for all of the classless helper methods

#ifndef _RBHELPER_
#define _RBHELPER_

#include <iostream>
#include <string>
#include <cstdlib>
#include "RBTreeNode.h"
using namespace std;

bool getcolor(RBTreeNode* n); // gets the color of the node and handles the null case
RBTreeNode* getsibling(RBTreeNode* n, RBTreeNode* p); // uses the parent to find the sibling of the given node
void DelProcess(RBTreeNode* x, RBTreeNode* p); // performs necessary color changes and balancing after physical deletion of a node

#endif
