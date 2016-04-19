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
		// Traverse tree based on symbols stopping one before the end
		for (unsigned int i = 0; i < (in.length() - 1); i++)
		{
			// Go left
			if (in[i] == '*')
			{
				curr = curr->left;
			}

			// Go right
			else if (in[i] == '-')
			{
				curr = curr->right;
			}

			// That was not a valid symbol
			else
			{
				throw std::exception("Error 1: not a valid symbol");
			}


		}


		// Give the letter a new home
		Node* temp_node = new Node;
		temp_node->data = letter;
		log_file << "added " << letter << endl;

		// Set the pointers to the new node
		if (in[in.length() - 1] == '*')
		{
			curr->left = temp_node;
		}
		else if (in[in.length() - 1] == '-')
		{
			curr->right = temp_node;
		}

		else
		{
			throw std::exception("Error 1: not a valid symbol");
		}

		return true;
	}

	
	

	return true;
}

// See if we have a Morse Code Tree
bool MorseCode::isEmpty()
{
	// Does the root have no childeren
	if (root->left == nullptr && root->right == nullptr)
		return true;

	// Something still there
	return false;
}

// Clear the primitive variables
void MorseCode::clear()
{
	// Clear output
	output == "";

	return;
}

