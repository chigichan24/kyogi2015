#pragma once
#include "bits/stdc++.h"
class Utility
{
private:
	unsigned long long x = 123456789;
	unsigned long long y = 362436069;
	unsigned long long z = 521288629;
	unsigned long long w = 88675123;
public:
	Utility();
	~Utility();
	void initXor128();
	unsigned long long xor128();
	static double INF;
};

