//  ---------------------------------------------------------------------------
//  Header file for class block										  block.hpp
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 12/1/18
//  Date modified: 12/9/18
// ----------------------------------------------------------------------------

#ifndef BLOCK_H
#define BLOCK_H

#include "tools.hpp"
#include "SPtr.hpp"

// ----------------------------------------------------------------------------
//	Class Block instantiates the basis of the blockchain.
//
class Block {
private:
	const SPtr ptr;
	const int serialNo;
	const int level;

	int identifier() const { return serialNo; }
	
public:
	// Constructor for the genesis block
	Block() : ptr(SPtr()) , serialNo(ptr.id()) , level(0) {}

	// Constructor for non-genesis blocks
	Block(SPtr s) : ptr(SPtr(s)) , serialNo(ptr.id()) , level(((*s).blkLevel() + 1))  {}

	Block(const Block& b) = delete;				// blocks not allowed to be copied
	Block& operator=(const Block& b) = delete;

	// Returns block height
	int blkLevel() const { return level; };

	// Tests if block ID is less than that of another
	bool serialLessThan(Block* b) const { return (serialNo < b->identifier()); }

	ostream& print(ostream& out) const;
	ostream& printFromGenesis(ostream& out) const;
};

// ----------------------------------------------------------------------------
// Define the << operator for block such that it prints information about the 
// current block as defined in print().
//
inline ostream& operator<<(ostream& out, const Block& b) { return b.print(out); }

#endif