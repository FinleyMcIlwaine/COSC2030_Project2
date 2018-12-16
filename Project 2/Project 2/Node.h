// Node.h
// Finley McIlwaine
// COSC2030 Project 2
// 11/21/18

#pragma once
#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>
#include <iostream>
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Node
{
public:
	// Constructors
	Node();
	Node(string notFilled);

	// Display node contents
	void showNode() const;

	// Setter functions
	void setParentId(const string& pId);
	void setId(const string& nodeId);
	void setEvent(const string& textEvent);
	void setLeftHash(const string& leftChildHash);
	void setRightHash(const string& rightChildHash);

	// Getter functions
	string getId() const;
	string getParentId() const;
	string getRawEvent() const;
	string getRightHash() const;
	string getLeftHash() const;
	vector<string> getRightHistory();
	vector<string> getLeftHistory();

private:
	string id;
	string parentId;
	string rawEvent;
	string rightHash;
	string leftHash;
	vector<string> rightHistory;
	vector<string> leftHistory;
};

#endif // !NODE_H
