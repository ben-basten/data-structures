//Ben Basten
//StringArithmetic.h provides the method structure for the supplemental math methods

#ifndef _STRINGARITHMETIC_
#define _STRINGARITHMETIC_

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

//removes any leading zeroes from a string
void removeleadingzeroes(string& a);
//adds 2 string numbers (assuming they only contain characters "0-9")
string add(string a, string b);
//subtracts 2 string numbers (assuming they only contain characters "0-9")
string sub(string a, string b);
//multiplies 2 string numbers (assuming they only contain characters "0-9")
string mult(string a, string b);
#endif
