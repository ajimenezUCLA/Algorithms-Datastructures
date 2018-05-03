#include "ScoreList.h"

ScoreList::ScoreList()
	: m_list()	// initialize this way because we're calling from a different class
{
	// Create an empty score list.
}


bool ScoreList::add(unsigned long score)
{
	// [X] If the score is valid (a value from 0 to 100) and the score list
	//	  has room for it, add it to the score list and return true.
	// [X] Otherwise, leave the score list unchanged and return false.

	if (/*score < 0 ||*/ score > 100 || m_list.size() >= DEFAULT_MAX_ITEMS)
	{			// unsigned longs, they're always positive. redundant
		return false;	
	}
	m_list.insert(score);
	return true;
}

bool ScoreList::remove(unsigned long score)		// NOTE: the remove function uses the erase function!!!
{
	// [X] Remove one instance of the specified score from the score list.
	// [X] Return true if a score was removed; otherwise false.
	
	if (m_list.find(score) != -1)			// determines if specific score is in list
	{										// returns pos if found, returns -1 if not found
		m_list.erase(m_list.find(score));	// uses the find function to return the position,
		return true;						// then uses the remove function to delete said position
	}
	return false;

	// better method? return m_list.erase(m_list.find(score));
	// theory: erase returns true if item was erased, false if it wasn't.
	// nested is m_list.find(score), which will return a position parameter. if it exists,
	// it returns the position p, if it doesn't it will return -1 , -1 is outside our sequence boundary.
	// erase is coded to handle this, it will return false.
}

int ScoreList::size() const 
{
	// [] Return the number of scores in the list.
	return m_list.size();
}

unsigned long ScoreList::minimum() const
{
	// [] Return the lowest score in the score list.  
	// [X] If the list is empty, return NO_SCORE.
	
	if (m_list.size() == 0)		// checks size of sequence, if 0, returns NO_SCORE.
	{							// alternatively, if(m_list.empty()) they're the same thing though.
		return NO_SCORE;
	}
	// we're going to cycle through our sequence, comparing the data
	// our default item should be one we know exists, the item at position 0.
	// we take item[k], then compare it to item[k+1] and so on.
	// however, we take the smallest of the two items, store this data.
	// and compare it to the next item, item[k+2], compare the data, and store the smallest
	// we repeat this until we reach the maximum size of the sequence.

	unsigned long minScore = 0;		// this item will store the current lowest score, the 0 doesn't matter.
	unsigned long minTemp = 0;		// this will temporarily store a comparison value.
	m_list.get(0, minTemp);		// obtain the initial value to compare. assuming the sequence holds at least 1 item.

	for (int i=0; i < size() /*m_list.size()*/; i++)				// QUESTION!!!!!! should this be i <= m_list.size() ?????
	{
		unsigned long x = 999;
		m_list.get(i, x);			// looks at position, i, assigns it to x.
		if (minTemp <= x)
		{
			minScore = minTemp;
		}
		else
		{
			minScore = x;
		}
	}

	return minScore;
}

unsigned long ScoreList::maximum() const
{
	// [] Return the highest score in the score list.  
	// [] If the list is empty, return NO_SCORE.

	if (m_list.size() == 0)
	{
		return NO_SCORE;
	}
	unsigned long maxScore = 0;		// this item will store the current lowest score, the 0 doesn't matter.
	unsigned long maxTemp = 0;		// this will temporarily store a comparison value.
	m_list.get(0, maxTemp);		// obtain the initial value to compare. assuming the sequence holds at least 1 item.

	for (int i = 0; i < size() /*m_list.size()*/; i++)				// QUESTION!!!!!! should this be i <= m_list.size() ?????
	{
		unsigned long x = 0;
		m_list.get(i, x);
		if (maxTemp >= x)			// same as the minimum score implementation, we just flip the comparator.
		{
			maxScore = maxTemp;
		}
		else
		{
			maxScore = x;
		}
	}
	return maxScore;

}