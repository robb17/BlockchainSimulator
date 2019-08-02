//  ---------------------------------------------------------------------------
//  Source file for simulator, which models a group of agents 	  simulator.cpp
//		attempting to reach consensus.
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 11/10/18
//	Date modified: 12/9/18
// ----------------------------------------------------------------------------
#include "simulator.hpp"

// ----------------------------------------------------------------------------
// Generate a uniformly-distributed random integer in the range [0, ..., n - 1]
// Courtesy of Michael J. Fischer
//
int Simulator::uRandom(int n) {
	long int usefulMax = RAND_MAX - ((RAND_MAX - n) + 1) % n;
	long int r;
	do { r = random(); }
	while (r > usefulMax);
	return r % n;
}

// ----------------------------------------------------------------------------
// So long as rounds is less than maxRounds, with probability probExtend,
// extend a random blockchain by exactly one unit. With probability
// 1 - probExtend, send a message from one random blockchain to another.
//
void Simulator::run() {
	cout << "Starting simulation with probExtend = " << probExtend << endl;
	while (rounds < maxRounds) {

		if (pop.dRandom() < probExtend) {

			int extender = uRandom(pop.size());
			// cout << "  extend(" << extender << ")" << endl;
			pop.extend(extender);

		} else {

			if (pop.size() == 1) {
				rounds++;
				continue;
			}
			int sender = uRandom(pop.size());
			int receiver = uRandom(pop.size() - 1);
			if (receiver >= sender) { 	// achieve uniform distribution
				receiver++;
			}
			// cout << "  sendMessage(" << sender << ", " << receiver << ")" << endl;
			pop.sendMessage(sender, receiver);
		}

		rounds++;
	}
}