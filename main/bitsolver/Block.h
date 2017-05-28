#pragma once
typedef unsigned long long ull;
class Block
{
private:
	int circumference;
	int zk;
	void calcCircumference();
public:
	ull blockRow[32];
	ull blockCol[32];
	static const int BLOCKWIDTH = 8;
	static const int BLOCKHEIGHT = 8;
	Block();
	~Block();
	Block& operator=(Block block);
	Block clone();
	int getZk();
	int getCircumference();
	void rotate(int angle);
	void frip();
	void in();
	void out();
};

