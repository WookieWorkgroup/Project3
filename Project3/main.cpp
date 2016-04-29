/*********************************************

Name:			Joshua Neustrom, jwnf7b@mail.umkc.edu, 10227835
Daniel Mitchel
Chen Wang, cwrp3@mail.umkc.edu, 16208411

Course:			CS303
Program:		Project3 (Wookie Workgroup)
Team:			Team1
Due Date:		May 4, 2016
Description:	Decoder/Encoder, uses a binary search tree where * means fo left and - means go right and root has no data
Inputs:			Message
Outputs:		Decoded or encoded message

*********************************************/

#include <iostream>
#include <string> 
#include <fstream>
#include "MorseCode.h"

using namespace std;

// Functions for the menu
void displayMenu(ofstream& log_file, MorseCode& morsecode, string& result);

int main()
{
	// Initial variables for results and morse code conversions
	MorseCode morsecode;
	string result = "";

	// Open a file of morse codes
	ifstream morse;
	morse.open("morse.txt");

	// Test the file
	if (!morse.is_open())
	{
		cerr << "Log.txt did not open, bye!" << endl;
	}

	// Give me a log file
	ofstream log_file;
	log_file.open("log.txt");

	// Test the file
	if (!log_file.is_open())
	{
		cerr << "Log.txt did not open, bye!" << endl;
	}

	// Build a map for encoding
	morsecode.getMorseValues(morse);

	// Put the morse code into a binary tree for decoding
	while (morsecode.build(morse, log_file) && morse.good())
	{
		log_file << "added letter, back to main" << endl;
	}

	// All done with Mr Morse's input
	morse.close();

	// Call the menu for entering calculations
	while (true)
	{
		displayMenu(log_file, morsecode, result);
	}

	// close up files
	log_file.close();

}

void displayMenu(ofstream& log_file, MorseCode& morsecode, string& result)
{
	// Fresh and clean string for user input
	string user_input = "";

	// My choices
	int userSelection(-1);

	cout << "Please select one: \n\n";
	cout << "1:\tEnter a message to encode (letters only) \n";
	cout << "2:\tEnter a message to decode (* or - only) \n";
	cout << "3:\tDisplay Last Encode/Decode Result\n";
	cout << "4:\tClear entries\n";
	cout << "5:\tExit\n";


	// Filter input so program accepts single digits only
	while (!(cin >> userSelection))
	{
		// Make sure the input is proper
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		// Warn the user about an improper input
		cout << endl << "Single digits only" << endl;
		cout << "Make another selection: ";
	}

	// What happens when making a choice
	switch (userSelection)
	{
	
	// Give me a message to encode
	case 1:
		cout << endl << endl;
		cout << "Enter the message to encode: ";
	
		// Get the message to encode
		cin.ignore();
		getline(cin, user_input);
		log_file << "User entered " << user_input << endl;

		// See if the code is proper
		try
		{
			//Check for errors and throw codes as necessary
			//Letters are automatically converted to lowercase when encoded, so we don't need to check capitalization here
			
			// Look for symbols
			string punctuation = "!@#$%^&*()-_=+`~[]{}|\\;:'\"<>,./?";
			for (unsigned int i = 0; i < punctuation.length(); ++i)if (user_input.find(punctuation[i]) != string::npos) throw 1;

			// Look for numbers
			string numbers = "0123456789";
			for (unsigned int i = 0; i < numbers.length(); ++i)if (user_input.find(numbers[i]) != string::npos) throw 2;
			//---------------------------------------------

			// Result to display
			result = morsecode.encode(user_input);
			cout << "Message encoded: " << result << endl;
			log_file << "Message encoded: " << result << endl;
		}

		// Bad input, try again
		catch (int i)
		{
			// For the user
			std::cout << std::endl << std::endl;
			cout << "Input failed, please try again. Consult log file for more information.\n";

			// For the log
			log_file << "Error code receieved: " << i << endl;
			log_file << "Encode failed, try again!!!" << std::endl;
			log_file << "Purging previous data" << std::endl;

			// Clear any result, user input, or data to purge error
			morsecode.clear();
			result = "";
			user_input = "";
		}
		cout << endl << endl;
		break;

	// Message to decode
	case 2:
		cout << endl << endl;
		cout << "Enter the message to decode: ";
	
		// Get the input
		cin.ignore();
		getline(cin, user_input);

		log_file << "User entered " << user_input << endl;
		
		// Lets see if we can decode that for you
		try
		{
			//Check for errors and throw codes as necessary
			// Look for symbols
			string punctuation = "!@#$%^&()_=+`~[]{}|\\;:'\"<>,./?";
			for (unsigned int i = 0; i < punctuation.length(); ++i)if (user_input.find(punctuation[i]) != string::npos) throw 3;
			for (unsigned int i = 0; i < user_input.size(); i++) if (isalpha(user_input[i])) throw 4;
			
			// Look for numbers
			string numbers = "0123456789";
			for (unsigned int i = 0; i < numbers.length(); ++i)if (user_input.find(numbers[i]) != string::npos) throw 5;
			//---------------------------------------------

			// Make the translation
			result = morsecode.decode(user_input);
			cout << "Message decoded: " << result << endl;
			log_file << "Message decoded: " << result << endl;
		
		}

		// Bad input, try again
		catch (int i)
		{

			// For the user
			std::cout << std::endl << std::endl;
			cout << "Input failed, please try again. Consult log file for more information.\n";

			// For the log
			log_file << "Error code receieved: " << i << endl;
			log_file << "Encode failed, try again!!!" << std::endl;
			log_file << "Purging previous data" << std::endl;

			// Clear any result, user input, or data to purge error
			morsecode.clear();
			result = "";
			user_input = "";
		}
		cout << endl << endl;
		
		break;
	
	// Last result
	case 3:

		// A result exists
		if (result != "")
		{
			cout << endl << endl;
			cout << "Last message coded/decoded was " << result << endl;
			cout << endl << endl;
			log_file << "Last message coded/decoded was " << result << endl;
		}

		// Nothing there
		else
		{
			cout << endl << endl;
			cout << "Nothing there, try giving us a message to encode/decode " << endl;
			cout << endl << endl;
			log_file << "Nothing there, try giving us a message to encode/decode " << endl;

		}

		break;
		
	// Clear
	case 4:
	
		morsecode.clear();
		result = "";
		user_input = "";

		cout << endl << endl;
		cout << "Entries cleared\n\n";
		log_file << "Entries cleared\n\n";

		break;


	// Bah bye
	case 5:
		
		exit(0);
		log_file.close();

	// Bad choice, try that again
	default:
		
		cout << endl << endl;
		cout << "Invalid menu option" << endl;
		log_file << "Invalid menu option" << endl;
		
		break;
	}
}
