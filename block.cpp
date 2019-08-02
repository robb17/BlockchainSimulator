//  ---------------------------------------------------------------------------
//  Source file for block, which is the basic unit of a blockchain.	  block.cpp
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 12/1/18
//  Date modified: 12/9/18
// ----------------------------------------------------------------------------
#include "block.hpp"

// ----------------------------------------------------------------------------
// Recursive function that enables the entire blockchain to be printed
// as specified without use of a public ptr.
//
ostream& Block::printFromGenesis(ostream& out) const {
	if (level == 0) {					// start printing at genesis block
		return print(out);
	} else {
		ostream& delayed_out = ptr.myTarget()->printFromGenesis(out);
		cout << " ";					// separate prints by spaces
		return print(delayed_out);
	}
}

// ----------------------------------------------------------------------------
// Print basic information about a given block.
//
ostream& Block::print(ostream& out) const {
	cout << "[" << level << "," << serialNo << "]";
	return out;
}