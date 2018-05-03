// Name: Angel Jimenez
// Homework 1
// Problem (1),(2),(3)
//

#ifndef NEWSEQUENCE_INCLUDED
#define NEWSEQUENCE_INCLUDED

// #include <string>	// only included if we test strings
#include <iostream>
#include <stdio.h>

		// using ItemType = std::string;	
		// or typedef std::string ItemType;
		// using varName = returnType;
		// typedef returnType varName;
		// using ItemType = unsigned long;

 typedef unsigned long ItemType;
 // typedef std::string ItemType;

const int DEFAULT_MAX_ITEMS = 200;		// global variable used as a limiter

class Sequence
{
public:
	
	Sequence();							// Create an empty sequence (i.e., one with no items)
	Sequence(int itemSize);				// ctor for a sequence of itemSize (non default)
	Sequence(const Sequence& other);	// copy constructor
	Sequence& operator=(const Sequence& rhs);	// operator overrider, since we're dealing with dyn arrays
	~Sequence();						// deconstructor (compiler one no longer good)
	bool empty() const;					// Return true if the sequence is empty, otherwise false.
	int size() const;					// Return the number of items in the sequence.
	bool insert(int pos, const ItemType& value);
	// Insert value into the sequence so that it becomes the item at
	// position pos.  The original item at position pos and those that
	// follow it end up at positions one higher than they were at before.
	// Return true if 0 <= pos <= size() and the value could be
	// inserted.  (It might not be, if the sequence has a fixed capacity,
	// e.g., because it's implemented using a fixed-size array.)  Otherwise,
	// leave the sequence unchanged and return false.  Notice that
	// if pos is equal to size(), the value is inserted at the end.

	int insert(const ItemType& value);									// uncertain about this one
																		// Let p be the smallest integer such that value <= the item at
																		// position p in the sequence; if no such item exists (i.e.,
																		// value > all items in the sequence), let p be size().  Insert
																		// value into the sequence so that it becomes the item at position
																		// p.  The original item at position p and those that follow it end
																		// up at positions one higher than before.  Return p if the value
																		// was actually inserted.  Return -1 if the value was not inserted
																		// (perhaps because the sequence has a fixed capacity and is full).

	bool erase(int pos);												// modifies passed parameter, shouldn't be const
																		// If 0 <= pos < size(), remove the item at position pos from
																		// the sequence (so that all items that followed that item end up at
																		// positions one lower than they were at before), and return true.
																		// Otherwise, leave the sequence unchanged and return false.

	int remove(const ItemType& value);									// not const, modifies paramters
																		// Erase all items from the sequence that == value.  Return the
																		// number of items removed (which will be 0 if no item == value).

	bool get(int pos, ItemType& value) const;							// this simply copies the values, doesn't change them
																		// If 0 <= pos < size(), copy into value the item at position pos
																		// in the sequence and return true.  Otherwise, leave value unchanged
																		// and return false.

	bool set(int pos, const ItemType& value);							// can't be constant function, pos may change
																		// If 0 <= pos < size(), replace the item at position pos in the
																		// sequence with value and return true.  Otherwise, leave the sequence
																		// unchanged and return false.

	int find(const ItemType& value) const;								// we pass in value, but we do not modify it,therefore we can make this function a const
																		// Let p be the smallest integer such that value == the item at			
																		// position p in the sequence; if no such item exists, let p be -1.
																		// Return p.

	void swap(Sequence& other);											// function job is to swap sequences, cant be const
																		// Exchange the contents of this sequence with the other one.
private:
	int m_size;									// stores sequence size
	int m_cap;									// Sequence Capacity

	// modify our ItemType
	ItemType* m_value;



};

#endif // NEWSEQUENCE_INCLUDED