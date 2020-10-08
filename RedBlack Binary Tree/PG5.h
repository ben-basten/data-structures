// Ben Basten
// PG4.h contains the structure for taking user input and deciding what to do with it

#ifndef _PG5_
#define _PG5_

#include <string>
#include <cstdlib>
#include "Database.h"
using namespace std;

Database* Studs;

int main(int argc, char** argv); // entry point for the program - user continually enters commands until the EXIT command
bool ProcessCommand(); // takes user input and determines what command the user wants to run
void Print(); // prints out the list in alphabetical order
void RPrint(); // prints out the list in reverse alphabetical order
void AddCommand(string cmd); // determines what word the user wants to add and passes that into the tree
void RemoveCommand(string cmd); // determines what word the user wants to remove and passes that into the tree
void LookupCommand(string cmd); // determines what the user wants to look up and sends that to the tree

#endif
