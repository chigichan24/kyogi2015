#pragma once
#include "bits/stdc++.h"
#include "Utility.h"

class ZobristHashing
{
private:
	enum stageState{empty = 0, filled = 1};
	unsigned long long table[32][32][2];
	int Height, Width;
public:
	ZobristHashing();
	ZobristHashing(int Height, int Width);
	~ZobristHashing();
	void init();
	unsigned long long hash(unsigned long long *board);
};
