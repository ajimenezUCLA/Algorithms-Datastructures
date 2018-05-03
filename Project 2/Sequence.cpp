#include "Sequence.h"

#include <iostream>

using namespace std;


/*
int main()
{

}
*/

Sequence::Sequence()	// Constructor
{
	// FUNCTION: Create an empty sequence (i.e., one with no items)
	// we want to create an empty linked list sequence
	// PSEUDO CODE:
	// - set size to 0
	// - create dummy node pointing to self
	m_size = 0;
	head = new Node;
	head->next = head;
	head->prev = head;
}

Sequence::~Sequence()				// Destructor
{
	// FUNCTION: When a Sequence is destroyed, the nodes in the linked list must be deallocated.
	// PSEUDO CODE:
	// - loop through the nodes, do not delete the head node, we need it to delete the rest.
	// - create a node pointer as a place holder for node deletion process.
	// - using our node pointer, looking into our node to be deleted, go to the before that, and update its next pointer to head.
	//		i.e., curr -> prev -> next ( so now we're looking at the next ptr for the previous node of curr, then change that to head.
	// - change sentinel (head) node previous pointer so that it points node that curr node's previous pointer pointed to. 
	//		in this way, our circular doubly linked list is no longer dependent on node curr, thus we can delete it.
	// - delete current node.
	// - once our loop condition is met (we've deleted all nodes and now have head left), exit loop
	// - delete sentinal (head node)

	while (head->next != head)		// we're looking for the case where the head pointer isn't pointing to itself, we can easily use m_prev instead
	{
		Node* curr = head->prev;	// create a pointer called curr, make it point to the item before head.
		curr->prev->next = head;	// slightly confusing, but we're changing the next pointer of the node previous to curr so that it redirects to head.
									// we do this because curr is the node before head and since we're deleting it, we need to accomdate the new pointers.
		head->prev = curr->prev;	// make head's prev pointer point to the previous that curr's prev pointer points to, thus completing the loop
		delete curr;				// delete our pointer, i guess we could have placed this outside of the loop
	}
	delete head;					// delete the sentinel node.
}

Sequence& Sequence::operator=(const Sequence& rhs)		// Assignment operator
{
	// FUNCTION: When an existing Sequence(the left - hand side) is assigned
	//			 the value of another Sequence(the right - hand side), the
	//			 result must be that the left - hand side object is a duplicate
	//			 of the right - hand side object, with no memory leak of list
	//			 nodes(i.e.no list node from the old value of the left - hand
	//			 side should be still allocated yet inaccessible).
	// PSEUDO CODE:
	// - if condition: not same address
	//		- create temporary sequence from passed item
	//		- call swap function
	// - return current object

	if (this!= &rhs)	// alias check
	{
		Sequence temp(rhs);
		swap(temp);
	}
	return *this;
}



Sequence::Sequence(const Sequence& other)		// Copy constructor
{
	// FUNCTION: When a brand new Sequence is created as a copy of an
	//			 existing Sequence, enough new nodes must be allocated to
	//			 hold a duplicate of the original list.
	// PSEUDO CODE:
	// - set size to 0
	// - create dummy node, pointing to self
	// - use a loop to copy and create each node.
	//		two possible implementations, using m_size. and incrementing 
	//		or using a condition such as ptr != head, (best practice)
	//			LOOP: create a node pointer and assign it to a new node.
	//			assign the value data to the copy node from the passed node
	//			 
	//			
	// - update size of linked list
	m_size = other.m_size;			// initalize m_size, not necessary

	head = new Node;	// create dummy node
	head->next = head;
	head->prev = head; 

	for (Node* curr = other.head->next; curr != other.head; curr = curr->next)
	{
		// for loop explained:
		// Node* curr = other.head->next; /// create a node pointer and point it to the 'next' node of the head node of the linked list we're copying.
		// curr != other.head;	/// continue until you reach the copied linked list's head node
		// curr = curr->next	/// proceed to the next node 

		Node* copyNode = new Node;			// create a pointer and direct it a new Node.
		copyNode->m_value = curr->m_value;	// assign the value inside our original list into our new list.
		copyNode->next = head;				// assign the next pointer to head, since its the new end node
		copyNode->prev = head->prev;		// assign new end node prev ptr to point to the old end node
		head->prev->next = copyNode;		// assigning the previous old end node's next ptr to the new end node (copyNode)
		head->prev = copyNode;				// assign the head prev ptr to the new end node (copyMode)
	}
}



bool Sequence::empty() const
{
	// FUNCTION: Return true if the sequence is empty, otherwise false.
	// PSEUDO CODE:
	// - check member variable size is equal to zero
	// - return true if boolean is true, false other.
	// NOTE: Simpler implementation return (m_size == 0);
	/*
	if (m_size == 0)
	{
		return true;
	}
	return false;
	*/
	return (m_size == 0);
}

int Sequence::size() const
{
	// FUNCTION: Return the number of items in the sequence.
	// PSUEDO CODE:
	// - return the member variable for size
	return m_size;
}

bool Sequence::insert(int pos, const ItemType& value)
{
	// FUNCTION: Insert value into the sequence so that it becomes the item at
	//			 position pos.  The original item at position pos and those that
	//			 follow it end up at positions one higher than they were at before.
	//			 Return true if 0 <= pos <= size() and the value could be
	//			 inserted.  (It might not be, if the sequence has a fixed capacity,
	//			 e.g., because it's implemented using a fixed-size array.)  Otherwise,
	//			 leave the sequence unchanged and return false.  Notice that
	//			 if pos is equal to size(), the value is inserted at the end.
	// PSEUDO CODE:
	// - if statement to catch invalid cases (position less than 0 or greater than linked list size)... return false
	//		although, because of my circularly linked list implmentation, this wouldn't cause problems since it will eventually land on a node.
	// - create a Node pointer and assign it to the 'first real node' in our list, (i.e., the node our dummy's next points to)
	// - for loop with middle condition being i < pos... in this case, we arrive just before the position and we use this to our advantage
	//		in our for loop, our newly created node pointer will move through the linked list
	//		CAUTION: since we're using a dummy node (to assist us in special cases) we must be careful about which Node is at position "0"	
	// - create our new insertion Node and pointer
	// - implement at given position
	// - increment member size varable
	// - return true;

	if (pos < 0 || pos > size())		// if a bad case is presented, return false
	{
		return false;
	}
	Node* curr = head->next;			// create a Node pointer, call it curr and point it to the 'first real node'
	for (int i = 0; i < pos; i++)		// go through for loop, pushing the curr pointer until we get to the desired position
	{
		curr = curr->next;				// this reassigns the curr pointer into the following node
	}
	Node* insertionNode = new Node;		// create a new node with a pointer to it
	insertionNode->m_value = value;		// assign the node data to the passed value
	insertionNode->prev = curr->prev;	// connect the new node's prev ptr to the node before it using the current node
	insertionNode->next = curr;			// connect the new node's next ptr to the curr node
	curr->prev->next = insertionNode;	// connect the next ptr for the node at pos-1 to the new node
	curr->prev = insertionNode;			// connect the prev ptr for curr node (previously at pos) to the new node.
	m_size++;							// increment the member variable storing the size value
	return true;						// return true, insertion successful 
}

int Sequence::insert(const ItemType& value)
{
	// FUNCTION: Let p be the smallest integer such that value <= the item at
	//			 position p in the sequence; if no such item exists (i.e.,
	//			 value > all items in the sequence), let p be size().  Insert
	//			 value into the sequence so that it becomes the item at position
	// 			 p.  The original item at position p and those that follow it end
	// 			 up at positions one higher than before.  Return p if the value
	// 			 was actually inserted.  Return -1 if the value was not inserted
	// 			 (perhaps because the sequence has a fixed capacity and is full).
	// PSEUDO CODE:
	// - create an int to keep count
	// - create a node pointer to use so we can view the data held in each node of our linked list
	// - loop through the linked list, starting at the item after the head, 
	// - in the loop, compare the value to the data value held in the node.
	// - increment count and move pointer with each iteration of loop if condition not met.
	// - if condition met, break from loop, return count

	int count = 0;						// create a variable to store our count (position)
	Node * curr = head->next;			// temporary node pointer, pointing to our first 'real' node
	while (curr != head)			// instead of using m_size, we can go through the entire linked list until we return back to head.
	{	
		if (value <= curr->m_value)		// during the iteration, if at any time we meet the condition, break loop 
		{
			break;
		}
		curr = curr->next;				// if condition not met, update curr pointer to next node and increment count
		count++;
	}
	insert(count, value);				// pass into our previous insert function the count (pos) and value
	return count;						// return count
}

bool Sequence::erase(int pos)
{
	// FUNCTION: If 0 <= pos < size(), remove the item at position pos from
	//			 the sequence (so that all items that followed that item end up at
	//			 positions one lower than they were at before), and return true.
	//			 Otherwise, leave the sequence unchanged and return false.
	// PSEUDO CODE:
	// - if statement to catch good case ( 0 <= pos < size() )
	// - use a for loop to cycle through the linked list,
	// - properly delete node
	// - return true;
	// - else, return false;

	if (pos >= 0 && pos < size())		// bad case catcher
	{
		Node* curr = head->next;		// node pointer for cycling through linked list
		for (int i = 0; i < pos; i++)	// loop for getting to appropriate position
		{
			curr = curr->next;		
		}
		curr->prev->next = curr->next;	// the node pos-1 connected to node pos+1
		curr->next->prev = curr->prev;	// the node pos+1 connected to node pos-1
		delete curr;					// node curr has been disconnected and can be deleted
		m_size--;						// decrease recorded linked list size	
		return true;
	}
	return false;
}

int Sequence::remove(const ItemType& value)
{
	// FUNCTION: Erase all items from the sequence that == value.  Return the
	//			 number of items removed (which will be 0 if no item == value).
	// PSEUDO CODE:
	// - create count variable to track items removed
	// - create pointer variable to access node data
	// - loop through linked list 
	//		if statement parameter comparing the data stored to the value, if equivalent, run erase.
	//		increment count of item deleted
	//		proceed through loop until head is reached
	// - return count

	int rCount = 0;	// variable to keep track of items removed
	Node* curr = head->next;		// node pointer to cycle through linked list
	while (curr != head)			// escape condition for circular doubly linked list
	{
		if (curr->m_value == value)
		{
			Node* nodeKiller = curr;
			curr = nodeKiller->prev;
			nodeKiller->next->prev = curr;
			curr->next = nodeKiller->next;
			delete nodeKiller;
			m_size--;
			rCount++;
		}
		curr = curr->next;
	}
	return rCount;
}

bool Sequence::get(int pos, ItemType& value) const
{
	// Function: If 0 <= pos < size(), copy into value the item at position pos
	//			 in the sequence and return true.  Otherwise, leave value unchanged
	//			 and return false.
	// PSEUDO CODE: 
	// if statement to catch good cases
	//		create node pointer to cycle through code
	//		for loop to reach appropriate position
	//			increment pointer location
	//		copy value at position into member data
	//		return true
	// return false

	if (0 <= pos && pos < size())		// goood case catch, otherwise return false
	{
		Node* curr = head->next;		// node pointer for cycling through linked list
		for (int i = 0; i < pos; i++)	// for loop takes us to position
		{
			curr = curr->next;
		}
		value = curr->m_value;			// copy member value
		return true;
	}
	return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
	// FUNCTION: If 0 <= pos < size(), replace the item at position pos in the
	//			 sequence with value and return true.  Otherwise, leave the sequence
	//			 unchanged and return false.
	// PSEUDO CODE:
	// if statement to catch good case
	//	 Node pointer to cycle through linked list
	//	 for loop to get to desired position in linked list
	//		update node next pointer
	//	assign member data to value	

	if (0 <= pos && pos < size())
	{
		Node* curr = head->next;
		for (int i = 0; i < pos; i++)
		{
			curr = curr->next;
		}
		curr->m_value = value;
		return true;
	}
	return false;
}

int Sequence::find(const ItemType& value) const
{
	// FUNCTION: Let p be the smallest integer such that value == the item at
	//			 position p in the sequence; if no such item exists, let p be -1.
	//			 Return p.
	// PSEUDO CODE:
	// - initialize p, set to zero
	// - create node to traverse linked list
	// - while loop to circulate the linked list
	//		- if statement to catch equivalence condition
	//			- return p;
	//		- update curr position
	//		- increment position variable
	// - return -1 if while loop changes nothing

	int p = 0;
	Node* curr = head->next;
	while (curr != head)
	{
		if (value == curr->m_value)
		{
			return p;
		}
		p++;
		curr = curr->next;
	}
	return -1;
}

void Sequence::swap(Sequence& other)
{
	// FUNCTION: Exchange the contents of this sequence with the other one.
	// PSEUDO CODE:
	// - create a temporary node pointer, assign to LL1
	// - reassign LL1 head to LL2 head
	// - reassign LL2 head to temp head (LL1)
	// - create temporary size variable, assign it LL1 size
	// assign LL1 size to LL2 size
	// Assign LL2 size to temp Size

	Node* tempHead = other.head;	// temporary pointer
	other.head = head;				// swap "algorithm"
	head = tempHead;

	int tempSize = other.m_size;	// temporary size variable
	other.m_size = m_size;			// swap "algorithm"
	m_size = tempSize;
	// size is a strange looking word.
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	// FUNCTION: Consider all the items in seq2; let's call them seq20, seq21, ..., seq2n. If there exists at least
	//			 one k such that seq1k == seq20 and seq1k+1 == seq21 and ... and seq1k+n == seq2n, and k+n < seq1.size(),
	//			 then this function returns the smallest such k. (In other words, if seq2 is a consecutive subsequence of seq1,
	//			 the function returns the earliest place in seq1 where that subsequence starts.) If no such k exists or if seq2
	//			 is empty, the function returns -1. 
	// PSEUDO CODE:
	// - if statement: bad size parameters (
	//		- return -1
	// - for loop: exit condition, i reaches the size of sequence 1.
	//		- temporary place holder for our ItemType
	//		- use get to get the value of the 0th item in seq 2,
	//		- use get to obtain the value of the ith item in seq 1,
	//		- create variable to store start position of subseq
	//		- if statement: compare seq1 and seq2 values 
	//			- compounded for loop, update multiple variables
	//				- bool subseq variable defaulted to true
	//				- get next value in seq1
	//				- get next value in seq 2
	//				- if condition: values are different
	//					- update bool subseq to false, break loop.
	//			- if condition: subseq (if its true, will proceed)
	//				- return kStartPos
	//	- return -1; cycled through linked list, condition unmet

	if (seq2.empty() || seq1.size() < seq2.size())	// catches bad cases, faster for computation
	{
		return -1;
	}
	for (int i = 0; i < seq1.size() ; i++)
	{
		ItemType seq1Val;
		ItemType seq2Val;
		seq1.get(i, seq1Val);
		seq2.get(0, seq2Val);
		if (seq1Val == seq2Val)
		{
			bool subSeq = true;
			int kStartPos = i;		// has to be created outside of for loop because we return it later
			for (int x = 0, kPrime = i; x < seq2.size(); x++, kPrime++)
			{
				seq1.get(kPrime, seq1Val);
				seq2.get(x, seq1Val); 
				if (seq1Val != seq2Val)
				{
					subSeq = false;
					break;	// exit the for loop
				}

			}
			if (subSeq)
			{
				return kStartPos;
			}
		}
	}
	return -1;	// subsequence not found
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	Sequence returnResult;
	if (seq1.empty())
	{
		result = seq2;
	}
	if (seq2.empty())
	{
		result = seq1;
	}
	int shortLength, maxLength;
	if (seq1.size() < seq2.size())
	{
		shortLength = seq1.size();
		maxLength = seq2.size();
	}
	else
	{
		shortLength = seq2.size();
		maxLength = seq1.size();
	}
	ItemType val1;
	ItemType val2;
	for (int i = 0; i < shortLength*2; i+=2)
	{
		if (seq1.get(i, val1) == true)
		{
			returnResult.insert(i, val1);
		}
		if (seq2.get(i, val2) == true)
		{
			returnResult.insert(i + 1, val2);
		}
	}
	int k = returnResult.size();
	for (int i = shortLength; i < maxLength; i++)
	{
		if (seq1.size() < seq2.size())
		{
			if (seq2.get(i, val2) == true)
			{
				returnResult.insert(k, val2);
			}
		}
		else
		{
			if (seq1.get(i, val1) == true)
			{
				returnResult.insert(k, val1);
			}
		}
		k++;
	}
	result = returnResult;
}



void Sequence::dump() const {
	Node* p = head->next;
	while (p != head) { // condition to exit loop for circular DLL
		std::cerr << p->m_value << std::endl;
		p = p->next;	// update Node pointer
	}

	//print size
	std::cerr << m_size << std::endl;
}

/*
Resources:
http://www.cs.dartmouth.edu/~scot/cs10/lectures/6/6.html
http://web.eecs.utk.edu/~bvz/teaching/cs140Fa09/notes/Dllists/
https://www.geeksforgeeks.org/copy-constructor-in-cpp/
https://www.geeksforgeeks.org/doubly-circular-linked-list-set-1-introduction-and-insertion/
http://www.cs.uwm.edu/faculty/boyland/classes-archive/fa15.cs351/www/linked-list-variations.html
*/