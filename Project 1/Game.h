// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

class City;

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nFlatulans);
	~Game();

	// Mutators
	void play();

private:
	City * m_city;	// calls class City, must include it
};

#endif // GAME_INCLUDED