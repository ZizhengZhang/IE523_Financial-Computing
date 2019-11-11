#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <time.h>
#include "newmatap.h"           
#include "newmat.h"
#include "newmatio.h"

using namespace std;

Matrix repeated_squaring(Matrix A, int exponent, int no_rows) {
	Matrix B = IdentityMatrix(no_rows);
	if (exponent == 0) {
		return B;
	}
	if (exponent % 2 == 1) {
		return A * repeated_squaring(A * A, (exponent - 1) / 2, no_rows);
	}
	else {
		return repeated_squaring(A * A, exponent / 2, no_rows);
	}
}

Matrix bruteforce(Matrix A, int exponent, int no_rows) {
	Matrix C = A;
	for (int i = 1; i < exponent; i++) {
		C = A * C;
	}
	return C;
}

double random_interval(int range)
{
	double num = (((double)rand()) / RAND_MAX);
	if (num < 0.5) { return -1 * range * num; }
	if (num >= 0.5) { return range * num; }
	//return 0;
}

Matrix initialize(int size) {
	Matrix A(size, size);
	for (int i = 1; i <= A.Nrows(); i++) {
		for (int j = 1; j <= A.Nrows(); j++) {
			A(i, j) = random_interval(5);
		}
	}
	return A;
}

int main(int argc, char* const argv[])
{

	int exponent, size;
	sscanf_s(argv[1], "%d", &exponent);
	sscanf_s(argv[2], "%d", &size);

	cout << "The number of rows/columns in the square matrix is: " << size << endl;
	cout << "The exponent is: " << exponent << endl;

	Matrix randA = initialize(size);
	//cout << randA << endl;

	clock_t time_before1 = clock();
	Matrix repeated_squaring_result = repeated_squaring(randA, exponent, size);
	clock_t time_after1 = clock();
	double diff1 = ((double)time_after1 - (double)time_before1);
	cout << "Repeated squaring result: " << endl;
	cout << "It took " << setprecision(7) << diff1 / CLOCKS_PER_SEC << " seconds to complete " << endl;
	//cout << repeated_squaring_result << endl;


	clock_t time_before2 = clock();
	Matrix bruteforce_result = bruteforce(randA, exponent, size);
	clock_t time_after2 = clock();
	double diff2 = ((double)time_after2 - (double)time_before2);
	cout << "Direct multiplication result: " << endl;
	cout << "It took " << setprecision(7) << diff2 / CLOCKS_PER_SEC << " seconds to complete " << endl;
	//cout << bruteforce_result << endl;

	int nn = 1000;
	vector <double> repeated_sqr_time, direct_time;
	for (int i = 1; i <= nn; i++) {


		clock_t t1 = clock();
		Matrix result_rptsqr = repeated_squaring(randA, i, size);
		clock_t t2 = clock();
		double diff_rptsqr = ((double)t2 - (double)t1);
		double time_used_rptsqr = (diff_rptsqr) / CLOCKS_PER_SEC;
		//cout << before_rptsqr << endl;
		//cout << diff_rptsqr << endl;
		//printf("It took me (%f seconds).\n", before_rptsqr, ((float)before_rptsqr) / CLOCKS_PER_SEC);
		repeated_sqr_time.push_back(time_used_rptsqr);
	}

	for (int i = 1; i <= nn; i++) {
		double before_dir = clock();
		Matrix result_dir = bruteforce(randA, i, size);
		double after_dir = clock();
		double diff_dir = ((double)after_dir - (double)before_dir);
		double time_used_dir = diff_dir / CLOCKS_PER_SEC;
		//cout << time_used_dir << endl;
		direct_time.push_back(time_used_dir);
	}

	ofstream outf("repeated_sqr_time");
	for (int i = 0; i < nn; i++) {
		outf << repeated_sqr_time[i] << endl;
		//cout << repeated_sqr_time[i] << endl;
	}
	ofstream outf1("direct_time");
	for (int i = 0; i < nn; i++) {
		outf1 << direct_time[i] << endl;
		//cout << direct_time[i] << endl;
	}
	return 0;
}
