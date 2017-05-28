#include "Placement.h"

Placement::Placement()
{
	x = 0;
	y = 0;
	frip = 0;
	dir = 0;
	isPassed = 0;
	block = Block();
}

Placement::Placement(bool isPassed)
{
	this->isPassed = isPassed;
}

Placement::Placement(Block block, int x, int y, int frip, int dir, bool isPassed)
{
	this->block = block;
	this->x = x;
	this->y = y;
	this->frip = frip;
	this->dir = dir;
	this->isPassed = isPassed;
}


Placement::~Placement()
{
}

bool Placement::operator==(Placement p){
	Block A = block.clone();
	Block B = p.block.clone();
	
	if (frip){
		A.frip();
	}
	if (p.frip){
		B.frip();
	}

	A.rotate(dir);
	B.rotate(p.dir);

	for (int i = 0; i < Block::BLOCKHEIGHT; ++i){
		for (int j = 0; j < Block::BLOCKWIDTH; ++j){
			int Y = p.y - y;
			int X = p.x - x;
			if (Y < 0 || Block::BLOCKHEIGHT <= Y || X < 0 || Block::BLOCKWIDTH <= X){
				if (A[i][j]){
					return false;
				}
			}
			if (A[i][j] != B[i + Y][j + X]){
				return false;
			}
		}
	}

	return true;
}

bool Placement::operator<(const Placement &p){
	return x < y;
}

void Placement::out(){
	if (isPassed)printf("\n");
	else printf("%d %d %c %d\n", x, y, frip ? 'T' : 'H', dir*90);
}