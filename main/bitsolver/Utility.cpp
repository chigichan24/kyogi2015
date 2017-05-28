#include "Utility.h"

double Utility::INF = 1e10;

Utility::Utility()
{
}


Utility::~Utility()
{
}

void Utility::initXor128()
{
	srand(time(NULL));
	unsigned long long s = rand();
	z ^= s;
	z ^= z >> 21;
	z ^= z << 35;
	z ^= z >> 4;
	z *= 2685821657736338717LL;
	return;
}

unsigned long long Utility::xor128()
{
	unsigned long long t = (x ^ (x << 11));
	x = y; y = z; z = w;
	return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}