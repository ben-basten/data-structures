// Ben Basten
// HashTable.cpp performs the hashing algorithm and holds the data of the database

#include <iostream>
#include <string>
#include <cstdlib>
#include "HashTable.h"
#include "DRT.h"
#include "HashNode.h"
using namespace std;

// constructor
HashTable::HashTable(int sz) {

    HS = sz;
    table = new HashNode * [HS];
    for (int i = 0; i < HS; i++)
        table[i] = NULL;
}

//destructor
HashTable::~HashTable() {

    for (int i = 0; i < HS; i++)
        delete table[i];
    delete[] table;
}

//determines the (almost) unique hash code
int HashTable::hf(string key) {

    int val = 0;
    for (int i = 0; i < key.length(); i++) {
        int ch = key[i];
        if (ch == 0) ch = 256;
        val = (val * 256 + ch) % HS;
    }
    return val;
}

// adds a new node to the hash table
DRT* HashTable::add(string key, string data) { //very similar to sample code
    int hash = hf(key);
    if (!table[hash]) table[hash] = new HashNode(key, data); // if there's nothing in that array spot, create new Node
    else table[hash]->addnode(key, data); // if something already exists in that spot, let the node handle the work

    return new DRT(data, "", "");
}

// finds a node in the hash table
DRT* HashTable::searchnode(string key) { //searches the tree for the given key

    int val = hf(key);
    if (!table[val]) return new DRT("", "", ""); // if nothing in that array element, the key doesn't exist
    return table[val]->searchnode(key); // if something in the array element, call on the node to do the search
}


DRT* HashTable::remove(string key) { //removes an item from the list
    int hash = hf(key);
    if (!table[hash]) return new DRT("", "", "");
    return table[hash]->remove(key, nullptr, table[hash]); // HashNode drives the removal
}

DRT* HashTable::search(string key) { //Database search method
      //checks to see if we're searching on the empty string, if so builds a DRT with first() and last (), otherwise calls searchnode

    if (key == "") return new DRT("", "", "");
    return searchnode(key);
}


DRT* HashTable::modify(string key, string data) { //Database modify method

    if (key == "") return new DRT("", "", "");
    if (data == "") return remove(key);
    return add(key, data);
}