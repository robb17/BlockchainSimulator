//  ---------------------------------------------------------------------------
//  Author: Charles Robert Brunstad					readme
//	Date created: 12/10/18
// ----------------------------------------------------------------------------

A simulator for a number of agents attempting to reach consensus. The agents have
identities as follows:
	- fickle
		- Whenever a fickle agent receives a signal, its chice is updated to
			match that associated with the signal.
	- follow-the-crowd
		- This agent changes its choice to match that of an incoming message
			if and only if said agent's most recent message was the exact
			same.
Included:
	- main.cpp
		- main source file
	- inventory.cpp
		- source file for the class inventory, which maintains a (sorted) map
			of all the agents of a given population.
	- inventory.hpp
	- simulator.cpp
		- source file for the class simulator, which simulates agents of two
			types, "fickle" and "crowd," interacting with each other (across
			and within agent types) to reach consensus
	- simulator.hpp
	- agent.cpp
		- source file for the derived agent class functions.
	- agent.hpp
		- header file that declares and defines the agent class and its derived
			classes
	- population.cpp
		- source file for class population, where a population is defined to
			contain a number of fickle and a number of crowd agents.
	- population.hpp
	- blockchain.cpp
		- source file for the class blockchain, which is defined to consist
			of a series of blocks.
	- blockchain.hpp
	- block.cpp
		- source file for the class block, which is the basic unit of a
			blockchain. blocks have levels, as determined by their positions
			in their respective blockchains, and unique serial numbers
	- block.hpp
		- header file that declares and defines the block class
	- SPtr.cpp
		- source file for class SPtr, or smart pointer. Smart pointers
			automatically delete blocks that are no longer reachable
	- SPtr.hpp
	- Serial.cpp
		- source file for class Serial, which enables generation of unique ids
	- Serial.hpp
	- tools.cpp
		- source file that provides basic tools and utilities
	- tools.hpp
	- Makefile
	- notes (this file)
	- blockchain.in
		- supporting file that describes testing inputs
	- blockchain.out
		- supporting file that describes the results of testing
	- sample.sh
		- provided for reference
	- sample.out
		- provided for reference

Usage:
./blockchain numAgents maxRounds probNak probFickle probExtend [seed]
	- numAgents gives the number of agents maintaining their own blockchains
	- probNak is a real number in the range [0, 1] that specifies the 
		probability that an agent is chosen to be of type Nakamoto.
	- probFickle is a real number in the range [0, 1) that specifies the
		probability that an agent is chosen to be of type Fickle. The range
		excludes 1 because ps5 specifies such a window.
	- probExtend a real number in the range [0, 1] that specifies
		the probability that a given round of simulation involves the
		extension of a random chain. A message is propagated with probability
		1 - probExtend.
	- [seed], an optional argument, seeds the random number generator.

Comments:
- Inputs for probNak, probFickle, and probExtend must be within the window
	discussed above.
- Simulations can be run only on n agents, where n is less than the largest
	number representable by a signed int.
- Stringstreams are used owing to their ease of implementation and the ability
	to use standard status functions.
- With the exception of the first recorded output, debugging messages have been
	omitted so that the experience of reading blockchain.out is a bit
	more pleasant.
