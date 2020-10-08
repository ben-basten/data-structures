//Ben Basten
//CubeRoot.cpp contains the main method and does the majority of the operations to calculate the cube root

#include <iostream>
#include <string>
#include <cstdlib>

#include "CubeRoot.h"
#include "StringArithmetic.h"

using namespace std;

//Prompts the user to input a number and precision and outputs the cube root result
int main(int argc, char** argv) {
	string cube;
	int places;
	
	cout << "Please enter an integer:  ";
	getline(cin, cube);

	cout << "How many places would you like?  ";
	cin >> places;

	cout << "The cube root of " << cube << " to " << places << " places is:" << endl << cube_root(cube, places) << endl;
	
	cout << "\n";
	system("pause");
}

//Adds user-determined amount of zeroes to the end of the inputted number to increase the precision of the cube root
string add_places(string number, int input) { 
	// adds 3 * [user input places] to the number to increase result precision
	int places = input * 3;
	for (int x = 0; x < places; x++) {
		number += "0";
	}
	return number;
}

//Takes 2 integers in the form of strings (assuming that they contain characters 0-9) and compares their values
int compare(string a, string b) {
	//0: a=b
	//1: a>b
	//2: a<b
	removeleadingzeroes(a);
	removeleadingzeroes(b);
	// if the length of a is greater, it is the larger number
	if (a.length() > b.length()) {
		return 1;
	}
	// if the length of b is greater, it is the larger number
	else if (b.length() > a.length()) {
		return 2;
	}
	// if they are the same length, compare digit by digit to see which one is larger
	else {
		for (int i = 0; i < a.length(); ++i) {
			if ((a[i] - '0') > (b[i] - '0')) {
				return 1;
			} else if ((a[i] - '0') < (b[i] - '0')) {
				return 2;
			}
		}
		return 0;
	}
}

//Calculates the result of the 'magic formula' using the 'ans' value that is passed in
string magic_formula(string ans) {
	// formula = 12 * ans^2 + 6 * ans + 1
	return add(add(mult("12", mult(ans, ans)), mult("6", ans)), "1");
}

//takes user input for desired cube root number and precision, calculates the cube root, and returns the result
string cube_root(string number, int places) {
	removeleadingzeroes(number);

	// if the user enters 0, add the desired decimal precision and return the result
	if (number == "0") {
		//no need for a decimal if the precision desired is 0
		if (places == 0) {
			return number;
		} else {
			number += ".";
			for (int i = 0; i < places; i++) {
				number += "0";
			}
			return number;
		}
	}

	//adds extra places to the inputted number to increase decimal precision
	number = add_places(number, places);

	string * eights = new string[number.length() * 3];
	string ans = "0";
	string rem = number;

	//creates the eight product array
	string eight = "1";
	int index = -1;
	//add another eight product to the array while the product is <= the number
	while (compare(number, eight) == 1 || compare(number,eight) == 0) {
		index++;
		eights[index] = eight;
		eight = mult(eight, "8");
	}

	// perform the operation for each product in the eight product array
	string eightProduct;
	for (index; index >= 0; index--) {
		eightProduct = mult(eights[index], magic_formula(ans));
		//eight product is less than or equal to remainder
		if (compare(eightProduct, rem) == 2 || compare(eightProduct, rem) == 0) {
			rem = sub(rem, eightProduct);
			// double ans and add 1
			ans = add(mult(ans, "2"), "1");
		}
		//eight product is greater than remainder
		else {
			//double ans
			ans = mult(ans, "2");
		}
	}

	//add the decimal into the answer
	if(places != 0) ans.insert(ans.length() - places, ".");

	return ans;
} 