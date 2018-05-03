// History.cpp

#include "History.h"
#include "globals.h"

#include <iostream>
#include <cstdlib>
using namespace std;

History::History(int nRows, int nCols)
	:m_rows(nRows), m_cols(nCols)		// sets m_rows = nRows, initializes member list
{
	// want to be a catch that will check to see if the values are beyond our range
	// if they are, it will terminate before attempting to create a grid object
	if (nRows < 1 || nRows > MAXROWS || nCols < 1 || nCols > MAXCOLS)
	{
		cout << "***** History created with invalid size " << nRows << " by "
			<< nCols << "!" << endl;					// stolen from City.cpp
		exit(1);
	}
	// we made it past the catch, so our values are good.
	// now we must create the grid object for our history
	for (int r = 0; r < nRows; r++) 
	{
		for (int c = 0; c < nCols; c++)
		{
			m_grid[r][c] = 0;
		}						// this should be the same as the private grid in the History.h
	}							// it should be stored in the History.h that way its accessible
								// by the City call functions... I think
								// we initialize the entire matrix with zeros, becuase
								// at the start of the game, no flatulan has been converted
							
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
The record function is to be called to notify the History object
that a Flatulan at the indicated location was converted upon
being preached to. The function returns false if row r, column c 
is not within the City; otherwise, it returns true after 
recording what it needs to. This function expects its parameters
to be expressed in the same coordinate system as the City 
(e.g., row 1, column 1 is the upper-left-most position).
*/


// (QQQQ) - Can you better explain the record function? What is it doing exactly, why is it bool?

bool History::record(int r, int c)					// so this should take the m_grid object, and update it if a flatulan was converted at [r][c] location
{
													// similar type of catch as before
	if (r <= 0 || r > m_rows || c <= 0 || c > m_cols)	// determines if the coordinate is within the city limits
	{
		return false;								// if any of the bad parameters are met, it will return false
	}
	m_grid[r-1][c-1]++;								// r-1 and c-1 because the game reads [1][1] as the initial, but our code initializes with [0][0]
	return true;									// this is supposed to record something, 
													// uncertain how to implement the record function
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
The display function clears the screen and displays the history 
grid as the posted programs do. This function does clear the
screen, display the history grid, and write an empty line after
the history grid; it does not print the Press enter to continue. 
after the display. (Note to Xcode users: It is acceptable that 
clearScreen() just writes a newline instead of clearing the
screen if you launch your program from within Xcode, since the
Xcode output window doesn't have the capability of being cleared.)
*/

void History::display() const
{
										// First we need to clear the screen
	clearScreen();
		// creates copy of m_grid[r][c]
										// Then we have to draw the grid
	for (int r = 0; r < m_rows; r++)									// (QQQQ) - do I have to define nRows? 
	{
		for (int c = 0; c < m_cols; c++)								// (QQQQ) - Do i have to define nCols?
		{
			char ch = '.';
			int numGrid = m_grid[r][c];	// assigns value of current grid coord to numGrid
			if (numGrid >= 26)
			{
				ch = 'Z';
			}
			else if (numGrid > 0)
			{
				ch = 'A' + numGrid-1;	// minus 1 because A == 1
			}
			cout << ch;
		}
		cout << endl;
	}
	cout << endl;
}
