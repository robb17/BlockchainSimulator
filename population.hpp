//  ---------------------------------------------------------------------------
//  Header file for class Population							 population.hpp
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 11/10/18
//  Date modified: 12/10/18
// ----------------------------------------------------------------------------
#ifndef POPULATION_H
#define POPULATION_H
#include "tools.hpp"
#include "agent.hpp"
#include "inventory.hpp"

// ----------------------------------------------------------------------------
class Population {
private:
	const int numAgents;
	int numNak;
	int numFickle;
	Inventory inv;
	const double probExtend;
	Agent** agents; // array in which all agents are stored

public:
	// ----------------------------------------------------------------------------
	// Construct population, intialize values
	//
	Population(int numAgents, double probNak, double probFickle, double probExtend, unsigned int seed) : numAgents(numAgents) , probExtend(probExtend) {
		srandom(seed); // init random number generator

		agents = new Agent*[numAgents]; 		// allocate space for agent pointers

		inv = Inventory();									// new inventory

		int numFickle = 0;
		int numNak = 0;

		Blockchain genesis = Blockchain();

		for (int j = 0; j < numAgents; j++) {

			double randomVal = dRandom();

			if (randomVal < probNak) {
				agents[j] = new Nakamoto(genesis);
				numNak++;
			} else if (randomVal < probNak + probFickle) {
				agents[j] = new Fickle(genesis);
				numFickle++;
			} else {
				agents[j] = new Crowd(genesis);
			}

			inv.add(agents[j]->choice());		// add each chain to inventory
		}
		this->numNak = numNak;
		this->numFickle = numFickle;

		printStats();

		cout << inv << endl;
	}

	// ----------------------------------------------------------------------------
	// Destructor must not be default because of dynamically-allocated memory
	//
	~Population() {
		for (int j = 0; j < numAgents; j++) {
			delete agents[j];					// delete each agent
		}
		delete agents;							// delete list of pointers
	}
	
	// ----------------------------------------------------------------------------
	// Return the number of agents.
	//
	int size() const { return numAgents; }

	// ----------------------------------------------------------------------------
	// Generate a random real in [0, 1)
	// Courtesy of Michael J. Fischer
	//
	double dRandom() { return random() / (RAND_MAX + 1.0); }

	void extend(int receiver);
	void sendMessage(int sender, int receiver);
	void printStats() const;
	ostream& print(ostream& out) const;
};

// ----------------------------------------------------------------------------
// Define the << operator for population such that it calls the print()
// function.
//
inline ostream& operator<<(ostream& out, const Population& pop) { return pop.print(out); }

#endif