// Node.cpp
// Finley McIlwaine
// COSC2030 Project 2
// 11/21/18

#include "pch.h"
#include "Node.h"

// Default constructor
Node::Node() {}

// Constructor with input for unitialized node members
Node::Node(string notFilled) {
	id = notFilled;
	parentId = notFilled;
}

void Node::showNode() const {
	// Display the contents of a node
	cout << "\n";
	cout << "  Parent ID:              " + parentId + "\n";
	cout << "  ID:                     " + id + "\n";
	// Format the raw event for better reading
	cout << "  Raw Event:              ";
	int letterCount = 0;
	for (char letter : rawEvent) {
		if (letterCount > 25 && letter == ' ') {
			cout << "\n";
			cout << "                          ";
			letterCount = 0;
		}
		else {
			cout << letter;
		}
		letterCount++;
	}
	cout << "\n";

	cout << "  Left Child Hash:        " << leftHash << "\n";
	cout << "  Right Child Hash:       " << rightHash << "\n";
	// Format the hash histories for better reading
	cout << "  Left Child History:     { ";
	for (int i = 0; i < leftHistory.size() - 1 && leftHistory.size() != 0; i++) {
		cout << leftHistory[i] + ",\n";
		cout << "                            ";
	}
	if (leftHistory.size() != 0) {
		cout << leftHistory.back();
	}
	cout << " }\n";
	cout << "  Right Child History:    { ";
	for (int i = 0; i < rightHistory.size() - 1 && rightHistory.size() != 0; i++) {
		cout << rightHistory[i] + ",\n";
		cout << "                            ";
	}
	if (rightHistory.size() != 0) {
		cout << rightHistory.back();
	}
	cout << " }\n";
	cout << endl;
}

void Node::setParentId(const string& pId) {
	parentId = pId;
}

void Node::setId(const string& nodeId) {
	id = nodeId;
}

void Node::setEvent(const string& textEvent) {
	rawEvent = textEvent;
}

void Node::setLeftHash(const string& leftChildHash) {
	leftHash = leftChildHash;
	leftHistory.push_back(leftChildHash);
}

void Node::setRightHash(const string& rightChildHash) {
	rightHash = rightChildHash;
	rightHistory.push_back(rightChildHash);
}

string Node::getId() const { return id; }

string Node::getParentId() const { return parentId; }

string Node::getRawEvent() const { return rawEvent; }

string Node::getRightHash() const { return rightHash; }

string Node::getLeftHash() const { return leftHash; }

vector<string> Node::getRightHistory() { return rightHistory; }

vector<string> Node::getLeftHistory() { return leftHistory; }