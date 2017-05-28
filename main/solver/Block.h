#pragma once
class Block
{
private:
	bool block[8][8];
	int circumference;
	int zk;
	const unsigned long long HEIGHTMASK = 255LL;
	const unsigned long long WIDTHMASK = 72340172838076673LL;
	unsigned long long close(unsigned long long state);
	void calcCircumference();
public:
	static const int BLOCKWIDTH = 8;
	static const int BLOCKHEIGHT = 8;
	unsigned long long bit;
	Block();
	~Block();
	bool *operator[](int i);
	Block& operator=(Block _block);
	Block clone();
	int getZk();
	int getCircumference();
	void rotate(int angle);
	void frip();
	void in();
	void out();
};

