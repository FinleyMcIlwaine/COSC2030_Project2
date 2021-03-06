// Project 2.cpp
// Finley McIlwaine
// COC2030 Project 2
// 11/21/18

#include "pch.h"
#include <iostream>
#include "TrackingTree.h"
#include "Node.h"
#include "myHash.h"

using std::cout;
using std::cin;
using std::endl;

void initScreen();
void inputError();
void getInput(string& req);
void getId(string& id);

int main()
{
	// initialize tree and root node
	TrackingTree tree;

	initScreen();

	string req;
	string id;
	string newEvent;

	// Main program loop
	while (true) {
		// Process input
		getInput(req);

		// Route request to appropriate action
		if (req == "da") {
			tree.displayTree();
		}
		else if (req == "dn") {
			getId(id);
			if (id == "R" || id == "r") {
				req = "";
				id = "";
				continue;
			}
			tree.displayRecord(id);
		}
		else if (req == "un") {
			getId(id);
			if (id == "R" || id == "r") {
				req = "";
				id = "";
				newEvent = "";
				continue;
			}
			tree.updateRecord(id);
		}
		else if (req == "nn") {
			tree.newRecord();
		}
		else if (req == "h") {
			initScreen();
		}
		else if (req == "e" || req == "E") {
			break;
		}
	}
}

// Displays instruction prompt
void initScreen() {
	cout << " ___________________________________________________________ \n";
	cout << "|~+~+~+~+~+~    EVENT TRACKING TREE TERMINAL     ~+~+~+~+~+~|\n";
	cout << "|                                                           |\n";
	cout << "|                       *INSTRUCTIONS*                      |\n";
	cout << "|                                                           |\n";
	cout << "| To display the entire                                     |\n";
	cout << "| tree:                       Enter 'DA' or 'da'            |\n";
	cout << "|                                                           |\n";
	cout << "| To display a node's                                       |\n";
	cout << "| contents:                   Enter 'DN' or 'dn'.           |\n";
	cout << "|                                                           |\n";
	cout << "| To update an existing                                     |\n";
	cout << "| node:                       Enter 'UN' or 'un'.           |\n";
	cout << "|                                                           |\n";
	cout << "| To add a new node:          Enter 'NN' or 'nn'.           |\n";
	cout << "|                                                           |\n";
	cout << "| To display instructions:    Enter 'H' or 'h'.             |\n";
	cout << "|                                                           |\n";
	cout << "| To exit the application:    Enter 'E' or 'e'.             |\n";
	cout << "|___________________________________________________________|\n" << endl;
}

// Gets and processes user input, throwing safe errors if necessary
void getInput(string& req) {
	// Reset input variables
	req = "";

	// Input prompt
	cout << "  INPUT: ";

	// Handle exceptions
	try
	{
		cin >> req;

		// Check for recognized input strings
		if (req == "DA" || req == "da") { req = "da"; }
		else if (req == "DN" || req == "dn") { req = "dn"; }
		else if (req == "NN" || req == "nn") { req = "nn"; }
		else if (req == "UN" || req == "un") { req = "un"; }
		else if (req == "H" || req == "h") { initScreen(); getInput(req); }
		else if (req == "E" || req == "e") { req == "e"; }
		else {
			inputError();
			getInput(req);
		}
	}
	catch (...)
	{
		// Exception thrown, display error message
		inputError();
		// Reprompt for input
		getInput(req);
	}
}

// Ignores following input, clears input state,
// and displays error message.
void inputError() {
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.clear();
	cout << "                 **** ERROR: INVALID INPUT ****              " << endl;
	cout << "                  Input 'H' or 'Help' for help.              \n" << endl;
}

// Gets and processes the input ID
void getId(string& id) {
	while (true) {
		cout << "  Enter the desired node's ID ('R' to return to menu): ";
		cin >> id;
		if (id == "R" || id == "r") {
			cout << endl;
			return;
		}
		else if (id.size() == 8) {
			return;
		}
		else {
			cout << "                 **** ERROR: INVALID ID ****              " << endl;
		}
	}
	
}