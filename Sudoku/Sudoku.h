/*
 *  sudoku.h
 *  Sudoku
 *  Some parts are created by Prof. Ramavarapu Sreenivas
 *  Inspired by: http://web.eecs.utk.edu/courses/spring2012/cs140/Notes/Sudoku/index.html
*/

#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include <iostream>
using std::vector;
using namespace std;

class Sudoku
{
	// Private
	int puzzle[9][9];

	bool check_row_valid(int row, int num)  // Check if a number is already in a row
	{
		for (int c = 0; c < 9; c++)
		{
			if (num != 0 && puzzle[row][c] == num)
				return false;              // If the row already have the number, return false
		}
		return true;
	}

	bool check_col_valid(int col, int num)  // Check if a number is already in a col
	{
		for (int r = 0; r < 9; r++)
		{
			if (num != 0 && puzzle[r][col] == num)
				return false;              // If the column already have the number, return false
		}
		return true;
	}

	bool check_block_valid(int blockRow, int blockCol, int num)  // Check if a number is already in a 3X3 block
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (puzzle[i + blockRow][j + blockCol] == num)
					return false;
			}
		}
		return true;
	}

	bool check_entry(int row, int col, int num)  // Check if a number can be placed on an entry
	{
		if (check_row_valid(row, num))
			if (check_col_valid(col, num))
			{
				int blockRow = row - row % 3;
				int blockCol = col - col % 3;
				if (check_block_valid(blockRow, blockCol, num))
					return true;
			}
		return false;
	}

	bool find_next_empty(int& row, int& col)  // Find next puzzle[row][col] == 0
	{
		for (row = 0; row < 9; row++)
			for (col = 0; col < 9; col++)
				if (puzzle[row][col] == 0)
					return true;
		return false;
	}

public:
	// Public member function that reads the incomplete puzzle
	// we are not doing any checks on the input puzzle -- that is,
	// we are assuming they are indeed valid

	int n = 0;

	void read_puzzle(int argc, char* argv[])
	{
		ifstream input_file(argv[1]);

		if (input_file.is_open()) // If "Data.txt" exists in the local directory
		{
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
					input_file >> puzzle[i][j];
			input_file.close();
		}
		else
			cout << "Input file " << argv[1] << " does not exist in PWD" << endl;
	}

	// Public member function that prints the puzzle when called
	void print_puzzle()
	{
		cout << std::endl << "Board Position" << std::endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				// check if we have a legitimate integer between 1 and 9
				if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
				{
					// printing initial value of the puzzle with some formatting
					cout << puzzle[i][j] << " ";
				}
				else {
					// printing initial value of the puzzle with some formatting
					cout << "X ";
				}
			}
			cout << std::endl;
		}
	}

	// Public member function that (recursively) implements the brute-force 
	// search for possible solutions to the incomplete Sudoku puzzle
	bool Solve(int row, int col)  // This is for part 1. Only try to find one solution.
	{
		// this part of the code identifies the row and col number of the 
		// first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
		// no zeros, the variable row will be 9 => the puzzle is done, as 
		// each entry is row-, col- and block-valid...

		// int row, col;
		if (find_next_empty(row, col))  // Find next empty entry. If cannot, then the problem has been solved
		{
			for (int num = 1; num <= 9; num++)
			{
				if (check_entry(row, col, num))
				{
					puzzle[row][col] = num;
					if (Solve(row, col))  // Recursive
						return true;
					puzzle[row][col] = 0;
				}
			}
			return false; 
		}
		else
			return true; 

	}

	bool alternate_Solve(int row, int col)  // This is for part 2. Trying to find all solutions.
	{
		if (!find_next_empty(row, col))
		{
			cout << endl;
			cout << "Solution #" << n + 1 << " : ";
			print_puzzle();
			n++;
			return true;
		}

		for (int k = 1; k <= 9; k++)
		{
			if (check_entry(row, col, k))
			{
				puzzle[row][col] = k;
				alternate_Solve(row, col);
				puzzle[row][col] = 0;
			}
		}
		return true;
	}

};

#endif

