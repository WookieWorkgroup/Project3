/*********************************************

Name:			Joshua Neustrom, jwnf7b@mail.umkc.edu, 10227835
Daniel Mitchel
Chen Wang, cwrp3@mail.umkc.edu, 16208411

Course:			CS303
Program:		Project3 (Wookie Workgroup)
Team:			Team1
Due Date:		May 4, 2016
Description:	Decoder/Encoder
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
	if (!morse.is_open())
	{
		cerr << "Log.txt did not open, bye!" << endl;
	}

	// Give me a log file
	ofstream log_file;
	log_file.open("log.txt");
	if (!log_file.is_open())
	{
		cerr << "Log.txt did not open, bye!" << endl;
	}

	// Put the morse code into a binary tree
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
	string user_input = "";

	// My choices
	int userSelection(-1);
	cout << "Please select one: \n\n";
	cout << "1:\tEnter a message to encode\n";
	cout << "2:\tEnter a message to decode\n";
	cout << "3:\tDisplay Last Encode/Decode Result\n";
	cout << "4:\tClear entries\n";
	cout << "5:\tExit\n";


	// Filter input so program accepts single digits only
	while (!(cin >> userSelection))
	{
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
		cin.ignore();
		getline(cin, user_input);
		log_file << "User entered " << user_input << endl;
		// See if the polynomial is poperly entered
		try
		{
			//result = morsecode.encode(user_input);
			cout << "Message to encode successfully entered" << endl;
		}

		// Bad input, try again
		catch (const std::exception &e)
		{
			std::cout << std::endl << std::endl;

			std::cout << e.what() << std::endl << std::endl;
			log_file << e.what() << endl;
			std::cout << "Process failed, try again!!!" << std::endl;
			std::cout << "Purging previous data" << std::endl;
			std::cout << "See log.txt for details" << std::endl;
			log_file << "Encode failed, try again!!!" << std::endl;
			log_file << "Purging previous data" << std::endl;

			// Clear any result, user input, or data to purge error
			//morsecode.clear();
			result = "";
			user_input = "";
		}


		cout << endl << endl;
		break;

	// Message to decode
	case 2:
		cout << endl << endl;
		cout << "Enter the message to decode: ";
		cin.ignore();
		getline(cin, user_input);
		log_file << "User entered " << user_input << endl;
		// See if the polynomial is poperly entered
		try
		{
			//result = morsecode.decode(user_input);
			cout << "Message to decode successfully entered" << endl;
		}

		// Bad input, try again
		catch (const std::exception &e)
		{
			std::cout << std::endl << std::endl;

			std::cout << e.what() << std::endl << std::endl;
			log_file << e.what() << endl;
			std::cout << "Process failed, try again!!!" << std::endl;
			std::cout << "Purging previous data" << std::endl;
			std::cout << "See log.txt for details" << std::endl;
			log_file << "Decode failed, try again!!!" << std::endl;
			log_file << "Purging previous data" << std::endl;

			// Clear any result, user input, or data to purge error
			morsecode.clear();
			result = "";
			user_input = "";

		}


		cout << endl << endl;
		break;
	case 3:
		cout << endl << endl;
		cout << "Last message coded/decoded was " << result << endl;

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
