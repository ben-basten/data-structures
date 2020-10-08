//Ben Basten
//PG2.cpp takes user input for a list and prints out the sorted result

#include <iostream>
#include <string>
#include <cstdlib>
#include "PG2.h"
#include "LLN.h"
#include "LL.h"
using namespace std;

// takes user input sorts it, and displays the result
int main(int argc, char ** argv) {
	LL* list = new LL();
	string input = "";
	do {
		//inputs strings until the user inputs an empty string
		if (input != "") list->add(input);
		cout << "Enter a string to add to the list: ";
		getline(cin, input);
	} while (input != "");

	list->radixsort();
	cout << "Sorted List: " << endl;
	list->print();

	//deallocate memory after program is run
	delete list;

	system("pause");
	return 0;
}
