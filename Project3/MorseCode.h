#pragma once

// Class for morse code
#include <iostream>
#include <string> 
#include <fstream>
#include "Node.h"


using namespace std;

class MorseCode
{
public:
	// Constructor
	MorseCode();

	// Morse code killah
	~MorseCode();

	// Functions to clear between different user inputs
	bool isEmpty();
	void clear();
	
	// Builds the table using a file
	bool build(ifstream& morse, ofstream& log_file);
	
	// Translation functions
	string encode(string input);
	string decode(string input);

private:
	// Our variables
	string output;
	Node* root;
};




