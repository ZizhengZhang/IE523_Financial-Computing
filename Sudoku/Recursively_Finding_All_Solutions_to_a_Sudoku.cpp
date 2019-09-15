#include <iostream>
#include "Sudoku.h"

int main(int argc, char* argv[])
{
	Sudoku x;
	x.read_puzzle(argc, argv);
	cout << "Initilal";
	x.print_puzzle();
	cout << "----------------------" << endl;
	//x.Solve(0, 0);
	x.alternate_Solve(0, 0);
	cout << "Zizheng Zhang" << endl;
	cout << "NetID: zizheng2" << endl;
	//cout << "Final solution";
	//x.print_puzzle();

	return 0;
}

