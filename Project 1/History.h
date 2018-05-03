// History.h

#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
{
public:
	History(int nRows, int nCols);
	bool record(int r, int c); //r: rows, c: cols
	void display() const;
private:
	// ??? 
	char m_grid[MAXROWS][MAXCOLS];	// this is to record
	int m_rows;						// 
	int m_cols;						// ??? Not entirely certain on the purpose of these
};

#endif HISTORY_INCLUDED