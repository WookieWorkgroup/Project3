struct Node
{
	// Data Fields
	char data;
	Node* left;
	Node* right;

	// Constructor
	Node(const char the_data,
		Node* left_val = nullptr,
		Node* right_val = nullptr) :
		data(the_data), left(left_val), right(right_val) {}

	Node()
	{
		data = 0;
		Node *left = nullptr;
		Node *right = nullptr;
	}

	//Destructor
	virtual ~Node() {}

};