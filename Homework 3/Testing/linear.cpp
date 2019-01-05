#include <string>
using namespace std;
bool somePredicate(string s);

#include <cassert>
#include <iostream>

  /////////////////////////////
 //		somePredicate		//
/////////////////////////////

bool somePredicate(string s)	// this predicate returns true if string is empty, otherwise false
{
	return s.empty();
}

  /////////////////////////////////////////
 //		IMPLEMENTATION OF FUNCTIONS		//
/////////////////////////////////////////

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{	
	if (n <= 0)								// checking the size
	{
		return false;
	}
	if (somePredicate(a[0]) == false)		// if the first string is false, return false
	{										// i wrote it this way for readability
		return false;
	}
	if (n == 1)
	{
		return true;
	}
	return allTrue(a + 1, n - 1);			// recursively progress to next string in array. update parameters
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
	if (n <= 0)
	{
		return 0;
	}
	if (somePredicate(a[0]) == false)
	{
		return 1 + countFalse(a + 1, n - 1);
	}
	return countFalse(a + 1, n - 1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
	if (n <= 0)								// zero elements in array
	{
		return -1;
	}
	if (somePredicate(a[0]) == false)		// if item in array false, return 0; 
	{
		return 0;
	}
	else
	{
		if (firstFalse(a + 1, n - 1) == -1)		// check if the recursion will return -1, if it does return -1, 
		{
			return -1;
		}
		return 1 + firstFalse(a + 1, n - 1);	// increment count and proceed
	} 
}

// Return the subscript of the least string in the array (i.e.,
// the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.
int indexOfLeast(const string a[], int n)
{
	if (n <= 0)								// no elements to examine
	{
		return -1;
	}
	if (n == 1)								// last element in array
	{
		return 0;
	}
	int i = 1 + indexOfLeast(a + 1, n - 1);	// at last element of array, the i it evalus a[0] <= a[i] should be 1
	if (a[0] <= a[i])						// meaning, the first items it checks are the last two sequential elements
	{										// if a[0] is smaller, it returns 0; if a[0] is larger, it returns 1.
		return 0;							// the proceeding i is now i= 1 or 0, if the i is larger, it increments
	}										// this is best explained with drawings...
	else
	{
		return i;
	}
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 > n1)
	{
		return false;
	}
	if (n2 == 0)
	{
		return true;
	}
	if (n1 == 0)
	{
		return false;
	}
	if (a2[0] == a1[0])
	{
		return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	}
	else
	{
		return includes(a1 + 1, n1 - 1, a2, n2);
	}
}



  /////////////////////
 //		MAIN		//
/////////////////////

int main()
{
	/////		TESTING METHODS		//////
	int n = 0, n1 = 0, n2 = 0;					// initialize n variables

	//	TESTING PREDICATE	//
	string a = "", b = "boy";
	assert(somePredicate(a) == true);			// tests the predicate, empty string returns true
	assert(somePredicate(b) == false);			// non empty string returns false

	// TESTING ALLTRUE	//
	string aTTest[5] = { "", "", "", "", "" };
	assert(allTrue(aTTest, n) == false);		// tests that if n <= 0, return false
	assert(somePredicate(aTTest[0]) == true);
	n = 5;
	assert(allTrue(aTTest, n) == true);			// in this case, predicate never returns false, therefore all true
	aTTest[3] = "broken";						// replaces the (3+1)th element with "broken" -> |""|""|""|"broken"|""|
	assert(allTrue(aTTest, n) == false);		// the predicate will return false at least once
	aTTest[0] = "broken";
	aTTest[1] = "broken";
	aTTest[2] = "broken";
	aTTest[4] = "broken";
	assert(allTrue(aTTest, n) == false);

	//	TESTING	COUNTFALSE	//
	string fF1[] = { "", "","", "","erase" };
	n = -4;
	assert(countFalse(fF1, n) == 0);				// since n <= 0, return 0.
	n = 5;
	assert(countFalse(fF1, n) == 1);				// correct n, countFalse should return 1
	string fF2[] = { "", "snap","", "","erase" };
	assert(countFalse(fF2, n) == 2);
	string fF3[] = { "kenny", "kyle","butters", "mintberrycrunch","erase" };
	assert(countFalse(fF3, n) == 5);
	string fF4[] = { "","","" };
	assert(countFalse(fF4, 3) == 0);

	// TESTING FIRSTFALSE	//
	assert(firstFalse(fF1, -3) == -1);			// n<=0, therefore return -1
	assert(firstFalse(fF4, 3) == -1);			// predicate never false, return -1
	assert(firstFalse(fF1, 5) == 4);			// predicate calls false on 4
	assert(firstFalse(fF2, 5) == 1);
	assert(firstFalse(fF3, 5) == 0);

	//	TESTING INDEXOFLEAST	//
	assert(indexOfLeast(fF1, 5) == 0);			// since first item is empty, it should proceed the rest
	assert(indexOfLeast(fF2, 5) == 0);			// two empty items, first encountered takes precedence
	assert(indexOfLeast(fF3, 5) == 2);			// butters is the least (alphabetically), at position 2

	// TESTING OF INCLUDES //
	string z1[] = { "a", "b", "c" };
	string z2[] = { "a" };
	assert(includes(z1, 3, z2, 1) == true);		// "a" is in z1
	assert(includes(z1, 1, z2, 3) == false);		// since n2 > n1, it will never be contained in n1, return false
	string y1[] = { "c", "a", "c" };
	string y2[] = { "a" };
	assert(includes(y1, 3, y2, 1) == true);		// "a" is in y1
	string x1[] = { "c", "b", "a" };
	string x2[] = { "a" };
	assert(includes(x1, 3, x2, 1) == true);		// "a" is in x1
	string w1[] = { "c", "b", "a" };
	string w2[] = { "r"};
	assert(includes(w1, 3, w2, 1) == false);	// "r" is not in w1
	string v1[] = { "c", "b", "a" };
	string v2[] = { "b", "a" };
	assert(includes(v1, 3, v2, 2) == true);		// v2 is in v1
	string u1[] = { "cat", "dog", "boy", "mouse", "cow" };
	string u2[] = { "cat", "boy","cow"};
	assert(includes(u1, 5, u2, 3) == true);		// u2 is in u1
	string t1[] = { "cat", "dog", "boy", "mouse", "cow" };
	string t2[] = { "cat", "cow","mouse" };
	assert(includes(t1, 5, t2, 3) == false);		// t2 is not in t1

}