//  ---------------------------------------------------------------------------
//  Header file for class inventory								  inventory.hpp
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 12/9/18
// ----------------------------------------------------------------------------

#ifndef INVENTORY_H
#define INVENTORY_H

#include "blockchain.hpp"
#include "tools.hpp"
#include <map>

// ----------------------------------------------------------------------------
class Inventory {
private:
	map<Blockchain,int> table;

public:
	Inventory() { ; }

	void add(Blockchain bc);

	void subtract(Blockchain bc);

	ostream& print(ostream& out);
};

// ----------------------------------------------------------------------------
// Define the << operator for inventory such that it prints all maintained
// blockchains by calling the print() method.
//
inline ostream& operator<<(ostream& out, Inventory& in) { return in.print(out); }

#endif