#include "Placement.h"

Placement::Placement()
{
	x = 0;
	y = 0;
	frip = 0;
	dir = 0;
	isPassed = 0;
	block = Block();
	canUse = false;
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
	this->canUse = applyCor();
}


Placement::~Placement()
{
	
}

bool Placement::applyCor(){
	bool flagment = true;
	int absx = std::abs(x);
	int absy = std::abs(y);
	ull row[32];
	ull column[32];
	Block a = block.clone();
	if (frip){
		a.frip();
	}
	a.rotate(dir);

	block = a;

	for (int i = 0; i < 32; ++i){
		row[i] = block.blockRow[i];
		column[i] = block.blockCol[i];
	}

	if (x <= 0 && y <= 0){
		flagment &= moveLeft(row, column, absx);
		flagment &= moveTop(row, column, absy);
	}
	else if (x <= 0 && y >= 0){
		flagment &= moveLeft(row, column, absx);
		flagment &= moveBottom(row, column, absy);
	}
	else if (x >= 0 && y <= 0){
		flagment &= moveRight(row, column, absx);
		flagment &= moveTop(row, column, absy);
	}
	else if (x >= 0 && y >= 0){
		flagment &= moveRight(row, column, absx);
		flagment &= moveBottom(row, column, absy);
	}

	if (flagment){
		for (int i = 0; i < 32; ++i){
			block.blockRow[i] = row[i];
			block.blockCol[i] = column[i];
		}
	}

	return flagment;
}

bool Placement::operator==(Placement p){
	ull row[32];
	ull column[32];

	ull subrow[32];
	ull subcolumn[32];

	for (int i = 0; i < 32; ++i){
		row[i] = p.block.blockRow[i];
		column[i] = p.block.blockCol[i];
		subrow[i] = block.blockRow[i];
		subcolumn[i] = block.blockCol[i];
	}
	
	while (moveLeft(row, column, 1));
	while (moveTop(row, column, 1));
	while (moveLeft(subrow, subcolumn, 1));
	while (moveTop(subrow, subcolumn, 1));

	for (int i = 0; i < 32; ++i){
		if (row[i] != block.blockRow[i])return false;
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

void Placement::rowToColumn(ull *rowbit, ull *columnbit){
	for (int i = 0; i < 32; ++i){
		columnbit[i] = 0;
		for (int j = 0; j < 32; ++j){
			columnbit[i] |= ((rowbit[j] >> i & 1) << j);
		}
	}
}

void Placement::columnToRow(ull *columnbit, ull *rowbit){
	for (int i = 0; i < 32; ++i){
		rowbit[i] = 0;
		for (int j = 0; j < 32; ++j){
			rowbit[i] |= ((columnbit[j] >> i & 1) << j);
		}
	}
}

bool Placement::moveRight(ull *row,ull *col,int count){
	for (int i = 0; i < 32; ++i){
		row[i] <<= count;
	}
	for (int i = 32 - count; i < 32; ++i){
		if (col[i]){
			return false;
		}
	}
	for (int i = 31 - count; i >= 0; --i){
		col[i + count] = col[i];
	}
	for (int i = 0; i < count; ++i){
		col[i] = 0LL;
	}
	return true;
}

bool Placement::moveLeft(ull *row,ull *col,int count){
	for (int i = 0; i < 32; ++i){
		row[i] >>= count;
	}
	for (int i = 0; i < count; ++i){
		if (col[i]){
			return false;
		}
	}
	for (int i = count; i < 32; ++i){
		col[i - count] = col[i];
	}
	for (int i = 32 - count; i < 32; ++i){
		col[i] = 0LL;
	}

	return true;
}

bool Placement::moveTop(ull *row,ull *col,int count){
	for (int i = 0; i < 32; ++i){
		col[i] >>= count;
	}
	for (int i = 0; i < count; ++i){
		if (row[i]){
			return false;
		}
	}
	for (int i = count; i < 32; ++i){
		row[i - count] = row[i];
	}
	for (int i = 31 - count; i < 32; ++i){
		row[i] = 0LL;
	}
	return true;

}

bool Placement::moveBottom(ull *row,ull *col,int count){
	for (int i = 0; i < 32; ++i){
		col[i] <<= count;
	}
	for (int i = 32 - count; i < 32; ++i){
		if (row[i]){
			return false;
		}
	}
	for (int i = 32 - count; i >= 0; --i){
		row[i + count] = row[i];
	}
	for (int i = 0; i < count; ++i){
		row[i] = 0LL;
	}
	return true;
}