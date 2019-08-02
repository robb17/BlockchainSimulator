//  ---------------------------------------------------------------------------
//  Source file for class agent. Agents are of three types:	  		  agent.cpp
//		Fickle, Crowd, and Nakamoto. Fickle agents will update
//		their current chain to be whatever's sent to them. Crowd
//		agents will update their current chain to be that which
//		is sent to them if and only if their most recent message
//		suggested to switch to the same chain. Nakamoto agents
//		will update their current chain to be that which is sent
//		to them if and only if the new chain is longer than that
//		which they currently maintain.
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 12/9/18
// ----------------------------------------------------------------------------

#include "agent.hpp"

// ----------------------------------------------------------------------------
// Update the agent's choice based on the message m given, but only if current
// chain is the same as the last message received.
//
void Crowd::update(Blockchain b) {
	if (b == last_chain && !(this->b == b)) {
		this->b = last_chain;
	}
	last_chain = b;
}

// ----------------------------------------------------------------------------
// Print the blockchain maintained by this Agent(Base).
//
ostream& AgentBase::print(ostream& out) const {
	cout << b;
	return out;
}