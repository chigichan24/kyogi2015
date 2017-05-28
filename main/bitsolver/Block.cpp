#include "Block.h"
#include "bits/stdc++.h"

Block::Block()
{
	for (int idx = 0; idx < 32; ++idx){
		blockRow[idx] = blockCol[idx] = 0LL;
	}
}


Block::~Block()
{

}

Block& Block::operator=(Block block){
	for (int idx = 0; idx < 32; ++idx){
		this->blockRow[idx] = block.blockRow[idx];
		this->blockCol[idx] = block.blockCol[idx];
	}
	this->zk = block.zk;
	this->circumference = block.circumference;
	return (*this);
}


Block Block::clone()
{
	Block b;
	for (int idx = 0; idx < 32; ++idx){
		b.blockRow[idx] = this->blockRow[idx];
		b.blockCol[idx] = this->blockCol[idx];
	}
	b.zk = this->zk;
	b.circumference = this->circumference;
	return b;
}

void Block::rotate(int angle)
{
	if (90 <= angle){
		angle /= 90;
	}
	angle %= 4;

	while (angle--){
		ull tmp[32];
		for (int x = 0; x < BLOCKWIDTH; ++x){
			tmp[x] = blockCol[x];
		}

		for (int y = 0; y < BLOCKHEIGHT; ++y){
			blockCol[y] = blockRow[BLOCKHEIGHT - 1 - y];
		}

		for (int x = 0; x < BLOCKWIDTH; ++x){
			for (int y = 0; y < BLOCKHEIGHT / 2; ++y){
				if ((1 & tmp[x] >> y) ^ (1 & tmp[x] >> (BLOCKHEIGHT - 1 - y))){
					tmp[x] ^= 1LL << y;
					tmp[x] ^= 1LL << (BLOCKHEIGHT - 1 - y);
				}
			}
			blockRow[x] = tmp[x];
		}

	}

	return;
}

void Block::frip()
{
	for (int x = 0; x < BLOCKWIDTH/2; ++x){
		std::swap(blockCol[x], blockCol[BLOCKWIDTH - 1 - x]);
	}

	for (int y = 0; y < BLOCKHEIGHT; ++y){
		for (int x = 0; x < BLOCKWIDTH / 2; ++x){
			if ((1 & (blockRow[y] >> x)) ^ (1 & (blockRow[y] >> (BLOCKWIDTH - 1 - x)))){
				blockRow[y] ^= 1LL << x;
				blockRow[y] ^= 1LL << (BLOCKWIDTH - 1 - x);
			}
		}
	}

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
	ull tmp[32] = { 0LL };
	int ans = 0;

	for (int y = 0; y < BLOCKHEIGHT; ++y){
		for (int x = 0; x < BLOCKWIDTH; ++x){
			if (1 & (blockRow[y] >> x)){
				for (int dir = 0; dir < 4; ++dir){
					int ny = y + dy[dir];
					int nx = x + dx[dir];
					if (ny < 0 || BLOCKHEIGHT <= ny || nx < 0 || BLOCKWIDTH <= nx)continue;
					if (1 & (tmp[ny] >> nx)){
						ans -= 2;
					}
					++ans;
				}
				tmp[y] |= 1LL << x;
			}
		}
	}
	this->circumference = ans;
	return;
}

void Block::in()
{
	for (int i = 0; i < BLOCKHEIGHT; ++i){
		blockCol[i] = blockRow[i] = 0LL;
	}
	int cnt = 0;
	for (int i = 0; i < BLOCKHEIGHT; ++i){
		char s[10];
		scanf("%s", s);
		for (int j = 0; j < BLOCKWIDTH; ++j){
			if (s[j] == '1'){
				cnt++;
				blockRow[i] |= 1LL << j;
				blockCol[j] |= 1LL << i;
			}
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
			printf("%d", (1&(blockRow[i]>>j)));
		}
		printf("\n");
	}
	printf("zk : %d , circum : %d\n",this->zk, this->circumference);
	return;
}
