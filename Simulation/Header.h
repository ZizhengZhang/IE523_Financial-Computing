/*
 *  IE 523: Financial Computing Assignment6
 *  Author: Zizheng Zhang
 *  Some hints are given by Prof. Sreenivas
 */
#ifndef ALICE_AND_BOB
#define ALICE_AND_BOB

#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

class I_have_nothing_apropos_for_this_class
{
private:
	double alice_probability, bob_probability;

	// pseudo random number
	// private member function: uniform RV generator
	double get_uniform()
	{
		// write the appropriate code here
		return (((double) rand()) / (pow(2.0, 31.0) - 1.0));
	}

	// private member function: nCi (i.e. n-take-i)
	long long int take(int n, int i)
	{
		// write a **RECURSIVE** implementation of n-take-i.
		// If you made it non-recurisive (i.e. n!/((n-i)!i!)) -- it
		// will take too long for large sizes
		if (i == 0 || n == i) {
			return 1;
		}
		else {
			return (((n - i + 1) * take(n, i - 1)) / i);
		}
	}

	// this routine implements the probability that Alice has more
	// heads than Bob after n-many coin tosses
	double theoretical_value(double q, double p, int n)
	{
		// implement equation 1.1 of Addona-Wagon-Wilf paper
		double probability_of_winning = 0;

		for (int r = 0; r < n; r++) {
			for (int s = r + 1; s <= n; s++) {
				probability_of_winning += take(n, s) * (pow(q, s)) * (pow((1 - q), (n - s))) * take(n, r) * (pow(p, r)) * (pow((1 - p), (n - r)));
			}
		}
		return probability_of_winning;
	}

public:
	vector <double> simulated_data;
	vector <double> theoretical_data;

	// public function:
	void set_probability(double alice_p, double bob_p)
	{
		alice_probability = alice_p;
		bob_probability = bob_p;
	}

	// probability of Alice winning the game.
	double simulated_value(int number_of_coin_tosses_in_each_game, int no_of_trials)
	{
		int no_of_wins_for_alice = 0;
		for (int i = 0; i < no_of_trials; i++)
		{
			int number_of_heads_for_alice = 0;
			int number_of_heads_for_bob = 0;
			for (int j = 0; j < number_of_coin_tosses_in_each_game; j++)
			{
				if (get_uniform() < alice_probability)
					number_of_heads_for_alice++;
				if (get_uniform() < bob_probability)
					number_of_heads_for_bob++;
			}
			if (number_of_heads_for_alice > number_of_heads_for_bob)
				no_of_wins_for_alice++;
		}
		return (((double)no_of_wins_for_alice) / ((double)no_of_trials));
	}

	/* Create the data file. 
	void create_data_file() {

		for (int i = 0; i < 60; i++) {
			theoretical_data.push_back(theoretical_value(alice_probability, bob_probability, i));
			simulated_data.push_back(simulated_value(i, 500000)); //here modify the no_of_trials
		}
		ofstream theoretical_file;
		theoretical_file.open("theoretical_data.txt");
		for (int i = 0; i < theoretical_data.size(); i++) {
			theoretical_file << theoretical_data[i] << endl;
		}

		ofstream simulated_file;
		simulated_file.open("simulated_data.txt");
		for (int i = 0; i < simulated_data.size(); i++) {
			simulated_file << simulated_data[i] << endl;
		}

		
	}
	*/

	int search_result()
	{
		// implememt a discrete-search procedure for the optimal n-value.
		// start with n = 1 and find the discrete-value of n that has
		// the largest probability for Alice winning.  Why would this work?
		// See Theorem 2.2 of the paper for the reason!
		int result = 0;
		for (int i = 1; i <= 100; i++) {
			if (((theoretical_value(alice_probability, bob_probability, i)) >= (theoretical_value(alice_probability, bob_probability, i - 1))) &&
				((theoretical_value(alice_probability, bob_probability, i)) >= (theoretical_value(alice_probability, bob_probability, i + 1))))
			{
				result = i;
				break;
			}
		}
		return result;
	}

};
#endif