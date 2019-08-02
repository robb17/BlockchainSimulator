//  ---------------------------------------------------------------------------
//  Source file for blockchain, where a blockchain is made up 	 blockchain.cpp
//		of some number of blocks connected together by
//		smartpointers.
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 12/1/18
//  Date modified: 12/9/18
// ----------------------------------------------------------------------------
#include "blockchain.hpp"

// ----------------------------------------------------------------------------
// Call the recursive printing function defined for each block.
//
ostream& Blockchain::print(ostream& out) const {
	Block* current_block_p = current.myTarget();
	(*current_block_p).printFromGenesis(out);
	return out;
}

// ----------------------------------------------------------------------------
// Extend the blockchain by exactly one block.
//
Blockchain Blockchain::extend() {
	Block* bp = new Block(current);					// make a new block
	Blockchain bc(bp);
	return bc;
}

// ----------------------------------------------------------------------------
// Test if one blockchain is shorter than another. If chains have the same
// height, that which has a top-level block ID that is less than that of
// another is considered to be shorter.
//
bool Blockchain::operator<(Blockchain bc) const {
	if (length() == bc.length()) {
		return ((*tail()).serialLessThan(bc.tail()));
	} else {
		return (length() > bc.length());
	}
}