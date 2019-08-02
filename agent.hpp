//  ---------------------------------------------------------------------------
//  Header file for class agent								  		  agent.hpp
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 11/10/18
//	Date modified: 12/9/18
// ----------------------------------------------------------------------------
#ifndef AGENT_H
#define AGENT_H
#include "tools.hpp"
#include "blockchain.hpp"

// ----------------------------------------------------------------------------
// A pure abstract class Agent
//
class Agent {
public:
	virtual ~Agent() = default;

	// ----------------------------------------------------------------------------
	// When replaced, update agent's choice
	//
	virtual void update(Blockchain b) = 0;

	// ----------------------------------------------------------------------------
	// When replaced, return agent's choice
	//
	virtual Blockchain choice() const = 0;

	// ----------------------------------------------------------------------------
	// Extend the current blockchain by exactly one block.
	//
	virtual void extend() = 0;

	// ----------------------------------------------------------------------------
	// Print the agent's blockchain
	//
	virtual ostream& print(ostream& out) const = 0;
};

// ----------------------------------------------------------------------------
// A class that enables collection of functions common to all agents.
//
class AgentBase : public Agent {
protected:
	Blockchain b;

public:
	// ----------------------------------------------------------------------------
	// Placeholder update function
	//
	void update(Blockchain b) { ; }

	// ----------------------------------------------------------------------------
	// Return agent's choice
	//
	Blockchain choice() const { return b; }

	// ----------------------------------------------------------------------------
	// Extend the current blockchain by exactly one block.
	//
	void extend() { b = b.extend(); }

	ostream& print(ostream& out) const;
};

// ----------------------------------------------------------------------------
// Define the << operator for AgentBase
//
inline ostream& operator<<(ostream& out, const AgentBase& ab) { return ab.print(out); }

// ----------------------------------------------------------------------------
// A publicly derived class of AgentBase that will change its choice to whatever
// is given in a message to it
//
class Fickle : public AgentBase {
public:
	Fickle(Blockchain b) {
		this->b = b;
	}
	~Fickle() = default;

	// ----------------------------------------------------------------------------
	// Update the agent's choice based on the message given
	//
	void update(Blockchain b) { this->b = (!(b == this->b) ? b : this->b); }
};

// ----------------------------------------------------------------------------
// A publicly derivied class of AgentBase. A follow-the-crowd agent will change its
// choice to whatever it's given in a message only if the last message received
// by the agent was identical in content
//
class Crowd : public AgentBase {
private:
	Blockchain last_chain;

public:
	Crowd(Blockchain b) : last_chain(nullptr) { // last_chain should not be valid message at start
		this->b = b;
	}
	~Crowd() = default;

	void update(Blockchain b);
};

// ----------------------------------------------------------------------------
// A publicly derivied class of AgentBase. A Nakamoto agent will change its
// current choice of blockchain to another blockchain if and only if the
// new chain is longer than the current one.
//
class Nakamoto : public AgentBase {
public:
	Nakamoto(Blockchain b) {
		this->b = b;
	}
	~Nakamoto() = default;

	// ----------------------------------------------------------------------------
	// Update the agent's choice based on the message given.
	//
	void update(Blockchain b) { this->b = ((b.length() > this->b.length()) ? b : this->b); }
};

#endif