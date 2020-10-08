//Ben Basten
//StringArithmetic.cpp provides supplemental math operations that are needed to find the cube root

#include <iostream>
#include <string>
#include <cstdlib>
#include "StringArithmetic.h"
using namespace std;

//removes any leading zeroes from a string
void removeleadingzeroes(string &a) {

	while (a.length() > 1 && a[0] == '0') a = a.substr(1);
}

//adds 2 string numbers (assuming they only contain characters "0-9")
string add(string a, string b) {

	removeleadingzeroes(a);
	removeleadingzeroes(b);
	while (a.length() < b.length()) a = "0" + a;
	while (b.length() < a.length()) b = "0" + b;
	a = "0" + a;
	b = "0" + b;
	string sum = "";
	int carry = 0;
	for (int i = a.length() - 1; i >= 0; i--) {
		int s = (a[i] - '0') + (b[i] - '0') + carry;
		carry = s / 10;
		sum = (char)(s % 10 + '0') + sum;
	}
	removeleadingzeroes(sum);
	return sum;
}

//subtracts 2 string numbers (assuming they only contain characters "0-9")
string sub(string a, string b) {
	removeleadingzeroes(a);
	removeleadingzeroes(b);
	while (b.length() < a.length()) b = "0" + b;
	for (int i = 0; i < b.length(); i++)
		b[i] = 9 - (b[i] - '0') + '0';
	string diff = add(add(a, b), "1");
	diff = diff.substr(1);
	removeleadingzeroes(diff);
	return diff;
}

//multiplies 2 string numbers (assuming they only contain characters "0-9")
string mult(string a, string b) {

	removeleadingzeroes(a);
	removeleadingzeroes(b);
	string sum = "0";
	for (int i = 0; i < a.length(); i++)
		for (int j = 0; j < b.length(); j++) {
			string prod = to_string((a[i] - '0') * (b[j] - '0'));
			for (int k = 0; k < a.length() - i - 1 + b.length() - j - 1; k++)
				prod += "0";
			sum = add(sum, prod);
		}
	return sum;
}
