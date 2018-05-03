// Homework 2
// Part 1

#include <iostream>
#include <stack>

// REFERENCE MATERIAL
//	stack<Coord> coordStack;     // declare a stack of Coords
//	Coord a(5,6);
//	coordStack.push(a);          // push the coordinate (5,6)
//	coordStack.push(Coord(3,4)); // push the coordinate (3,4)
//	...
//	Coord b = coordStack.top();  // look at top item in the stack
//	coordStack.pop();            // remove the top item from stack
//	if (coordStack.empty())      // Is the stack empty?
//	cout << "empty!" << endl;
//	cout << coordStack.size() << endl;  // num of elements

using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(char maze[10][10], int sr, int sc, int er, int ec)
{
// FUNCTION: 
//		Return true if there is a path from (sr,sc) to (er,ec)
//			through the maze; return false otherwise
// PSEUDO CODE:
//	Push the starting coordinate(sr, sc) onto the coordinate stack and
//		update maze[sr][sc] to indicate that the algorithm has encountered
//		it(i.e., set maze[sr][sc] to have a value other than '.').
//		While the stack is not empty,
//	{ Pop the top coordinate off the stack.This gives you the current
//	(r,c) location that your algorithm is exploring.
//		If the current(r,c) coordinate is equal to the ending coordinate,
//		then we've solved the maze so return true! 
//		Check each place you can move from the current cell as follows :
//	If you can move NORTH and haven't encountered that cell yet,
//		then push the coordinate(r - 1,c) onto the stack and update
//		maze[r - 1][c] to indicate the algorithm has encountered it.
//		If you can move WEST and haven't encountered that cell yet,
//		then push the coordinate(r,c - 1) onto the stack and update
//		maze[r][c - 1] to indicate the algorithm has encountered it.
//		If you can move SOUTH and haven't encountered that cell yet,
//		then push the coordinate(r + 1,c) onto the stack and update
//		maze[r + 1][c] to indicate the algorithm has encountered it.
//		If you can move EAST and haven't encountered that cell yet,
//		then push the coordinate(r,c + 1) onto the stack and update
//		maze[r][c + 1] to indicate the algorithm has encountered it.
//	}
//		There was no solution, so return false
	stack <Coord> coordStack;
	Coord startPos(sr,sc);
	Coord endPos(er, ec);
	coordStack.push(startPos);
	maze[sr][sc] = 'O';
	// int k = 1;
	while (coordStack.empty() == false)
	{
		Coord curr = coordStack.top();
		coordStack.pop();
		maze[curr.r()][curr.c()] = 'O';
		/*
		// use this code to view the map and get the current iteration 
		cout << "Itertion # " << k << endl;
		k++;
		cout << "current coord is: (" << curr.r() << " , " << curr.c() << ")"<< endl;
		for (int r = 0; r < 10; r++)
		{
			for (int c = 0; c < 10; c++)
			{
				cout << maze[r][c];
			}
			cout << endl;
		}
		cout << endl;
		// */
		if (curr.r() == er && curr.c() == ec)
		{
			return true;
		}
		if (maze[curr.r() - 1][curr.c()] != 'X' && maze[curr.r() - 1][curr.c()] != 'O')	// check NORTH
		{
			coordStack.push(Coord(curr.r()-1, curr.c() ));
		}
		if (maze[curr.r()][curr.c()-1] != 'X' && maze[curr.r()][curr.c() - 1] != 'O')	// check WEST
		{
			coordStack.push(Coord(curr.r(), curr.c()-1 ));
		}
		if (maze[curr.r()+1][curr.c()] != 'X' && maze[curr.r()+1][curr.c()] != 'O')	// check SOUTH
		{
			coordStack.push(Coord(curr.r()+1, curr.c() ));
		}
		if (maze[curr.r()][curr.c() + 1] != 'X' && maze[curr.r()][curr.c() + 1] != 'O')	// check EAST
		{
			coordStack.push(Coord(curr.r(), curr.c() + 1 ));
		}
	}
	return false;
}

int main()
{
	char maze[10][10] = {
	{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','.','.','.','.','.','.','.','.','X' },
	{ 'X','X','X','X','X','.','X','.','X','X' },
	{ 'X','.','.','.','X','.','X','.','.','X' },
	{ 'X','.','X','.','.','.','X','.','.','X' },
	{ 'X','.','X','X','X','.','X','X','X','X' },
	{ 'X','X','X','.','.','.','.','X','.','X' },
	{ 'X','.','X','X','.','X','X','X','.','X' },
	{ 'X','.','.','.','.','X','.','.','.','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 6, 5, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}