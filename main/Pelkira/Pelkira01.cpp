#include<bits/stdc++.h>
#include"procon26.h"
using namespace std;
typedef pair<int,Placement> ip;
int W,H,N;
Field F;
Block blocks[300];
Placement ans[300];
int main(){
	F.In();
	cin>>N;
	for(int q = 0;q < N;q++)blocks[q].In();
	vector<ip> _V[N];
	bool canPut[50][50] = {};
	for(int q = 0;q < N;q++){
		Block B = blocks[q];
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
                				else canPut[y + P.y][x + P.x] = B[i][j];
							}
						}
					}
					P = Placement(q,j,i,1,d,0);
					if(F.CanPut(P)){
						_V[q].push_back(ip(1e+8,P));
						for(int y = 0;y < 8;y++){
							for(int x = 0;x < 8;x++){
								if (y + P.y < 0 || H <= y + P.y || x + P.x < 0 || W <= x + P.x);
                				else canPut[y + P.y][x + P.x] = B[y][x];
							}
						}
					}
				}
			}
		}
	}
	int cantPutNum = 0;
	for(int i = 0;i < H;i++){
		for(int j = 0;j < W;j++){
			if(!canPut[i][j])cantPutNum++;
		}
	}
	vector<ip> V[N];
	for(int q = 0;q < N;q++){
		for(int i = 0;i < _V[q].size();i++){
			for(int j = i + 1;j < _V[q].size();j++){
				if(_V[q][i].second == _V[q][j].second){
					_V[q][j].first = 0;
				}
			}
		}
		for(int i = 0;i < _V[q].size();i++){
			if(_V[q][i].first)V[q].push_back(_V[q][i]);
		}
	}
	for(int q = 0;q < N;q++){
		for(int i = 0;i < V[q].size();i++){
			Field G = F.Clone();
			Placement P = V[q][i].second;
			G.Put(P);
			int cnt = 0;
			bool cp[50][50] = {};
			for(int r = 0;r < N;r++){
				if(q == r)continue;
				for(int j = 0;j < V[r].size();j++){
					if(!G.CanPut(V[r][j].second))cnt++;
					else{
						for(int y = 0;y < 8;y++){
							for(int x = 0;x < 8;x++){
								if (y + P.y < 0 || H <= y + P.y || x + P.x < 0 || W <= x + P.x);
                				else cp[y + P.y][x + P.x] = blocks[V[r][j].second.id][i][j];
							}
						}
					}
				}
				V[q][i].first = cnt;
				/*
				int cantPutNum = 0;
				for(int y = 0;y < H;y++){
					for(int x = 0;x < W;x++){
						if(!cp[y][x])cantPutNum++;
					}
				}
				*/
			}

		}
		if(V[q].size() == 0)V[q].push_back(ip(1e+8,Placement(q,true)));
	}
	for(int q = 0;q < N;q++){
		for(int i = 0;i < V[q].size();i++){
			for(int j = i+1;j < V[q].size();j++){
				if(V[q][i].first > V[q][j].first)swap(V[q][i],V[q][j]);
			}
		}
	}
	int now = 0;
	for(int q = 0;q < N;q++){
		//cout<<q<<"["<<V[q][0].first<<"]:";
		V[q][0].second.Out();
	}
}