// IE523 Financial Computing, Assignment 1 : Finding solutions to the N-Queens Problem.
// Author: Zizheng Zhang


// This solution doesn't use a pointer-to-pointer to create a 2D array. 
// Instead, I create a 1D array, chess_board, only storing the location of the queen of every row.
// For example, if chess_board[2] == 1, that means a queen can be placed on row 2, column 1.
// Compared with 2D array solutions, this solution can save more memory space.
// And I'm used to Python, so C++ OOP is a little confusing... I'll keep learning.


#include<iostream>
#include<vector>
using namespace std;

bool is_this_place_safe(int* chess_board, int i, int j)  // Judging if a queen can be placed on row i, col j.
{
	for (int k = 0; k < i; k++)
		if (j == chess_board[k] || abs(chess_board[k] - j) == abs(i - k))  // Some limits that prevent a queen from being placed on row i, col j
			return false;
	return true;
}

void print_board(int* chess_board, int n)  // Print the whole chess board
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (chess_board[i] == j)
				cout << 1 << " ";  // 1 represents a queen
			else
				cout << 0 << " ";  // 0 represent nothing
		}
		cout << endl;
	}
	cout << endl;
}

int check(int i, int* chess_board, int n) 
{
	int num = 0;  // Store the number of solutions.
	
	if (i == n)  // Aftering checking all rows, this solution succeeds.
	{
		print_board(chess_board, n);  // Print this solution.
		return 1;
	}

	for (int j = 0; j < n; j++) 
	{  
		if (is_this_place_safe(chess_board, i, j)) 
		{ 
			chess_board[i] = j;
			num += check(i + 1, chess_board, n);  // Recursive to check next row.
		}
	}
	return num;
}

int solutions_count(int n)  // Counting how many solutions are there for a N-Queens Problem.
{
	if (n < 1)
		return 0;
	int* chess_board = new int[n]; // initiate a 1D array to record queens' locations.
	int num = check(0, chess_board, n);  // Starting from row 0.

	delete[] chess_board; 
	return num;

}
int main() 
{
	cout << "Please enter the size of the chess board (also the number of queens): ";
	int n;
	cin >> n;
	cout << "For " << n << "-Queens Problem," << "There are " << solutions_count(n) << " different kinds of solution." << endl;
	return 0;
}
