#include "newSequence.h"
#include <iostream>
#include <cassert>
#include <stdio.h>

using namespace std;

Sequence::Sequence()
{
	// Create an empty sequence (i.e., one with no items)

	// assuming the user doesn't put in values less than 0

	m_size = 0;						// defaults our size to zero
	m_cap = DEFAULT_MAX_ITEMS;		// sets our sequence capacity to the allowable limit
	m_value = new ItemType[m_cap];	// dynamically allocates a sequence
}

Sequence::Sequence(int itemSize)				// non default constructor
{												// not convinced this is necessary, but it's failsafe
	m_cap = itemSize;							// non default size
	m_size = 0;
	m_value = new ItemType[m_cap];
}

Sequence::Sequence(const Sequence& other)		// copy constructor
{												// it is okay to overwrite the previous seq b/c we only care about copying
	m_size = other.size();						// assigns to the called sequence, the size of the referenced sequence
	m_cap = other.m_cap;						// assigns called sequence the capacity of the referenced sequence
	m_value = new ItemType[m_cap];				// dynamically allocates the copied data type. (maybe we could overwrite it instead?)

	for (int i = 0; i < m_size; i++)			// go through the sequence, reassigning the old sequence to the new one, item by item
	{
		m_value[i] = other.m_value[i];
	}
}
Sequence& Sequence::operator=(const Sequence& rhs)	// operator override so = can deal with our dynamic arrays
{													// since we're passing by ref, we don't have to return anything
	if (this != &rhs)								// however, we return *this to tell the function, it's comparing the same item.
	{
		Sequence tempSeq(rhs);						// creates a temp sequence to perform the equivalence.
		swap(tempSeq);								// utilize our improved swap function, otherwise we code the swap here as well.
	}		
	return *this;									// the if statement catches the case wherein we're comparing the same items
}													// we perform this by checking their addresses.

Sequence::~Sequence()							// since we no longer rely trust the compier dtor
{												// we created this one to dispose of unused dynamically allocated
	delete [] m_value;							// sequences, this is to prevent memory leaks.
}

bool Sequence::empty() const						// no changes here
{
	// Return true if the sequence is empty, otherwise false.
	if (m_size == 0)	
		return true;
	return false;
}

int Sequence::size() const							// no changes here
{
	// Return the number of items in the sequence.
	return m_size;		// returns the private member m_size
}


bool Sequence::insert(int pos, const ItemType& value)
{

	// [X] Insert value into the sequence so that it becomes the item at position pos.  (last step)
	// [X] The original item at position pos and those that follow it end up at positions one higher than they were at before.
	// [X] Return true if 0 <= pos <= size() and the value could be inserted. (It might not be, if the sequence has a fixed capacity,
	//	   e.g., because it's implemented using a fixed-size array.)  Otherwise, leave the sequence unchanged and return false. 
	// [X] Notice that if pos is equal to size(), the value is inserted at the end.

	// Bad case catcher: 
	// 1) pos less than zero (out of bounds)
	// 2) pos greater than size (out of bounds)
	// 3) size is larger than allowable limit

	if (pos < 0 || pos > size() || size() >= m_cap)	// bad case catcher, bad cases: pos greater
	{												// !! we changed DEFAULT_MAX_ITEMS to m_cap
		return false; 
	}
	// parameter made it through the catch, therefore it will be added. thus we increase the size by 1.
	
	/*
	if (pos == size())					// if pos is equal to size(), we insert the value at the end.
	{
		
		m_value[pos] = value;		// we subtract 1 from size, because the array starts at 0
		m_size++;
		return true;
	}
	*/
	// if it proceeds, then we have a permissible parameter 
	for (int i = size(); i > pos; i--)
	{
		m_value[i] = m_value[i - 1];	//this starts from the end, it copies the previous one to the following, overwriting the old one.
										// essetially [10] becomes [11], [9] becomes [10]... until we get to pos, where [pos] == [pos+1]
										// then once the loop is over, we will write over [pos], thus including it to the array.
		// m_value[i + 1] = m_value[i];
	}
	m_value[pos] = value;
	m_size++;
	return true;
}



int Sequence::insert(const ItemType& value)
{

	// [X] Let p be the smallest integer such that value <= the item at position p in the sequence; 
	// [X] if no such item exists (i.e., value > all items in the sequence), let p be size().  
	// [X] Insert value into the sequence so that it becomes the item at position p.  
	// [X] The original item at position p and those that follow it end up at positions one higher than before.  
	// [X] Return p if the value was actually inserted.  
	// [X] Return -1 if the value was not inserted (perhaps because the sequence has a fixed capacity and is full).
	
	int p = 0;	// initialize p.
	
	// two cases: 1) p is smallest integer such that value <= m_value[p]
	//			: 2) no such item exists, value > m_value[p], then p = size();
	for (int i = 0; i < size() ; i++)	// cycling through the array, starting from the bottom (want the smallest p)
	{
		if (m_value[i] >= value)	// this will catch the case where value <= m_value[p];
		{
			p = i;					// assign p to the current position
			break;					// exit the for loop
		}
		else
		{
			p = size();				// the second case is passed; the argument value is the largest, thus set p = size();
		}
	}
	// insert the item at p	(similar code used before)
	if (p < 0 || p > size() || size() >= m_cap)	// bad case catcher, bad cases: pos greater
	{														// !! newSequence.cpp change: DEFAULT_MAX_ITEMS to m_cap
		return -1;			// can't be inserted
	}
	// parameter made it through the catch, therefore it will be added. thus we increase the size by 1.
	for (int i = size(); i > p; i--)
	{
		m_value[i] = m_value[i - 1];	//this starts from the end, it copies the previous one to the following, overwriting the old one.
										// essetially [10] becomes [11], [9] becomes [10]... until we get to pos, where [pos] == [pos+1]
										// then once the loop is over, we will write over [pos], thus including it to the array.
										// m_value[i + 1] = m_value[i];
	}
	m_value[p] = value;
	m_size++;
	return p;
}


bool Sequence::erase(int pos)
{
	// [x] If 0 <= pos < size(), remove the item at position pos from
	//	  the sequence (so that all items that followed that item end up at
	//    positions one lower than they were at before), and return true.
	// [x] Otherwise, leave the sequence unchanged and return false.
	
	if(pos>=size()||pos<0)						// catches a bad case
	{
		return false;							// sequence unchanged
	}
	else
	{
		for ( int i = pos; i < size()-1; i++)	// starting from the given position, move through
		{										// the sequence. We overwrite the starting position
			m_value[i] = m_value[i+1];			// with the item after the given position.
		}										// increment i and repeat, in this way, we'll "erase"
		m_size--;								// the passed position and once the for loop ends, 
		return true;							// we decrease the size of the sequence by 1 and return true.
	}
}


int Sequence::remove(const ItemType& value)
{
	// [X] Erase all items from the sequence that == value.  
	// [X] Return the number of items removed (which will be 0 if no item == value).
	
	int rCount = 0;						// to keep track of the amount removed
	for ( int i =0; i < size(); i++)	// cycle through the sequence, checking at every step
	{									// for our removal criteria ( == ).
		if (m_value[i]==value)			// if criteria met, erase position, increment removal count
		{								// then decrease the count size due to the change in sequence size
			int k = i;					// the last step is crucial.
			erase(k);
			rCount++;
			i--;
		}
	}
	return rCount;
}

bool Sequence::get(int pos, ItemType& value) const		// newSequence.cpp - no changes.
{

	// [X] If 0 <= pos < size(), copy into value the item at position pos in the sequence and return true.  
	// [X] Otherwise, leave value unchanged and return false.


	//pseudo code:
	// if ( 0 <= pos < size())
	// {
	//		value = m_value[pos]	// copy into value means... value = ...
	//		return true;
	//	}
	//	return false;
	if (pos >= 0 && pos < size())	//checks criteria, i.e., 0 <= pos < size()
	{
		value = m_value[pos];		// copies the value in our sequence into the variable value
		return true;
	}
	return false;
}


bool Sequence::set(int pos, const ItemType& value)		// newSequence.cpp - no changes.
{

	// [X] If 0 <= pos < size(), replace the item at position pos in the sequence with value and return true.
	// [X] Otherwise, leave the sequence unchanged and return false.

	//psuedo code:
	// if( 0 <= pos < size()) // catches criteria.
	// m_value[pos] = value; return true;
	// else return false;
	if (pos >= 0 && pos < size())
	{
		m_value[pos] = value;
		return true;
	}
	return false;
}

int Sequence::find(const ItemType& value) const			// newSequence.cpp - no changes.
{
	// [X] Let p be the smallest integer such that value == the item at position p in the sequence;
	// [X] if no such item exists, let p be -1.
	// [X] Return p.
	for (int p = 0; p < size(); p++)
	{
		if (m_value[p] == value)
		{
			return p;
		}
	}
	return -1;
}


void Sequence::swap(Sequence& other)
{
	// [] Exchange the contents of this sequence with the other one.

	// psuedo code:
	// create temp array of m_size (use size())
	// we have three arrays now. m_value[], tempArray[], other.m_value[]
	// assign tempArray[k] to m_value[k] & m_value[k] to other.m_value[k]
	// then assign other.m_value[k] to tempArray[k]

	ItemType* tempPtr;		// our swap function will deal with pointers now
	tempPtr = m_value;		// default our pointer location to our sequence.
	int tempSize = 0;		// place holder for the size swap
	int tempCap = 0;
	
	// swap the sequences
	tempPtr = m_value;			// operator= stores m_value into tempPtr;
	m_value = other.m_value;	// operator= updates m_value with referenced sequence
	other.m_value = tempPtr;	// operator= reassigns other.m_value with m_value data held in tempPtr.

	// swap the capacities
	tempCap = m_cap;			// same logic as sequence swap
	m_cap = other.m_cap;
	other.m_cap = tempCap;

	// swap the sizes, this code stays the same from previous implementation

	tempSize = m_size;		// reuse tempSize, that way we don't have to implement the logic in swapping after
	m_size = other.m_size;	// having swapped the values.
	other.m_size = tempSize;
}
