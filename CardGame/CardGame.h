#ifndef	CARDGAME_H
#define CARDGAME_H
#include <algorithm>

using namespace std;

double value(int r, int b, double** mem)
{

	if (0 == r)
		return ((double)b);
	if (0 == b)
		return (0);

	if (mem[r][b] == -1)

	{
		double draw_r = ((double)r / (r + b)) * value(r - 1, b, mem);

		double draw_b = ((double)b / (r + b)) * value(r, b - 1, mem);

		mem[r][b] = max((draw_r + draw_b), (double)(b - r));
	}

	//return std::max((draw_r + draw_b), (double) (b - r));
	return mem[r][b];
} 
#endif