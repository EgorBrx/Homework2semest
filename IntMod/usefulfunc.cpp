#include "usefulfunc.h"
int32_t mod(int32_t dividend, int32_t divisor)
{
	return (dividend % divisor + divisor) % divisor;
}

int32_t TestFunc()
{
	assert(mod(5,  2) == 1);
	assert(mod(7,  2) == 1);
	assert(mod(7,  3) == 1);
	assert(mod(25, 9) == 7);
	assert(mod(-5, 2) == 1);
	assert(mod(32455, 762)  == 451);
	assert(mod(-7653, 53)   == 32);
	return 1;
}

int32_t gcdExtended(int32_t a, int32_t b, int32_t& x, int32_t& y)
{
	// ax + by = d, d = gcd(a,b)
	if (a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}

	int32_t x1, y1;
	int32_t gcd = gcdExtended(b % a, a, x1, y1);

	x = y1 - (b / a) * x1;
	y = x1;

	return gcd;
}
