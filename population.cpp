//  ---------------------------------------------------------------------------
//  Source file for population, where a population is made up 	 population.cpp
//		of some number of fickle agents and some number of
//      crowd agents.
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 10/27/18
//  Date modified: 12/10/18
// ----------------------------------------------------------------------------
#include "population.hpp"

// ----------------------------------------------------------------------------
// The given agent sends a message to the given receiver, and the inventory
// is updated accordingly.
//
void Population::sendMessage(int sender, int receiver) {
	Blockchain rChoice = agents[receiver]->choice(); 		// old receiver's choice
	Blockchain sChoice = agents[sender]->choice(); 			// sender's choice
	agents[receiver]->update(sChoice);
	Blockchain newrChoice = agents[receiver]->choice();
	if (!(rChoice == newrChoice)) {
		inv.subtract(rChoice);
		inv.add(newrChoice);
		cout << inv;										// print inventory
	}
}

// ----------------------------------------------------------------------------
// Extend an agent's blockchain by exactly one block
//
void Population::extend(int receiver) {
	inv.subtract(agents[receiver]->choice());
	agents[receiver]->extend();
	inv.add(agents[receiver]->choice());
	// cout << "  New blockchain: " << agents[receiver]->choice() << endl;
	cout << inv;												// print inventory
}

// ----------------------------------------------------------------------------
// Print population statistics.
//
void Population::printStats() const {
	cout << setw(20) << left << "Population statistics:" << endl;
	cout << setw(13) << right << "numNak:" << setw(7) << numNak << endl;
	cout << setw(13) << right << "numFickle:" << setw(7) << numFickle << endl;
	cout << setw(13) << "numCrowd:" << setw(7) << numAgents - numNak - numFickle << endl;
	cout << setw(13) << "probExtend:" << setw(7) << probExtend << endl << endl;
}

// ----------------------------------------------------------------------------
// Print the blockchains maintained by all agents.
//
ostream& Population::print(ostream& out) const {
	for (int j = 0; j < numAgents; j++) {
		cout << "Agent " << j << " choice: " << agents[j]->choice();
		cout << endl;
	}
	return out;
}