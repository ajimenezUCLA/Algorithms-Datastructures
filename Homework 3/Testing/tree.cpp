#include <string>
#include <iostream>
#include <cassert>

using namespace std;

  /////////////////////////
 //		DESCRIPTION		//
/////////////////////////


  /////////////////////////////
 //		IMPLEMENTATIONS		//
/////////////////////////////


// DESCRIPTION: 
// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then for this value of a2            the function must return
//    "stan" "kenny" "cartman"                      1
//    "stan" "cartman" "butters"                    2
//    "kenny" "stan" "cartman"                      0
//    "kyle" "cartman" "butters"                    3

// NOTE: this search starts from end and works up
//		 this eliminates double counting
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
	// /*
	if (n2 <= 0)	// Base Case: "the empty sequence appears once"
	{
		return 1;
	}
	if (n1 < n2 )	// Base Case: if n2>n1, impossible for n2 to exist in n1
	{
		return 0;
	}
	int count = countIncludes(a1 + 1, n1 - 1, a2, n2);	// initalizes count to zero & takes us to the end
	if (a1[0] == a2[0])									// once we work to the beginning, count increments when appropriate 
	{
		count = count + countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);	// searches the rest after a positive match
	}
	return count;
	// */
	/*
	if (n2 <= 0)
		return 1;
	if (n1 < n2)
		return 0;

	// If we get here, a1 and a2 are nonempty
	int t = countIncludes(a1 + 1, n1 - 1, a2, n2);  // rest of a1, all of a2
	if (a1[0] == a2[0])
		t += countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);  // rest of a1, rest of a2
	return t;
	*/
}

// Exchange two strings
void exchange(string& x, string& y)
{
	string t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.

void separate(string a[], int n, string separator,
	int& firstNotLess, int& firstGreater)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
	//  Every element earlier than position firstNotLess is < separator
	//  Every element from position firstNotLess to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstGreater-1 is not known yet
	//  Every element at position firstGreater or later is > separator

	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > separator)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < separator)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
	if (n <= 1)		// base case: "If n <= 1, do nothing"
	{
		return;
	}
	// we have to utlize the seperate function
	// seperate takes in a string, its size, the first element, and two integer references
	
	// first create our integers
	//

	int firstNotLess;
	int firstGreater;
	// then call the seperate function.
	// NOTE: "Upon return, firstNotLess is set to the
    //		 index of the first element in the rearranged array that is
    //		 >= separator, or n if there is no such element, and firstGreater is
    //		 set to the index of the first element that is > separator"

	// essentially, we'll cycle through order, changing a[0], and calling seperate on it.


	separate(a, n, a[n/2], firstNotLess, firstGreater);
	
	// now we do the same to the other halves
	order (a, firstNotLess);	// this sorts the elements > seperator
	order(a + firstGreater, n - firstGreater);	// this sorts the elements < seperator
}


  ///////////////////////////
 ////		MAIN		////
///////////////////////////

int main()
{
	/////	TESTING COUNTINGINCLUDES	////

	// int countIncludes(const string a1[], int n1, const string a2[], int n2)
	// string a1[] = { "A","B","C","A","B","A" };
	// string a2[] = { "A","B" };
	string a1[] = { "AR","BR","AR","BR","CR","AR","BR" };
	string a2[] = { "AR","BR","CR" };
	// assert(countIncludes(a1, 6, a2, 2) == 2);
	cout << countIncludes(a1, 7, a2, 3) <<endl<<endl;

	string b1[] = { "stan","kyle","cartman","kenny","kyle","cartman","butters" };
	string b2[] = { "stan", "kyle" };
	cout << countIncludes(b1, 7, b2,2) <<endl<< endl;

	string c1[] = { "stan","kyle","cartman","kenny","kyle","cartman","butters" };
	string c2[] = { "stan", "kyle", "cartman" };
	cout << countIncludes(c1, 7, c2, 3) << endl << endl;

	cout << "*** SMALLBERG TEST ****" << endl;
	cout << "should output 1,2,0,3" << endl;

	string d1[] = { "stan","kyle","cartman","kenny","kyle","cartman","butters" };
	string d2[] = { "stan", "kenny", "cartman" };
	cout << countIncludes(d1, 7, d2, 3) << endl;

	string e1[] = { "stan","kyle","cartman","kenny","kyle","cartman","butters" };
	string e2[] = { "stan", "cartman", "butters" };
	cout << countIncludes(e1, 7, e2, 3) << endl;

	string f1[] = { "stan","kyle","cartman","kenny","kyle","cartman","butters" };
	string f2[] = { "kenny", "stan", "cartman" };
	cout << countIncludes(f1, 7, f2, 3) << endl;

	string g1[] = { "stan","kyle","cartman","kenny","kyle","cartman","butters" };
	string g2[] = { "kyle", "cartman", "butters" };
	cout << countIncludes(g1, 7, g2, 3) << endl;

	// void separate(string a[], int n, string separator, int& firstNotLess, int& firstGreater)

	// void order(string a[], int n)


	////	TESTING ORDER	////

	string dog[] = { "woof","bark","cough","drink","growl","yelp","sneeze" };
	for (int i = 0; i < 7; i++)
	{
		cout << dog[i] << ", ";
	}
	cout << endl;
	order(dog, 7);
	for (int i = 0; i < 7; i++)
	{
		cout << dog[i] << ", ";
	}
	cout << endl;

	string abcs[] = { "A","G","D","C","E","F","B","C","T","C","C"};
	for (int i = 0; i < 11; i++)
	{
		cout << abcs[i] << ", ";
	}
	cout << endl;
	order(abcs, 11);
	for (int i = 0; i < 11; i++)
	{
		cout << abcs[i] << ", ";
	}
	cout << endl;



}

