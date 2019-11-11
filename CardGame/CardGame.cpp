// Author: Zizheng Zhang, netID: zizheng2
// IE 523 Financial Computing Assignment 5
// Some hints are given by Professor Sreenivas


#include <iostream>
#include <fstream>
#include "CardGame.h"

using namespace std;

int main(int argc, char* const argv[])
{
	int total_number_of_cards;
	double** mem;

	sscanf_s(argv[1], "%d", &total_number_of_cards);

	// use a double pointer to store the result, every time calculate the value
	// avoid repeated calculations and use it directly
	mem = new double* [total_number_of_cards / 2 + 1];

	for (int i = 0; i <= total_number_of_cards / 2; i++)
		mem[i] = new double[total_number_of_cards / 2];

	for (int i = 0; i <= total_number_of_cards / 2; i++)
		for (int j = 0; j <= total_number_of_cards / 2; j++)
			mem[i][j] = -1;
		

	cout << "Total Number of Cards = " << total_number_of_cards << endl;

	cout << "Value of the game = " << value(total_number_of_cards / 2, total_number_of_cards / 2, mem) << endl;

	free(mem);

	return 0;

}
