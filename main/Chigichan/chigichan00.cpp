#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/param.h>
#include "procon26.h"
using namespace std;
const int dx[]={1,0,-1,0,1,-1,-1,1};
const int dy[]={0,1,0,-1,1,1,-1,-1};
const int INF = 1<<30;
const double EPS = 1e-8;
#define PB push_back
#define mk make_pair
#define ll long long
#define reps(i,j,k) for(int i = (j); i < (k); i++)
#define rep(i,j) reps(i,0,j)
#define MOD 1000000007
#define lengthof(x) (sizeof(x) / sizeof(*(x)))
typedef pair<int,int> Pii;
typedef pair<Pii,int> P;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector <Pii> vp;
typedef pair <int,Placement> ip; 
int W,H,N;
Field F;
Block blocks[300];

set < string > memo;

string convert(Field s){
	string tmp = "";
	for(int y = 0; y < H; ++y){
		for(int x = 0; x < W; ++x){
			tmp += (s.sc[y][x]+'0');
		}
	}
	return tmp;
}

struct data{
	vi seq;
	int depth;
	int score;
	data(){}
	data(vi _seq,int _depth,int _score){
		seq = _seq;
		depth = _depth;
		score = _score;
	}
};
int main(){
	F.In();
	cin >> N;
	int szStone[1024]={0};
	for(int q = 0; q < N; q++){
		blocks[q].In();
		int c = 0;
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(blocks[q][i][j])szStone[q]++;
			}
		}
	}
	multiset < ip > _V[N];
	for(int q = 0 ; q < N; q++){
		for(int i = -7; i < H; i++){
			for(int j = -7; j < W; j++){
				for(int d = 0; d < 4; d++){
					Placement P;
					P = Placement(q,j,i,0,d,0);
					if(F.CanPut(P)){
						_V[q].insert(ip(1e+8,P));
					}
					P = Placement(q,j,i,1,d,0);
					if(F.CanPut(P)){
						_V[q].insert(ip(1e+8,P));
					}
				}
			}
		}
	}
	vector < ip > V[N];
	for(int q = 0; q < N; q++){
		copy(_V[q].begin(), _V[q].end(), inserter(V[q], V[q].begin()));
	}
	
	int ret = -INF;
	queue < data > Q;
	vector < Placement > final;
	vi s;
	Q.push(data(s,0,0));
	///*
	while( !Q.empty() ){
		
		data d = Q.front();Q.pop();
		Field G = F.Clone();
		bool isPut = false;
		//今までどのような手順でおいたか復元する
		for(int q = 0; q < d.seq.size(); q++){
			if(d.seq[q] == -1)continue;
			G.Put(V[q][d.seq[q]].second,false);
			isPut = true;
		}

		//一度来ていた盤面ならば探索するのをやめる
		string s = convert(G.Clone());

		if(isPut && memo.find(s) != memo.end())continue;
		memo.insert(s);

		//最後まで調べ終わったら最も評価が高いものを答えにする
		//ここでは敷き詰めることのできた石の数
		if(d.depth == N){
			if(ret < d.score){
				ret = d.score;
				final.clear();
				for(int q = 0; q < N; q++){
					if(d.seq[q] == -1)final.push_back(Placement(q,true));
					else final.push_back(V[q][d.seq[q]].second);
				}
			}
			continue;
		}


		//次にどの置き方でどの場所に石を置くかすべて試す
		for(int i = 0; i < V[d.depth].size(); i++){
			Placement p = V[d.depth][i].second;
			if(G.CanPut(p)){
				if(!isPut || G.isConnected(p)){
					d.seq.push_back(i);
					Q.push(data(d.seq,d.depth+1,d.score+szStone[d.depth]));
					d.seq.pop_back();
				}
			}
		}
		//置かないパターンも試す
		d.seq.push_back(-1);
		Q.push(data(d.seq,d.depth+1,d.score));
		d.seq.pop_back();
		//printf("%lf\n",clock()-t);
	}
	//*/
	for(int q = 0; q < N; q++){
		final[q].Out();
	}
	return 0;
}