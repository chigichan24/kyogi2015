#include <bits/stdc++.h>
#include "procon26.h"
using namespace std;
typedef pair<int, Placement> ip;
Field F;
Block blocks[300];
int blockSize,W,H;

Placement Eval(Field f,int id){
	Placement p = Placement();
	return p;
}

void In(){
	F.In();
	scanf("%d", &blockSize);
	for(int q = 0; q < blockSize; q++){
		blocks[q].In();
	}
	return;
}

void GreedySearch(){
	Field G = F.Clone();
	bool isPut = false;
	for (int q = 0; q < blockSize; q++){
		Placement p = Eval(G, q);
		p.Out();
		if (!p.isPassed){
			isPut = true;
		}
		F.Put(p,isPut);
	}
}

int main(){
	In();
	GreedySearch();
	return 0;
}