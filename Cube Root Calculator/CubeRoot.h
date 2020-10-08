//Ben Basten
//CubeRoot.h contains the method structure for finding the cube root

#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

//Prompts the user to input a number and precision and outputs the cube root result
int main(int argc, char** argv);
//Adds user-determined amount of zeroes to the end of the inputted number to increase the precision of the cube root
string add_places(string number, int input);
//Takes 2 integers in the form of strings (assuming that they contain characters 0-9) and compares their values
int compare(string a, string b);
//Calculates the result of the 'magic formula' using the 'ans' value that is passed in
string magic_formula(string ans);
//takes user input for desired cube root number and precision, calculates the cube root, and returns the result
string cube_root(string number, int places);