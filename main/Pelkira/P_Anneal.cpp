#include<bits/stdc++.h>
#include"procon26.h"
using namespace std;
typedef pair<int,Placement> ip;
int W,H,N;
Field F;
Block blocks[300];
Placement ans[300];
Field bestF;
void Input(){
	F.In();
	cin>>N;
	for(int q = 0;q < N;q++)blocks[q].In();
	return;
}
double Eval(Placement P){
    return 0.0;
}
Placement ChoicePlm(int q,Field G){
	return Placement();
}
void AnswerGrd(int S){
    Field G = F.Clone();
    for(int q = S;q < N;q++){
        Placement P = ChoicePlm(q,G);
        double score = Eval(P);
        G.Put(P,true);
    }
    if(bestF > G)bestF = G;
}
int main(){
	Input();
	bestF = F;
	vector<ip> _V[N];
	bool canPut[50][50] = {};
	for(int q = 0;q < N;q++){
		for(int i = -7;i < 8;i++){
			for(int j = -7;j < 8;j++){
				for(int d = 0;d < 4;d++){
					Placement P;
					P = Placement(q,j,i,0,d,0);
					if(F.CanPut(P)){
						_V[q].push_back(ip(1e+8,P));
						for(int y = 0;y < 8;y++){
							for(int x = 0;x < 8;x++){
								if (y + P.y < 0 || H <= y + P.y || x + P.x < 0 || W <= x + P.x);
							}
						}
					}
					P = Placement(q,j,i,1,d,0);
					if(F.CanPut(P)){
						_V[q].push_back(ip(1e+8,P));
						for(int y = 0;y < 8;y++){
							for(int x = 0;x < 8;x++){
								if (y + P.y < 0 || H <= y + P.y || x + P.x < 0 || W <= x + P.x);
							}
						}
					}
				}
			}
		}
	}
	for(int q = 0;q < N;q++){
		AnswerGrd(q);
	}
}
