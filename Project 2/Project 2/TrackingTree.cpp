// TrackingTree.cpp
// Finley McIlwaine
// COSC2030 Project 2
// 11/21/18

#include "pch.h"
#include "TrackingTree.h"

// Default constructor
TrackingTree::TrackingTree() {
	nodes.push_back(Node());    // fill 0th element for easier indexing
	nodes.push_back(Node("-")); // root node
	nodes[1].setParentId(myHash({ "***RANDOM_ROOT_PARENT_ID***" }));
	newestRecord = 0;
}

void TrackingTree::displayTree() const {
	cout << endl;
	// Supplementary spacing and height variables
	int maxLevel = log2(newestRecord);
	int indent = 8;
	int nodeSpace = 2;
	int nodeSpaceChange = 10;
	int indentChange = 5;

	// Calculate the initial indentation and
	// node spacing based on height
	for (int i = 1; i < maxLevel + 1; i++) {
		indent += indentChange;
		indentChange *= 2;
		nodeSpace += nodeSpaceChange;
		nodeSpaceChange *= 2;
	}
	nodeSpaceChange /= 2;
	indentChange /= 2;

	int currentNode = 1;
	int currentLevel = 0;

	// Outer loop for iterating over levels
	for (int i = 0; i < maxLevel + 1; i++) {
		printSpace(indent);
		// Inner loop for iterating over nodes
		for (int j = 1; j <= pow(2, currentLevel); j++) {
			cout << nodes[currentNode].getId();
			if (j + 1 <= pow(2, currentLevel)) {
				printSpace(nodeSpace);
			}
			currentNode++;
		}
		// Decrement spacing
		cout << "\n";
		nodeSpace -= nodeSpaceChange;
		nodeSpaceChange /= 2;
		indent -= indentChange;
		indentChange /= 2;
		currentLevel++;
	}
	cout << endl;
}

void TrackingTree::printSpace(const int indentSize) const {
	for (int i = indentSize; i > 0; i--) {
		cout << " ";
	}
}

void TrackingTree::displayRecord(const string findId) const {
	// Find the node with the requested ID
	int displayNodeIndex = 0;
	do
	{
		displayNodeIndex++;
		// Check if no node found
		if (displayNodeIndex > newestRecord) {
			cout << "  A node with ID = " << findId << " could not be found.\n" << endl;
			return;
		}
	} while (nodes[displayNodeIndex].getId() != findId);

	// Node found, call node member display
	nodes[displayNodeIndex].showNode();
}

void TrackingTree::updateRecord(const string findId) {
	// Find the node with the requested ID
	int changeNodeIndex = 0;
	do
	{
		changeNodeIndex++;
		// Check if no node found
		if (changeNodeIndex > newestRecord) {
			cout << "  A node with ID = " << findId << " could not be found.\n" << endl;
			return;
		}
	} while (nodes[changeNodeIndex].getId() != findId);

	// Node found, get new event
	string newEvent;
	getEvent(newEvent);

	// Change the node's event and ID
	nodes[changeNodeIndex].setEvent(newEvent);
	nodes[changeNodeIndex].setId(myHash({ nodes[newestRecord].getParentId(),newEvent }));

	// Propagate the change down the tree, then up
	propagateChangeDownTree(changeNodeIndex);
	propagateChangeUpTree(changeNodeIndex);
}

void TrackingTree::newRecord() {
	newestRecord++;
	// Grow tree by one level if necessarry
	if (newestRecord > 1 && (floor(log2(newestRecord)) == ceil(log2(newestRecord)))) {
		grow();
	}
	// Set new node parent ID if new node is not root
	if (newestRecord > 1) {
		nodes[newestRecord].setParentId(nodes[(newestRecord) / 2].getId());
	}

	// Get the new node's event
	string newEvent;
	getEvent(newEvent);

	// Change the new node's event and ID
	nodes[newestRecord].setEvent(newEvent);
	nodes[newestRecord].setId(myHash({ nodes[newestRecord].getParentId(),newEvent }));

	// Propagate the change up the tree
	propagateChangeUpTree(newestRecord);
}

void TrackingTree::propagateChangeUpTree(int changedRecordIndex) {
	// Calculate parent index
	int parentIndex = changedRecordIndex / 2;
	if (parentIndex == 0) {
		return;
	}
	// Which child was changed
	bool leftChildChanged = (changedRecordIndex % 2 == 0);
	// Vector of strings for hash function input
	vector<string>hashVec = { nodes[changedRecordIndex].getParentId(),
							  nodes[changedRecordIndex].getId(),
							  nodes[changedRecordIndex].getRawEvent(),
							  nodes[changedRecordIndex].getLeftHash(),
							  nodes[changedRecordIndex].getRightHash() };
	// Change the appropriate parent hash
	if (leftChildChanged) {
		nodes[parentIndex].setLeftHash(myHash(hashVec));
	}
	else {
		nodes[parentIndex].setRightHash(myHash(hashVec));
	}
	// Recursively call this function for parent index
	propagateChangeUpTree(parentIndex);
}

void TrackingTree::propagateChangeDownTree(int changedRecordIndex) {
	// Base case: the changed record is a leaf, return
	if (changedRecordIndex * 2 > newestRecord) { return; }
	// Recursive case: changed record has one child
	else if (changedRecordIndex * 2 + 1 > newestRecord) {
		// Change the child's ID based on the changed record's new ID
		nodes[changedRecordIndex * 2].setId(myHash({ nodes[changedRecordIndex].getId(),
													 nodes[changedRecordIndex * 2].getRawEvent() }));
		// Change the child's parent ID to the changed record's ID
		nodes[changedRecordIndex * 2].setParentId(nodes[changedRecordIndex].getId());
		// Vector of hash function input strings
		vector<string>hashVec = { nodes[changedRecordIndex * 2].getParentId(),
							  nodes[changedRecordIndex * 2].getId(),
							  nodes[changedRecordIndex * 2].getRawEvent(),
							  nodes[changedRecordIndex * 2].getLeftHash(),
							  nodes[changedRecordIndex * 2].getRightHash() };
		// Change the changed record's child hash
		nodes[changedRecordIndex].setLeftHash(myHash(hashVec));
		return;
	}
	// Recursive case: changed record has two children
	// Change the child IDs
	nodes[changedRecordIndex * 2].setId(myHash({ nodes[changedRecordIndex].getId(),
												 nodes[changedRecordIndex * 2].getRawEvent() }));
	nodes[changedRecordIndex * 2 + 1].setId(myHash({ nodes[changedRecordIndex].getId(),
													 nodes[changedRecordIndex * 2 + 1].getRawEvent() }));
	// Change the child parent IDs
	nodes[changedRecordIndex * 2].setParentId(nodes[changedRecordIndex].getId());
	nodes[changedRecordIndex * 2 + 1].setParentId(nodes[changedRecordIndex].getId());
	// Vector of hash function input strings
	vector<string>hashVec = { nodes[changedRecordIndex * 2].getParentId(),
							  nodes[changedRecordIndex * 2].getId(),
							  nodes[changedRecordIndex * 2].getRawEvent(),
							  nodes[changedRecordIndex * 2].getLeftHash(),
							  nodes[changedRecordIndex * 2].getRightHash() };
	// Change left child hash of changed record
	nodes[changedRecordIndex].setLeftHash(myHash(hashVec));
	hashVec = { nodes[changedRecordIndex * 2 + 1].getParentId(),
				nodes[changedRecordIndex * 2 + 1].getId(),
				nodes[changedRecordIndex * 2 + 1].getRawEvent(),
				nodes[changedRecordIndex * 2 + 1].getLeftHash(),
				nodes[changedRecordIndex * 2 + 1].getRightHash() };
	// Change left child hash of changed record
	nodes[changedRecordIndex].setRightHash(myHash(hashVec));

	// Recursively call this function for changed record's children
	propagateChangeDownTree(changedRecordIndex * 2);
	propagateChangeDownTree(changedRecordIndex * 2 + 1);
}

void TrackingTree::grow() {
	// Double the size of the container
	int newSize = newestRecord * 2;
	while (nodes.size() != newSize) {
		nodes.push_back(Node(""));
	}
}

void TrackingTree::getEvent(string& newEvent) {
	// Ignore any garbage in cin
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	// Get the new event
	cout << "  Enter the new event: ";
	getline(cin, newEvent);
	// Resize if necessary
	if (newEvent.size() >= 1024) {
		newEvent.resize(1024);
	}
	cout << endl;
}