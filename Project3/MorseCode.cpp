#include "MorseCode.h"


// Default Constructor
MorseCode::MorseCode()
{
	root = new Node(0, nullptr, nullptr);

	output = "";

}

// Killah
MorseCode::~MorseCode()
{

}

// Build a binary tree of morse code letters using a text file (* is left and - is right)
bool MorseCode::build(ifstream& morse, ofstream& log_file)
{
	// Starter variables to read in data
	string in = "";
	Node *curr = root;
	char letter = ' ';

	// Get me a letter
	if (morse >> in)
	{
		letter = in[0];
	}

	// That did not work
	else
		return false;

	// Find a place for the node
	if (morse >> in)
	{
		// Traverse tree based on symbols
		for (int i = 0; i < in.length(); i++)
		{
			// Go left
			if (in[i] == '*')
			{
				curr->left;
			}

			// Go right
			else if (in[i] == '-')
			{
				curr->left;
			}

			// That was not a valid symbol
			else
			{
				throw std::exception("Error 1: not a valid symbol");
			}
				

		}

		// Give the letter a new home
		Node* temp_node = new Node(letter, nullptr, nullptr);
		temp_node = curr;
		log_file << "added " << letter << endl;

		return true;
	}

	
	

	return true;
}

