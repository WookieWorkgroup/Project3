#include "MorseCode.h"


// Default Constructor
MorseCode::MorseCode()
{
	root = new Node(0, nullptr, nullptr);
	output = "";
}

// Destructor
MorseCode::~MorseCode()
{
	Free_nodes(root);
}

// Build a binary tree of morse code letters using a text file (* is left and - is right) for decoding
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
				throw std::exception("Error 6: not a valid symbol");
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
			throw std::exception("Error 7: not a valid symbol");
		}

		return true;
	}

	// Make the compiler happy
	return true;
}


// Builds a morse code map for encoding
void MorseCode::getMorseValues(ifstream& morse)
{
	// Some basic variables
	char c;
	string s;

	// Go through the file and build the map one line at a time
	while (morse.good())
	{
		// Get a letter
		c = morse.get();
		
		//throw away space
		morse.get(); 

		// Get the code
		getline(morse, s);

		// Store in the map
		encodings[c] = s;
		decodings[s] = c;
	}
}

//prints tree inorder, wrapper function
void MorseCode::printTree()
{
	printTree(root);
}

// Recursive call for printing the tree inorder, for testing purposes
void MorseCode::printTree(Node* n)
{
	// Print left
	if(n->left != nullptr)printTree(n->left);
	cout << n->data << endl;

	// Print right
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

// Encode a message
string MorseCode::encode(string input)
{
	// Store results in a string stream
	stringstream ss;

	// Go through input
	for (unsigned int i = 0; i < input.size(); ++i)
	{
		// Look at encodings via map
		ss << encodings[tolower(input[i])];

		// Add space between codes for each letter
		if (i < input.size() - 1) ss << " ";
	}

	// Return the encoded string
	return ss.str();
}

// Decode
string MorseCode::decode(string input)
{
	stringstream ss;
	
	//Separate the input with spaces
	ss << input;
	string letters;

	while(ss)
	{
		string temp;
		ss >> temp;

		//Check if the temp is the end
		if (temp == "")
			break;

		//Check if the input is valid
		if (decodings.find(temp)==decodings.end())
			throw 6;

		// Store decoded output
		letters += decodings[temp];
	}	

	// Return the output
	return letters;
}

// Clears the binary tree, used by the destructor
void MorseCode::Free_nodes(Node* aroot)
{
	// Empty case
	if (aroot == NULL)
		return;

	// Otherwise recursively delete nodes through the tree
	Free_nodes(aroot->left);
	Free_nodes(aroot->right);
	
	// Delete the root and done
	delete[] aroot;
}
