//  ---------------------------------------------------------------------------
//  Source file for class inventory, which is responsible for	  inventory.hpp
//		maintaining a (sorted) map of the current set of
//		choices for all the agents in a given population.
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 12/9/18
// ----------------------------------------------------------------------------

#include "inventory.hpp"

// Update the inventory so as to reflect the fact that a blockchain has been
// added to it.
void Inventory::add(Blockchain bc) {
	if (table.size() == 0) {
		table.emplace(bc, 1);
		return;
	}

	map<Blockchain,int>::iterator it = table.find(bc);

	if (it == table.end()) {
		table.emplace(bc, 1);		// blockchain not found, insert blockchain
		return;
	}
	it->second += 1;
}

// Update the inventory so as to reflect the fact that a blockchain has been
// removed from it.
void Inventory::subtract(Blockchain bc) {

	map<Blockchain,int>::iterator it = table.find(bc);

	if (it == table.end()) {
		fatal("Error: tried to subtract blockchain that did not exist.");
	}
	if (it->second == 1) {
		table.erase(it);
	} else {
		it->second -= 1;
	}
}

// Print all inventory contents in an organized way
ostream& Inventory::print(ostream& out) {

	map<Blockchain,int>::iterator it = table.begin();
	
	cout << "Inventory: " << table.size() << " active blockchain(s):" << endl;

	while (it != table.end()) {
		cout << "  " << it->second << " copies of " << it->first << endl;
		it++;
	}
	return out;
}