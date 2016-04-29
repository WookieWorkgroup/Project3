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
	
	// Builds the tree for decoding
	bool build(ifstream& morse, ofstream& log_file);

	// Builds the map for encoding
	void getMorseValues(ifstream& morse);

	// Prints tree for testing 
	void printTree(); // Wrapper
	void printTree(Node* n); // Recursive function

	// Translation functions
	string encode(string input);
	string decode(string input);

private:

	// Our map for decoding
	map<char, string> encodings;
	map<string, char> decodings;

	//free nodes, can be used for the destructor
	void Free_nodes(Node* aroot);

	// Output of transalated message
	string output;

	// Root of the tree for decoding
	Node* root;
};




