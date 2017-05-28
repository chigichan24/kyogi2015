#pragma once
#include "Block.h"
#include "bits/stdc++.h"
typedef unsigned long long ull;
class Placement
{
private:
	void rowToColumn(ull *rowbit, ull *columnbit);
	void columnToRow(ull *columnbit, ull *rowbit);
	bool applyCor();
	bool moveRight(ull *row, ull *col,int count);
	bool moveLeft(ull *row, ull *col, int count);
	bool moveTop(ull *row, ull *col, int count);
	bool moveBottom(ull *row, ull *col, int count);
public:
	Block block;
	int isPassed;
	int x, y, frip, dir;
	bool canUse;
	
	bool operator==(Placement p);
	bool operator<(const Placement &p);
	Placement();
	Placement(bool isPassed);
	Placement(Block block, int x, int y, int frip, int dir, bool isPassed);
	~Placement();
	void out();
};

