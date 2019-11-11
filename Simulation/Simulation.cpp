/*
 *  IE 523: Financial Computing Assignment6
 *  Author: Zizheng Zhang
 *  Some hints are given by Prof. Sreenivas
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "Header.h"

using namespace std;

int main(int argc, char* argv[])
{
	I_have_nothing_apropos_for_this_class x;
	double alice_success_prob, bob_success_prob;
	sscanf_s(argv[1], "%lf", &alice_success_prob);
	sscanf_s(argv[2], "%lf", &bob_success_prob);

	cout << "Probability of success for Alice = " << alice_success_prob << endl;
	cout << "Probability of success for Bob = " << bob_success_prob << endl;
	
	clock_t start_time = clock();

	x.set_probability(alice_success_prob, bob_success_prob);

	int optimal = x.search_result();

	clock_t end_time = clock();

	if (optimal > 0)
		cout << "The optimal number of coin tosses in each game is " << optimal << endl;
	else {
		cout << "The optimal number of coin tosses in each game exceeds 100... Quitting" << endl;
	}
	cout << "Running time for repeating square algorithm: " << ((double)end_time - (double)start_time) / CLOCKS_PER_SEC << " s" << endl;

	//create the data file
	//x.create_data_file();
}
