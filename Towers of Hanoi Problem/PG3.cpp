// Ben Basten
// PG3.cpp takes user input and performs the Hanoi logic

#include <iostream>
#include <string>
#include <cstdlib>
#include "PG3.h"
using namespace std;

//creates and initializes to poles for hanoi
LLStack** InitializeStacks(int disks) {
	// 3 poles
	LLStack ** poles = new LLStack*[3];
	//each pole is an LLStack
	for (int i = 0; i < 3; i++) poles[i] = new LLStack();
	//adds numbers with the smallest number on top
	for (disks; disks > 0; disks--) poles[0]->PUSH(disks);
	return poles;
}

//moves a disk from one pole to another and displays it for the user
void MoveDisk(LLStack ** &poles, int source, int dest) {
	int toMove = poles[source]->POP();
	poles[dest]->PUSH(toMove);
	cout << "Move disk " << toMove << " from pole " << source + 1 << " to pole " << dest + 1 << "!" << endl;
}

// calculates what the only move 
int* OnlyMove(LLStack ** poles, int & oneLoc) {
	int src = -1, dest = -1;
	// pops all of the top disks so the move can be determined
	int topDisks[3];
	for (int i = 0; i < 3; i++) {
		if (!poles[i]->ISEMPTY()) topDisks[i] = poles[i]->POP();
		// if there isn't a disk on that pole, just assign that pole's top disk to -1
		else topDisks[i] = -1;
	}
	// loop through each of the disks to find where the move is
	for (int i = 0; i < 3; i++) {
		// the disk cannot be the one disk
		if (i != oneLoc) {
			// if there is no disk on a pole, that will definitely be the destination
			if (topDisks[i] == -1) dest = i;
			// if the pole isn't empty and the src hasn't been set yet, just set the source to that disk
			else if (src == -1) src = i;
			// the source isn't the largest disk, so move the source to destination and make the source the current disk
			else if (topDisks[i] < topDisks[src]) {
				dest = src;
				src = i;
			}
			// if all else fails, that disk is the destination
			else dest = i;
		}
	}
	// push the top disks back when done
	for (int i = 0; i < 3; i++) {
		if (topDisks[i] != -1) poles[i]->PUSH(topDisks[i]);
	}
	int coords[] = { src, dest };
	return coords;
}

// drives the operations for the Hanoi game
void Hanoi(int disks) {
	//creates the poles
	LLStack ** poles = InitializeStacks(disks);

	//keep track of where the 1 is at all times
	int oneLoc = 0;
	//one moves forward every time if even disks, and backwards if odd
	bool forward = (disks % 2 == 0) ? true : false;

	//it takes 2^n - 1 moves to solve Hanoi
	int totalMoves = pow(2, disks) - 1;

	for(int count = 1; count <= totalMoves; count++) {
		// move 1 disk if it is an odd move, starts on an odd move
		if (count % 2 == 1) {
			//if it is an odd move, the one always moves in the predetermined direction
			int src = oneLoc;
			if (forward) {
				oneLoc++;
				if (oneLoc > 2) oneLoc = 0;
			} else {
				oneLoc--;
				if (oneLoc < 0) oneLoc = 2;
			}
			// move the disk once the new position of the 1 is determined
			MoveDisk(poles, src, oneLoc);
		} else {
			// if it is an even move, there's only one non-1 disk move possible
			int* coords = OnlyMove(poles, oneLoc);
			// once the only move is found, make the move
			MoveDisk(poles, coords[0], coords[1]);
		}
	}

	// deallocate memory after operations are completed
	delete poles;
}

// gets user input for how many disks they want in their Hanoi game
int main(int argc, char ** argv)
{
	cout << "How many discs would you like to move? ";
	int disks;
	cin >> disks;

	Hanoi(disks);

	system("pause");

	return 0;
}