#pragma once

// Class for morse code
#include <iostream>
#include <vector>
#include <map>
#include <string> 
#include <fstream>
#include <sstream>
#include <istream>
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
	void getMorseValues(ifstream& morse);

	//prints tree
	void printTree();
	void printTree(Node* n);

	// Translation functions
	string encode(string input);
	string decode(string input);

private:
	// Our variables
	map<char, string> encodings;
	map<string, char> decodings;

	//free nodes, can be used for the destructor
	void Free_nodes(Node* aroot);

	string output;
	Node* root;
};




