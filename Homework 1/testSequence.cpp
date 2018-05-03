#include "Sequence.h"

#include <cassert>
// #include <string>		// only when testing strings(?)
#include <stdio.h>

using namespace std;

void stringTest()
{
	/**** STRING TESTING ********
	Sequence s;
	s.insert(0, "a");
	s.insert(1, "b");
	s.insert(2, "c");
	s.insert(3, "b");
	s.insert(4, "e");
	assert(s.remove("b") == 2);
	assert(s.size() == 3);
	string x;
	assert(s.get(0, x) && x == "a");
	assert(s.get(1, x) && x == "c");
	assert(s.get(2, x) && x == "e");

	Sequence s1;
	s1.insert(0, "paratha");
	s1.insert(0, "focaccia");
	Sequence s2;
	s2.insert(0, "roti");
	s1.swap(s2);
	assert(s1.size() == 1 && s1.find("roti") == 0 && s2.size() == 2 &&
		s2.find("focaccia") == 0 && s2.find("paratha") == 1);
	
	Sequence s;
	s.insert(0, "dosa");
	s.insert(1, "pita");
	s.insert(2, "");
	s.insert(3, "matzo");
	assert(s.find("") == 2);
	s.remove("dosa");
	assert(s.size() == 3 && s.find("pita") == 0 && s.find("") == 1 &&
		s.find("matzo") == 2);
	
		Sequence s;
		assert(s.empty());
		assert(s.find("laobing") == -1);
		assert(s.insert("laobing") == 0);
		assert(s.size() == 1 && s.find("laobing") == 0);

	// cout << "Passed all tests" << endl;
	// cout << "test complete" << endl;

	*/

}

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

	// cout << "Passed all tests" << endl;
}


int main()
{
	// to test the strings, you must go into Sequence.h and
	// use " typedef std::string ItemType; " instead 
	// of "typedef unsigned long ItemType;"

	// stringTest();

	// to test the int long ItemType
	// in sequence, uncomment out "typedef unsigned long ItemType;"
	// and comment out " typedef std::string ItemType; "

	unsignedLongTest();

	Sequence a;
	Sequence b;

	assert(a.empty());		// checks if they are empty
	assert(b.empty());

	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
	{
		a.insert(i);
	}
	assert(a.size() == 200);			// pulls m_size from a, compares it with 
	ItemType y = 0;
	assert(a.get(45, y) && y == 45);	// it should be 45 b/c of the for loop
	a.swap(b);
	assert(a.size() == 0);				// demonstrates the swap
	assert(b.size() == 200);
	ItemType w = 11;
	assert(b.get(45, w) && w == 45);	// swap successful, 45 pos contains 45, and was successfully swapped to b
	for (int j = 0; j < 50; j++)
	{
		b.remove(j);					// removes the first 50 items, setting 50 at position 0
	}
	assert(b.get(0, w) && w == 50);		// confirms 50 at position 0
	assert(b.size() == 150);			// confirms size was decreased by 50

	Sequence c;
	c.insert(0, 11);					// inserts 11 at position 0
	c.insert(c.size(), 13);				// inserts 13 at end position
	c.insert(1, 12);					// inserts 12 at middle position
	assert(c.size() == 3);				// confirms new size of Sequence
	assert(c.get(1, w) && w == 12);		// confirms 12 is in middle of sequence
	assert(c.find(13) == 2);			// finds 13, confirms its at position 2
	assert(!c.insert(80, 14));			// this is out of bounds, it will return false, but we make it true using ! for the assertion
	c.erase(0);							// removes 11 from the sequence leaving |12|13| (size 2)
	assert(c.find(12) == 0 && c.find(13) == 1);	// confirms items have been relocated
	assert(!c.erase(3));				// c.erase(3) returns false b/c out of bounds, ! makes it true

	unsigned long catDog = 101;			// confirms ItemType works appropriately 
	assert(c.get(0, catDog) && catDog == 12);
	unsigned long dogCat = 80;
	assert(c.set(1, dogCat) && c.find(80) == 1);
}
