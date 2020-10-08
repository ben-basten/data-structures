// Ben Basten
// PG6.h contains the structure for taking user commands and deciding what to do with them

#ifndef _PG6_
#define _PG6_

#include <string>
#include <cstdlib>
#include "Database.h"
using namespace std;

Database* Studs;

int main(int argc, char** argv);
bool ProcessCommand();
void AddCommand(string cmd);
void RemoveCommand(string cmd);
void LookupCommand(string cmd);

#endif