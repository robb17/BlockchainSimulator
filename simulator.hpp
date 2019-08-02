//  ---------------------------------------------------------------------------
//  Header file for class Simulator								  simulator.hpp
// 	Type: C++
// 	Tab-width: 4
//  Author: Charles Robert Brunstad
//	Date created: 11/10/18
// 	Date modified: 12/9/18
// ----------------------------------------------------------------------------
#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "tools.hpp"
#include "population.hpp"

// ----------------------------------------------------------------------------
class Simulator {
private:
	Population& pop;
	int rounds;
	const int maxRounds;
	const double probExtend;

	static
	int uRandom(int n);

public:
	// ----------------------------------------------------------------------------
	// Construct a simulator, initialize values
	//
	Simulator(Population& pop, int maxRounds, double probExtend) : pop(pop) , rounds(0) , maxRounds(maxRounds) , probExtend(probExtend) { }

	~Simulator() = default;

	void run();
};
#endif