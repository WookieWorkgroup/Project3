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
		Node* temp_node = new Node(letter, nullptr, nullptr);
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

		// What in the world was that symbol
		else
		{
			throw std::exception("Error 1: not a valid symbol");
		}

		return true;
	}

	// Make the compiler happy
	return true;
}

void MorseCode::getMorseValues(ifstream& morse)
{
	char c;
	string s;
	while (morse.good())
	{
		c = morse.get();
		morse.get(); //throw away space
		getline(morse, s);
		encodings[c] = s;
	}
}

//prints tree inorder
void MorseCode::printTree()
{
	printTree(root);
}

//prints tree inorder
void MorseCode::printTree(Node* n)
{
	if(n->left != nullptr)printTree(n->left);
	cout << n->data << endl;
	if (n->right != nullptr)printTree(n->right);
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

string MorseCode::encode(string input)
{
	stringstream ss;
	for (int i = 0; i < input.size(); ++i)
	{
		ss << encodings[input[i]];
		if (i < input.size() - 1) ss << " ";
	}
	return ss.str();
}
