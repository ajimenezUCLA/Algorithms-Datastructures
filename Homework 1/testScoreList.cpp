#include <iostream>
#include <cassert>
#include "ScoreList.h"

using namespace std;

int main()
{
	ScoreList scores;
	assert(scores.size() == 0);				// confirms the ctor creates an empty scores list.
	// cout << scores.size() << endl;
	assert(scores.add(0));
	assert(scores.add(50));
	assert(scores.add(99));					// Current roster |0|50|99|
	assert(!scores.add(-5));				// confirms cannot place a score less than 0
	assert(!scores.add(105));				// no extra credit for these kids - cannot place score > 100
	assert(scores.size() == 3);				// sequence is incrementing correctly
	// cout << scores.size() << endl;
	assert(scores.add(10));					// introduces a new score of 10
											// current roster |10|50|99|
	assert(scores.remove(0));
	assert(scores.size() == 3);				// confirms we again only have 3 scores in our sequence.
	
	assert(scores.maximum() == 99);
	assert(scores.minimum() == 10);
	assert(scores.size() == 3);
	
	// cout << "Scores sequence size: " << scores.size() << endl;			// perfect lining for my outputs ;)
	// cout << "The minimum score is: " << scores.minimum() << endl;
	// cout << "The maximum score is: " << scores.maximum() << endl;
	// cout << "Tests Complete" << endl;
}

/*
ScoreList();

bool add(unsigned long score);

bool remove(unsigned long score);

int size() const; 

unsigned long minimum() const;

unsigned long maximum() const;
*/
