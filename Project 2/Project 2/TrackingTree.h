// TrackingTree.h
// Finley McIlwaine
// COSC2030 Project 2
// 11/21/18

#pragma once
#ifndef TRACKING_TREE_H
#define TRACKING_TREE_H

#include <iostream>
#include <string>
#include "Node.h"
#include "myHash.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

class TrackingTree
{
public:
	TrackingTree();

	// Displays the entire tree structure as a set of ID values
	// with demonstration of parent children relationships
	void displayTree() const;

	// Prints a specific number of spaces to cout
	void printSpace(const int indentSize) const;

	// Displays a specific node in the tree,
	// if no node with input ID is found, a message is displayed
	void displayRecord(const string findId) const;

	// Updates a specific record in the tree and propgagates the change upward
	// if no node with input ID is found, a message is displayed
	void updateRecord(const string findId);

	// Puts a new record in the tree
	void newRecord();

	// Propagate a change up the tree
	void propagateChangeUpTree(int changedRecordIndex);

	// Propagate a change down the tree
	void propagateChangeDownTree(int changedRecordIndex);

	// Grow the tree by one level
	void grow();

	// Get user input event for new/updating node
	void getEvent(string& newEvent);

private:
	vector<Node> nodes;
	int newestRecord;
};

#endif // !TRACKING_TREE_H