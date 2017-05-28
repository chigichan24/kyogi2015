#include <bits/stdc++.h>
#include "procon26.h"
using namespace std;
const int dx[]={1,0,-1,0,1,-1,-1,1};
const int dy[]={0,1,0,-1,1,1,-1,-1};
const int INF = 1<<30;
const double EPS = 1e-8;
#define PB push_back
#define mk make_pair
#define fr first
#define sc second
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
struct data{
	vi seq;
	int depth;
	int score;
	int p;
	data(){}
	data(vi _seq,int _depth,int _score,int _p){
		seq = _seq;
		depth = _depth;
		score = _score;
		p = _p;
	}
};
int main(){
	srand(time(NULL));
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
	vector < ip > _V[N];
	for(int q = 0 ; q < N; q++){
		for(int i = -7; i < H; i++){
			for(int j = -7; j < W; j++){
				for(int d = 0; d < 4; d++){
					Placement P;
					P = Placement(q,j,i,0,d,0);
					if(F.CanPut(P)){
						_V[q].push_back(ip(rand()%1000,P));
					}
					P = Placement(q,j,i,1,d,0);
					if(F.CanPut(P)){
						_V[q].push_back(ip(rand()%1000,P));
					}
				}
			}
		}
	}
	vector < ip > V[N];
	for(int q = 0; q < N; q++){
		for(int i = 0; i < _V[q].size(); i++){
			for(int j = i + 1 ; j < _V[q].size(); j++){
				if(_V[q][i].second == _V[q][j].second){
					_V[q][j].first = 0;
				}
			}
		}
		for(int i = 0; i < _V[q].size(); i++){
			if(_V[q][i].first){
				V[q].push_back(_V[q][i]);
			}
		}
	}
	
	int ret = -INF;
	queue < data > Q;
	vector < Placement > final;
	vi s;
	///*
	int LIMIT = 950;
	while(ret == -INF){
		Q.push(data(s,0,0,1000));
		//cout << "!" << "\n";
		while( !Q.empty() ){
			data d = Q.front();Q.pop();
			Field G = F.Clone();
			bool isPut = false;
			//今までどのような手順でおいたか復元する
			for(int q = 0; q < d.seq.size(); q++){
				if(d.seq[q] == -1)continue;
				G.Put(V[q][d.seq[q]].second,true);
				isPut = true;
			}

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


			if(d.p > LIMIT){
				//次にどの置き方でどの場所に石を置くかすべて試す
				for(int i = 0; i < V[d.depth].size(); i++){
					Placement p = V[d.depth][i].second;
					int r = V[d.depth][i].first;
					if(r > LIMIT)continue;
					if(G.CanPut(p)){
						if(!isPut || G.isConnected(p)){
							d.seq.push_back(i);
							Q.push(data(d.seq,d.depth+1,d.score+szStone[d.depth],rand()%1000));
							d.seq.pop_back();
						}
					}
				}
				//置かないパターンも試す
				d.seq.push_back(-1);
				Q.push(data(d.seq,d.depth+1,d.score,rand()%1000));
				d.seq.pop_back();
			}
		}
		LIMIT /= 2;
	}

	//*/
	for(int q = 0; q < N; q++){
		final[q].Out();
	}
	return 0;
}