#include <bits/stdc++.h>

using namespace std;

const int W=32,H=32;
int N;

class xor128{
private:
	unsigned long long x=123456789, y=362436069, z=521288629, w=88675123;
public:
	void init(){
		unsigned long long s = rand();
		z ^= s;
		z ^= z >> 21;
		z ^= z << 35;
		z ^= z >> 4;
		z *= 2685821657736338717LL;
	}
	unsigned long long run(){
		unsigned long long t=(x^(x<<11));
		x=y; y=z; z=w;
		return ( w=(w^(w>>19))^(t^(t>>8)) );
	}
};

class ZobristHashing{
private:
	enum stageState{empty=0, filled=1};
	unsigned long long table[W][H][2];	 
public:
	void init(){
		xor128 r;
		r.init();
		for(int y = 0; y < H; ++y){
			for(int x = 0; x < W; ++x){
				for(int id = 0; id < 2; ++id){
					table[y][x][id] = r.run();
				}
			}
		}
	}

	unsigned long long hash(int **board){
		unsigned long long h = 0;

		for(int y = 0; y < H; ++y){
			for(int x = 0; x < W; ++x){
				if(board[y][x] != empty){
					int id = 1;
					h = h ^ table[y][x][id];
				}
			}
		}

		return h;
	}

};



int main(){
	


	return 0;
}