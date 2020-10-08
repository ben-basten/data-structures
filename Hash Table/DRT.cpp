// Ben Basten
// DRT.cpp creates the object that the database returns from a query

#include <string>
#include "DRT.h"
using namespace std;

// constructor - the user passes in the results of their operation
DRT::DRT(string d, string n, string p) {
	data = d;
	next = n;
	prev = p;
}

// getter for the data variable
string DRT::getdata() {
	return data;
}

// getter for the next variable
string DRT::getnext() {
	return next;
}

// getter for the previous variable
string DRT::getprev() {
	return prev;
}
