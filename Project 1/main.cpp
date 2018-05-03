// gas.cpp

/*				Why can't we include them all in main?
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include "Flatulan.h"
#include "Player.h"
#include "City.h"
#include "globals.h"
*/
#include "Game.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

// Return a random int from min to max, inclusive

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
	// Create a game
	// Use this instead to create a mini-game:   Game g(3, 4, 2);
	Game g(7, 8, 25);

	// Play the game
	g.play();
}
