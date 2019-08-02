//  ---------------------------------------------------------------------------
//  Header file for class blockchain						  	 blockchain.hpp
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 12/1/18
//  Date modified: 12/9/18
// ----------------------------------------------------------------------------

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.hpp"
#include "tools.hpp"

// ----------------------------------------------------------------------------
// Class blockchain uses smartpointers to point at the most recent block.
//
class Blockchain {
private:
	SPtr current;

public:
	// Construct totally new blockchain
	Blockchain(Block *b = new Block()) {
		current = SPtr(b);					// move assignment
	}

	// ----------------------------------------------------------------------------
	// Return the length of the blockchain
	//
	unsigned length() const { return current.myTarget()->blkLevel(); }

	// ----------------------------------------------------------------------------
	// Return a pointer to the most recently added block
	//
	Block* tail() const { return current.myTarget(); }

	// ----------------------------------------------------------------------------
	// Test for equality between two blockchains. Because blocks cannot be copied,
	// if both chains end at the same block, it must be true that they are the
	// same chain
	//
	bool operator==(Blockchain bc) const { return (current.myTarget() == bc.tail()); }

	bool operator<(Blockchain bc) const;

	// Function declarations
	Blockchain extend();
	ostream& print(ostream& out) const;
};

// ----------------------------------------------------------------------------
// Define the << operator for blockchain
//
inline ostream& operator<<(ostream& out, const Blockchain& b) { return b.print(out); }

#endif