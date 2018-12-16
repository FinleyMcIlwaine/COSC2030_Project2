// myHash.cpp
// Finley McIlwaine
// COSC2030 Project 2
// 11/21/18

#include "pch.h"
#include "myHash.h"

std::hash<string> hash_str;

// Concatenates the strings contained in a vector and hashes
// the result, resizing the hash output to an 8 character string
string myHash(vector<string> unhashed) {
	// Salting
	if (unhashed.size() < 2) {
		while (unhashed.size() < 2) {
			unhashed.push_back("{@${$:r43r{:#{54fsdf{:#{shufisdadfjik{:#{fjheww35r3452{:#{341e5wr5wse");
		}
	}

	// Concatenate vector strings
	string hashInput;
	for (string str : unhashed) {
		hashInput += str;
	}

	// Convert to string and resize
	string hashOutput = std::to_string(hash_str(hashInput));
	hashOutput.resize(8);

	return hashOutput;
}