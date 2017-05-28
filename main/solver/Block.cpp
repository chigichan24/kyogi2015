#include "Block.h"
#include "bits/stdc++.h"

Block::Block()
{
	for (int i = 0; i < BLOCKHEIGHT; ++i){
		for (int j = 0; j < BLOCKWIDTH; ++j){
			block[i][j] = 0;
		}
	}
	//bit = 0LL;
}


Block::~Block()
{

}

Block& Block::operator=(Block _block){
	for (int i = 0; i < BLOCKHEIGHT; ++i){
		for (int j = 0; j < BLOCKWIDTH; ++j){
			Block::block[i][j] = _block[i][j];
		}
	}
	Block::zk = _block.zk;
	Block::circumference = _block.circumference;
	return (*this);
}

bool *Block::operator[](int i){
	return block[i];
}

Block Block::clone()
{
	Block b;
	for (int i = 0; i < BLOCKHEIGHT; ++i){
		for (int j = 0; j < BLOCKWIDTH; ++j){
			b[i][j] = block[i][j];
			/*
			if (block[i][j]){
				b.bit |= 1LL << (BLOCKHEIGHT*i + j);
			}
			*/
		}
	}
	b.zk = this->zk;
	b.circumference = this->circumference;
	return b;
}

unsigned long long Block::close(unsigned long long state){
	while (!(WIDTHMASK & state)){
		state >>= 1;
	}
	while (!(HEIGHTMASK & state)){
		state >>= 8;
	}
	return state;
}

void Block::rotate(int angle)
{
	if (90 <= angle){
		angle /= 90;
	}

	angle %= 4;

	unsigned long long rotated = 0LL;
	while (angle--){
		for (int i = 0; i < BLOCKHEIGHT / 2; ++i){
			for (int j = 0; j < BLOCKWIDTH / 2; ++j){
				bool sub = block[i][j];
				block[i][j] = block[BLOCKHEIGHT - j - 1][i];
				block[BLOCKHEIGHT - j - 1][i] = block[BLOCKHEIGHT - i - 1][BLOCKWIDTH - j - 1];
				block[BLOCKHEIGHT - i - 1][BLOCKWIDTH - j - 1] = block[j][BLOCKWIDTH - i - 1];
				block[j][BLOCKWIDTH - i - 1] = sub;
 			}
		}
		/*
		for (int i = 0; i < BLOCKHEIGHT; ++i){
			for (int j = 0; j < BLOCKWIDTH; ++j){
				if (1 & (bit >> (i*BLOCKHEIGHT + j))){
					rotated += 1LL << (j*BLOCKWIDTH + BLOCKHEIGHT - i - 1);
				}
			}
		}
		*/
	}
	//bit = rotated;

	return;
}

void Block::frip()
{
	unsigned long long friped = 0LL;

	for (int i = 0; i < BLOCKHEIGHT; ++i){
		for (int j = 0; j < BLOCKWIDTH / 2; ++j){
			bool sub = block[i][j];
			block[i][j] = block[i][BLOCKWIDTH - j - 1];
			block[i][BLOCKWIDTH - j - 1] = sub;

			/*
			if ((1 & bit >> (BLOCKHEIGHT*i + j)) ^ (1 & bit >> (BLOCKHEIGHT*i + BLOCKWIDTH - j - 1))){
				bit ^= 1LL << (BLOCKHEIGHT*i + j);
				bit ^= 1LL << (BLOCKHEIGHT*i + BLOCKWIDTH + j - 1);
			}
			*/
			
		}
	}

	//bit = close(bit);

	return;
}

int Block::getZk(){
	return this->zk;
}

int Block::getCircumference(){
	return this->circumference;
}

void Block::calcCircumference(){
	int dy[] = { 1, 0, -1, 0 };
	int dx[] = { 0, 1, 0, -1 };
	bool tmp[BLOCKHEIGHT][BLOCKWIDTH] = { { 0 } };
	for (int i = 0; i < BLOCKHEIGHT; ++i){
		for (int j = 0; j < BLOCKWIDTH; ++j){
			if (this->block[i][j]){
				for (int dir = 0; dir < 4; ++dir){
					int ny = i + dy[dir];
					int nx = j + dx[dir];

					if (ny < 0 || BLOCKHEIGHT <= ny || nx < 0 || BLOCKWIDTH <= nx)continue;

					if (tmp[ny][nx] == 1){
						(this->circumference) -= 2;
					}
					(this->circumference)++;
				}
				tmp[i][j] = 1;
			}
		}
	}
	return;
}

void Block::in()
{
	int cnt = 0;
	for (int i = 0; i < BLOCKHEIGHT; ++i){
		char s[10];
		scanf("%s", s);
		for (int j = 0; j < BLOCKWIDTH; ++j){
			block[i][j] = s[j] - '0';
			if (block[i][j]){
				cnt++;
			}
			/*
			if (block[i][j]){
				bit += (1LL << (BLOCKHEIGHT*i + j));
			}
			*/
		}
	}
	this->circumference = 0;
	this->zk = cnt;
	calcCircumference();
	return;
}

void Block::out()
{
	for (int i = 0; i < BLOCKHEIGHT; ++i){
		for (int j = 0; j < BLOCKWIDTH; ++j){
			printf("%d", block[i][j]);
		}
		printf("\n");
	}
	printf("circum : %d\n", this->circumference);
	return;
}
