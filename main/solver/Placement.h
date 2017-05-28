#pragma once
#include "Block.h"
#include "bits/stdc++.h"
class Placement
{
private:

public:
	Block block;
	int isPassed;
	int x, y, frip, dir;
	
	bool operator==(Placement p);
	bool operator<(const Placement &p);
	Placement();
	Placement(bool isPassed);
	Placement(Block block, int x, int y, int frip, int dir, bool isPassed);
	~Placement();
	void out();
};

