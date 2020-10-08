// Ben Basten
// PG4.h contains the structure for taking user input and deciding what to do with it

#ifndef _PG4_
#define _PG4_

#include <string>
#include <cstdlib>
#include "Database.h"
using namespace std;

Database* Studs;

int main(int argc, char** argv);
bool ProcessCommand();
void Print();
void RPrint();
void AddCommand(string cmd);
void RemoveCommand(string cmd);
void LookupCommand(string cmd);

#endif
