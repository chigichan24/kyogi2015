#pragma once
#include "bits/stdc++.h"
#include "Placement.h"
typedef unsigned long long ull;
class Field
{
private:
	int stn;
	int zk;
	ull visited[32];
	ull state[32];
	const int HEIGHTMAX = 32;
	const int WIDTHMAX = 32;
	int Height, Width;
	int circumference;
	bool isTrueHole;
	std::vector<int> holes;
	void calcHole(Placement p,int &one,int &two);
	int getDepth(int y, int x);
public:
	ull fieldRow[32];
	ull fieldCol[32];
	ull obstacleRow[32];
	ull obstacleCol[32];
	bool operator<(Field f);
	bool operator>(Field f);
	bool operator==(Field f);
	bool operator<=(Field f);
	bool operator>=(Field f);
	Field& operator=(Field f);
	Field();
	~Field();
	Field clone();
	bool canPut(Placement p);
	bool isConnected(Placement p);
	bool put(Placement p, bool isCount);
	int getHeight();
	int getWidth();
	int getCircumference();
	int getZk();
	std::vector<int> getHole(Placement p,int &one,int &two);
	void in();
	void out();
};

