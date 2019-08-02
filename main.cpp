//  ---------------------------------------------------------------------------
//  Main source file for consensus, which allows for command-line	   main.cpp
//		simulation of a simple consensus-reaching algorithm (fickle).
//		The simulation is run until all agents have the same choice.
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 11/10/18
//  Date modified: 12/10/18
// ----------------------------------------------------------------------------
#include "tools.hpp"
#include "SPtr.hpp"
#include "blockchain.hpp"
#include "simulator.hpp"

static
void run(int argc, char* argv[]);
static
void initializeFromArgs(int& numAgents, int& maxRounds, double& probNak, double& probFickle, double& probExtend, unsigned int& seed, int argc, char* argv[]);
static
void printInputStatistics(int seed, int numAgents, int maxRounds, double probNak, double probFickle, double probExtend);

// ----------------------------------------------------------------------------
int
main(int argc, char* argv[]) {
	banner();
	run(argc, argv);
	bye();
}

// ----------------------------------------------------------------------------
// Call the simulator constructor, run the simulation, and print the results. 
//
void 
run(int argc, char* argv[]) {
	int numAgents;
	int maxRounds;
	double probNak;
	double probFickle;
	double probExtend;
	unsigned int seed;

	if (argc > 7 || argc < 6) {
		fatal("usage: %s numAgents maxRounds probNak probFickle probExtend [seed]", argv[0]);
	}

	initializeFromArgs(numAgents, maxRounds, probNak, probFickle, probExtend, seed, argc, argv);

	printInputStatistics(seed, numAgents, maxRounds, probNak, probFickle, probExtend);

	Population pop = Population(numAgents, probNak, probFickle, probExtend, seed);
	Simulator sim = Simulator(pop, maxRounds, probExtend);

	sim.run();

	cout << "Current blockchain choices after " << maxRounds << " rounds:" << endl;
	cout << pop;

}

// ----------------------------------------------------------------------------
// Try to assign variables in accordance with command-line arguments, handle
// unexpected inputs
//
void initializeFromArgs(int& numAgents, int& maxRounds, double& probNak, double& probFickle, double& probExtend, unsigned int& seed, int argc, char* argv[]) {
	stringstream arg1stream(argv[1]);
	stringstream arg2stream(argv[2]);
	stringstream arg3stream(argv[3]);
	stringstream arg4stream(argv[4]);
	stringstream arg5stream(argv[5]);
	arg1stream >> numAgents;
	arg2stream >> maxRounds;
	arg3stream >> probNak;
	arg4stream >> probFickle;
	arg5stream >> probExtend;
	if (arg1stream.fail() || !arg1stream.eof()) {
		fatal("The first argument is not convertable to an integer.");
	} else if (arg2stream.fail() || !arg2stream.eof()) {
		fatal("The second argument is not convertable to an integer.");
	} else if (arg3stream.fail() || !arg3stream.eof()) {
		fatal("The third argument is not convertable to a double.");
	} else if (arg4stream.fail() || !arg4stream.eof()) {
		fatal("The fourth argument is not convertable to a double.");
	} else if (arg5stream.fail() || !arg5stream.eof()) {
		fatal("The fifth argument is not convertable to a double.");
	}
	if (argc == 6) {
		seed = time(0);
	} else {
		stringstream seedstream(argv[6]);
		seedstream >> seed;
		if (seedstream.fail() || !seedstream.eof()) {
			fatal("The sixth argument is not convertable to an unsigned integer.");
		}
	}

	if (numAgents <= 0) { 			// handle cases with undefined behavior
		fatal("Performing a simulation on non-positive number of agents is either unnecessary or undefined.");
	} else if (probFickle >= 1 || probFickle < 0) {
		fatal("The probability of a given agent's status as fickle must be a real number in the interval [0, 1).");
	} else if (maxRounds < 0) {
		fatal("A non-negative number of rounds must be inputted as maxRounds.");
	}  else if (probNak > 1 || probNak < 0) {
		fatal("The probability of a given agent's status as nakamoto must be a real number in the interval [0, 1].");
	} else if (probFickle + probNak > 1) {
		fatal("The probability of a given agent's status as crowd must be a real number in the interval [0, 1].");
	} else if (probExtend > 1 || probExtend < 0) {
		fatal("The probability that a given agent have choice equal to 1 must be a real number in the interval [0, 1].");
	}
}

// ----------------------------------------------------------------------------
// Print welcome and inputs.
//
void printInputStatistics(int seed, int numAgents, int maxRounds, double probNak, double probFickle, double probExtend) {
	cout << "Welcome to Consensus Simulator!" << endl;
	cout << "Using seed: " << seed << endl;
	cout << setw(13) << right << "numAgents:" << setw(7) << numAgents << endl;
	cout << setw(13) << right << "maxRounds:" << setw(7) << maxRounds << endl;
	cout << setw(13) << "probNak:" << setw(7) << probNak << endl;
	cout << setw(13) << "probFickle:" << setw(7) << probFickle << endl;
	cout << setw(13) << "probExtend:" << setw(7) << probExtend << endl << endl;
}
