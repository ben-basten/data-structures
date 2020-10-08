//Ben Basten
//PG3.h contains the method structure for the main method.

#ifndef _PG2_
#define _PG2_

#include <iostream>
#include <string>
#include <cstdlib>
#include "PG3.h"
#include "LLStack.h"
using namespace std;

// abstract method for the stack initialization
LLStack** InitializeStacks(int discs);

// abstract method for moving the disks
void MoveDisk(LLStack ** &poles, int source, int dest);

// abstract method for finding the only move
int* OnlyMove(LLStack ** poles, int & oneLoc);

// abstract method for the Hanoi game operations
void Hanoi(int discs);

// abstract method for the main that takes user input
int main(int argc, char ** argv);

#endif