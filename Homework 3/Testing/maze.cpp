#include <iostream>

using namespace std;


  /////////////////////////
 //		PATHEXISTS		//
/////////////////////////

bool pathExists(char maze[10][10], int sr, int sc, int er, int ec)
{
	// PSEUDO CODE:
	//	If the start location is equal to the ending location, then we've
	//		solved the maze, so return true.
	//		Mark the start location as visted.
	//		For each of the four directions,
	//		If the location one step in that direction(from the start
	//			location) is unvisited,
	//		then call pathExists starting from that location(and
	//			ending at the same ending location as in the
	//			current call).
	//		If that returned true,
	//		then return true.
	//		Return false.
	if (sr == er && sc == ec)
	{
		return true;
	}
	maze[sr][sc] = 'O';
	if (maze[sr - 1][sc] == '.' && pathExists(maze, sr - 1, sc, er, ec))
	{
		return true;
	}
	if (maze[sr][sc - 1] == '.' && pathExists(maze, sr, sc - 1, er, ec))
	{
		return true;
	}
	if (maze[sr + 1][sc] == '.' && pathExists(maze, sr + 1, sc, er, ec))
	{
		return true;
	}
	if (maze[sr][sc + 1] == '.' && pathExists(maze, sr, sc + 1, er, ec))
	{
		return true;
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

	char maze1[10][10] = {
	{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','.','X','.','.','X','.','.','.','X' },
	{ 'X','.','X','X','.','X','.','X','X','X' },
	{ 'X','.','.','.','.','X','.','X','.','X' },
	{ 'X','X','.','X','.','X','.','.','.','X' },
	{ 'X','X','X','.','.','X','.','X','.','X' },
	{ 'X','.','.','.','X','.','.','.','X','X' },
	{ 'X','.','X','X','.','.','X','.','X','X' },
	{ 'X','.','.','.','.','X','.','.','.','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' },
	};


	if (pathExists(maze1, 8, 6, 1, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;

	char maze2[10][10] = {
	{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','.','X','.','.','X','.','.','.','X' },
	{ 'X','.','X','X','.','X','.','X','X','X' },
	{ 'X','.','.','.','.','X','.','X','.','X' },
	{ 'X','X','.','X','.','X','.','.','.','X' },
	{ 'X','X','X','.','X','X','.','X','.','X' },
	{ 'X','.','.','.','X','.','.','.','X','X' },
	{ 'X','.','X','X','.','.','X','.','X','X' },
	{ 'X','.','.','.','.','X','.','.','.','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' },
	};

	if (pathExists(maze2, 8, 6, 1, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;

	char maze3[10][10] = {
	{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','X','.','.','.','.','.','X','X','X' },
	{ 'X','.','.','X','X','.','.','.','.','X' },
	{ 'X','.','.','.','X','.','.','.','X','X' },
	{ 'X','.','X','.','X','X','X','.','.','X' },
	{ 'X','X','X','X','.','.','X','.','.','X' },
	{ 'X','X','.','.','.','.','X','.','.','X' },
	{ 'X','.','.','.','.','.','.','.','X','X' },
	{ 'X','.','.','X','X','X','X','X','X','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' },
	};


	if (pathExists(maze3, 4, 3, 7, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;


	char maze4[10][10] = {
	{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','X','.','.','.','.','.','X','X','X' },
	{ 'X','.','.','X','X','.','.','.','.','X' },
	{ 'X','.','.','.','X','.','.','.','X','X' },
	{ 'X','.','X','.','X','X','X','.','.','X' },
	{ 'X','X','X','X','.','.','X','.','.','X' },
	{ 'X','X','.','.','.','.','X','.','.','X' },
	{ 'X','.','.','.','.','.','X','.','X','X' },
	{ 'X','.','.','X','X','X','X','X','X','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' },
	};

	if (pathExists(maze4, 4, 3, 7, 1))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;


}