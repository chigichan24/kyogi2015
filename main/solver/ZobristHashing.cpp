#include "ZobristHashing.h"

ZobristHashing::ZobristHashing()
{
	this->Height = 32;
	this->Width = 32;
}

ZobristHashing::ZobristHashing(int Height, int Width)
{
	this->Height = Height;
	this->Width = Width;
}

ZobristHashing::~ZobristHashing()
{

}

void ZobristHashing::init()
{
	Utility u;
	u.initXor128();
	for (int y = 0; y < Height; ++y){
		for (int x = 0; x < Width; ++x){
			for (int id = 0; id < 2; ++id){
				table[y][x][id] = u.xor128();
			}
		}
	}
	return;
}

unsigned long long ZobristHashing::hash(int board[32][32])
{
	unsigned long long h = 0LL;

	for (int y = 0; y < Height; ++y){
		for (int x = 0; x < Width; ++x){
			if (board[y][x] != empty){
				int id = std::min(1, board[y][x]);
				h = h ^ table[y][x][id];
			}
		}
	}

	return h;
}