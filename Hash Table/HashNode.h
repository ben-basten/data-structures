// Ben Basten
// HashNode.h contains the structure for the individual nodes of data

#ifndef _HASHNODE_
#define _HASHNODE_

#include <iostream>
#include <string>
#include <cstdlib>
#include "DRT.h"
using namespace std;

class DRT;
class HashNode {
private:
    string k; string d;
    HashNode* next;
public:
    HashNode(string key, string data);
    ~HashNode(); //destructor
    DRT* searchnode(string key);
    DRT* addnode(string key, string data);
    string getk();
    string getd();
    DRT* remove(string key, HashNode* p, HashNode*& listhead);
    void setnext(HashNode* p);
};

#endif