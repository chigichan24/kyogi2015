#pragma once
#include "bits/stdc++.h"
#include "Placement.h"
class Field
{
private:
	int stn;
	int zk;
	int visited[32][32];
	const int HEIGHTMAX = 32;
	const int WIDTHMAX = 32;
	int Height, Width;
	int circumference;
	bool isTrueHole;
	std::vector<int> holes;
	void calcHole(Placement p);
	int getDepth(int y, int x);
public:
	int field[32][32];
	int *operator[](int i);
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
	std::vector<int> getHole(Placement p);
	void in();
	void out();
};

