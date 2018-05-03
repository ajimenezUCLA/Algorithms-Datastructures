#include "newSequence.h"

#include <cassert>
#include <string>
#include <stdio.h>

using namespace std;

void unsignedLongTest()
{
	/********** TESTING UNSIGNED LONG ***********/
	Sequence s;
	assert(s.empty());			// if empty, returns true
	assert(s.find(42) == -1);	// since 42 cant be found, will return -1
	assert(s.insert(42) == 0);	// inserts 42 at position zero, therefore s.size() = 1
	assert(s.size() == 1 && s.find(42) == 0); //checks if the size is 1 and 42 is at the 0 position.

	int itt = 1;	// insert was called above, so start at 1
	assert(s.insert(0, 10)); itt++;	// insert 10 at position 0 current sequence is |10|42|
	assert(s.insert(1, 20)); itt++;
	assert(s.insert(2, 50)); itt++;
	assert(s.insert(3, 100)); itt++;
	assert(s.insert(4, 200)); itt++; // current sequence |10|20|50|100|200|42| therefore 42 is at position 5
	// cout << "itt size = " << itt<< endl;
	// cout << "s.size() = " << s.size() << endl;
	assert(s.size() == itt); // s.size() = 6 and itt = 6, 
	// cout << s.find(42);		// confirms location of 42
	assert(s.find(42) == 5);	// confirms location of 42	
	ItemType x = 0;
	assert(s.get(0, x) && x == 10);	// takes in x and reassigns it according to what is in position 0. which is 10
	assert(s.get(4, x) && x == 200);// takes x, reassigns it to value in position 4, compares it  200, which is the item in pos 4

	cout << "Old Sequence tests were successful" << endl;
}

int main()
{
	unsignedLongTest();	// pasts previous tests
	Sequence a(1000);   // a can hold at most 1000 items
	Sequence b(5);      // b can hold at most 5 items
	Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
	ItemType v = 808;

	// No failures inserting 5 items into b
	for (int k = 0; k < 5; k++)
		assert(b.insert(v) != -1);

	// Failure if we try to insert a sixth item into b
	assert(b.insert(v) == -1);

	// When two Sequences' contents are swapped, their capacities are
	// swapped as well:
	a.swap(b);
	assert(a.insert(v) == -1 && b.insert(v) != -1);
	cout << "New Sequence tests were successful" << endl;
}
