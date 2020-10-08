//Ben Basten
//PG4.cpp inputs commands from the user and decides what operation to execute based on the
 //command

#include <iostream>
#include <string>
#include <cstdlib>
#include "Tree.h"
#include "DRT.h"
#include "PG4.h"
using namespace std;

// entry point for the program - user continually enters commands until the EXIT command
int main(int argc, char** argv) {

	Studs = new Tree();
	while (ProcessCommand());
	delete Studs;
	return 0;
}

// takes user input and determines what command the user wants to run
bool ProcessCommand() {

	string cmd;
	getline(cin, cmd);
	if (cmd == "EXIT") return false;
	if (cmd == "PRINT") Print();
	else if (cmd == "RPRINT") RPrint();
	else if (cmd.substr(0, 3) == "ADD") AddCommand(cmd);
	else if (cmd.substr(0, 6) == "REMOVE") RemoveCommand(cmd);
	else if (cmd.substr(0, 6) == "LOOKUP") LookupCommand(cmd);
	else cout << "Invalid Command!" << endl;
	return true;
}

// prints out the list in alphabetical order
void Print() {

	cout << "Printing list forwards:" << endl;
	// searching an empty string returns the first and last elements in the binary tree
	DRT* T = Studs->search("");
	string k = T->getnext();
	while (k != "") {
		delete T;
		// starting at the first element, go element by element and print out the records
		T = Studs->search(k);
		cout << "Name:  " << k << "\tCopies:  " << T->getdata() << endl;
		k = T->getnext();
	}
	delete T;
	cout << endl;
}

// prints out the list in reverse alphabetical order
void RPrint() {

	cout << "Printing list backwards:" << endl;
	// searching an empty string returns the first and last elements in the binary tree
	DRT* T = Studs->search("");
	string k = T->getprev();
	while (k != "") {
		delete T;
		// starting at the last element, go element by element and print out the records
		T = Studs->search(k);
		cout << "Name:  " << k << "\tCopies:  " << T->getdata() << endl;
		k = T->getprev();
	}
	delete T;
	cout << endl;
}

// determines what word the user wants to add and passes that into the tree
void AddCommand(string cmd) {
	// starting at the apostrophe, search for the word until it hits another apostrophe
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string word = cmd.substr(q1 + 1, q2 - q1 - 1);

	// if the modify method is passed a key and data, it knows to add it to the database
	DRT* T = Studs->modify(word, "1");
	// print the result nicely
	cout << "1 copy of \"" << word << "\" has been added to the library." << endl;
	delete T;
}

// determines what word the user wants to remove and passes that into the tree
void RemoveCommand(string cmd) {
	// starting at the apostrophe, search for the word until it hits another apostrophe
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string k = cmd.substr(q1 + 1, q2 - q1 - 1);

	// searches to see if the word exists in the database before deleting it
	DRT * T = Studs->search(k);
	if (T->getdata() == "")
		// if nothing is found, no removal necessary
		cout << "\"" << k << "\" does not exist in the library." << endl;
	else {
		/*if (T->getdata() == "1") {
			delete T;
			T = Studs->modify(k, "");
		} else {
			string d = to_string(stoi(T->getdata()) - 1);
			delete T;
			T = Studs->modify(k, "");
		}*/
		
		// if a record is found, pass a key with empty data so the modify method knows to delete
		delete T;
		T = Studs->modify(k, "");

		cout << "1 copy of \"" << k << "\" has been removed from the library." << endl;
		delete T;
	}
}

// determines what the user wants to look up and sends that to the tree
void LookupCommand(string cmd) {
	// starting at the apostrophe, search for the word until it hits another apostrophe
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string word = cmd.substr(q1 + 1, q2 - q1 - 1);

	// search for the word to get a database return
	DRT* T = Studs->search(word);
	if (T->getdata() == "") { // if the return doesn't contain data for the key, the key doesn't exist in the list
		// if the previous value in the return is empty, that means the element would be the first in the list
		string prev = (T->getprev() == "") ? "the beginning of the list" : T->getprev();
		// if the next value in the return is empty, that means the element would be the last in the list
		string next = (T->getnext() == "") ? "the end of the list" : T->getnext();
		cout << "\"" << word << "\" does not exist." << endl;
		cout << "\"" << word << "\" would fall between " << prev << " and " << next << endl;
	} else {
		// if the return contains data for the key, the key exists and should be printed out
		cout << "Name:  " << word << "     Copies:  " << T->getdata() << endl;
	}
}

