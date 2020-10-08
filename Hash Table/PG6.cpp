//Ben Basten
//PG6.cpp inputs commands from the user and decides what operation to execute based on the
 //command

#include <iostream>
#include <string>
#include <cstdlib>
#include "HashTable.h"
#include "DRT.h"
#include "PG6.h"
using namespace std;

// sets up database and continually takes user input
int main(int argc, char** argv) {
	Studs = new HashTable(3000);
	while (ProcessCommand());
	delete Studs;
	return 0;
}

// takes user input and decides what to do with it
bool ProcessCommand() {
	string cmd;
	getline(cin, cmd);
	if (cmd == "EXIT") return false;
	else if (cmd.substr(0, 3) == "ADD") AddCommand(cmd);
	else if (cmd.substr(0, 6) == "REMOVE") RemoveCommand(cmd);
	else if (cmd.substr(0, 6) == "LOOKUP") LookupCommand(cmd);
	else cout << "Invalid Command!" << endl;
	return true;
}

// determines what word the user wants to add and passes that into the tree
void AddCommand(string cmd) {
	// starting at the apostrophe, search for the word until it hits another apostrophe
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string word = cmd.substr(q1 + 1, q2 - q1 - 1);

	DRT* T = Studs->search(word); // logic for changing the data count is done from here
	if (T->getdata() == "")
		T = Studs->modify(word, "1");
	else {
		string d = to_string(stoi(T->getdata()) + 1);
		T = Studs->modify(word, d);
	}

	// print the result nicely
	cout << "1 copy of \"" << word << "\" has been added to the library." << endl;
	delete T;
}

// determines what word the user wants to remove and passes that into the tree
void RemoveCommand(string cmd) {
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string k = cmd.substr(q1 + 1, q2 - q1 - 1);
	DRT* T = Studs->search(k);
	if (T->getdata() == "")
		cout << "\"" << k << "\" does not exist in the library." << endl;
	else {
		if (T->getdata() == "1") {
			delete T;
			T = Studs->modify(k, ""); // only calls remove() method if that is the 'last copy' of the book in the library
		} else {
			string d = to_string(stoi(T->getdata()) - 1);
			delete T;
			T = Studs->modify(k, d);
		}
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
		cout << "\"" << word << "\" does not exist in the library." << endl;
	} else {
		// if the return contains data for the key, the key exists and should be printed out
		cout << "Name:  " << word << "     Copies:  " << T->getdata() << endl;
	}
}