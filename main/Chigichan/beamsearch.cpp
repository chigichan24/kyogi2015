#include <bits/stdc++.h>
#include "procon26.h"
#include <Windows.h>
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
#define BEAM_WIDTH_HIGH 300
#define BEAM_WIDTH_MED 150
typedef pair<int,int> Pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector <Pii> vp;
typedef pair <ll,Placement> ip; 
int W,H,N;
Field F;
Block blocks[300];
vector < ip > V[300];
ll szStone[1024]={0};

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
	unsigned long long table[32][32][2];
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

	unsigned long long hash(int board[50][50]){
		unsigned long long h = 0;

		for(int y = 0; y < H; ++y){
			for(int x = 0; x < W; ++x){
				if(board[y][x] != empty){
					int id = min(1,board[y][x]);
					h = h ^ table[y][x][id];
				}
			}
		}

		return h;
	}

};

struct data{
	vi seq;
	int score;
	ll subscore;
	data(){}
	data(vi _seq,int _score,ll _subscore){
		seq = _seq;
		score = _score;
		subscore = _subscore;
	}
	bool operator<(const data &a)const{
		if(subscore == a.subscore)return score<a.score;
		return subscore<a.subscore;
		/*
		if(score == a.score)return subscore<a.subscore;
		return score<a.score;
		*/
	}
};

int tempreatureEval(int x){
	double c = x;
	double y = -1.1/10.0*c*c*exp(-c/13.0)+10.0;
	int res = (int)y;
	return res;
}

set < unsigned long long > memo;

void solve(){
	int ret = -INF;
	ZobristHashing zob;
	zob.init();
	priority_queue < data > Q[2];
	vector < Placement > final;
	int LIMIT = 100;
	LIMIT = 1;
	while(LIMIT--){

		while(Q[0].size())Q[0].pop();
		while(Q[1].size())Q[1].pop();
		
		vi s;
		int step = N;
		Q[0].push(data(s,0,0));
		while( step-- ){
			memo.clear();
			int depth = N - step - 1;
			int cnt = BEAM_WIDTH_HIGH;
			//printf("step = %d cnt = %d V[depth] = %d\n",step,cnt,V[depth].size());
			while( true ){
				if(Q[0].size() == 0 || cnt-- == 0)break;
				data d = Q[0].top();Q[0].pop();
				Field G = F.Clone();
				bool isPut = false;
				int c = 0;
				//今までどのような手順でおいたか復元する
				for(int q = 0; q < d.seq.size(); q++){
					if(d.seq[q] == -1)continue;
					c++;
					G.Put(V[q][d.seq[q]].second,true);
					isPut = true;
				}
				//次にどの置き方でどの場所に石を置くかすべて試す
				for(int i = 0; i < V[depth].size(); i++){
					Placement p = V[depth][i].second;
					int r = V[depth][i].first;
					if(G.CanPut(p)){
						if(!isPut || G.isConnected(p)){
							/*類似盤面の除去をここでする	*/
						
							Field H = G.Clone();
							H.Put(p,true);

							unsigned long long hashed = zob.hash(H.sc);

							if(memo.find(hashed) != memo.end())continue;
							memo.insert(hashed);

							d.seq.push_back(i);
							Q[1].push(data(d.seq,d.score+szStone[depth],d.subscore+r*c));
							d.seq.pop_back();
						}
					}
				}
				//置かないパターンも試す
				unsigned long long hashed = zob.hash(G.sc);

				if(memo.find(hashed) != memo.end())continue;
				memo.insert(hashed);
				d.seq.push_back(-1);
				Q[1].push(data(d.seq,d.score,d.subscore+szStone[depth]+10));
				d.seq.pop_back();	
			}
			swap(Q[0],Q[1]);
			while(Q[1].size())Q[1].pop();
		}

		while(!Q[0].empty()){
			data d = Q[0].top();Q[0].pop();
			if(d.subscore > ret){
				ret = d.subscore;
				for(int q = 0; q < N; q++){
					if(d.seq[q] == -1)final.push_back(Placement(q,true));
					else final.push_back(V[q][d.seq[q]].second);
				}
			}
			break;
		}
	}
	for(int q = 0; q < N; q++){
		final[q].Out();
	}
}


int main(){
	F.In();
	cin >> N;
	ll prm[1024] = {0};
	for(int q = 0; q < N; q++){
		blocks[q].In();
		int c = 0;
		Pii w,h;
		w.first = INF;
		w.second = 0;
		h.first = INF;
		h.second = 0;
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if(blocks[q][i][j]){
					h.first = min(h.first,i);
					h.second = max(h.second,i);
					w.first = min(w.first,j);
					w.second = max(w.second,j);
					szStone[q]++;
				}
			}
		}
		prm[q] = ((ll)(w.second-w.first))*((ll)(h.second-h.first));
	}
	multiset < ip > _V[N+10];
	for(int q = 0 ; q < N; q++){
		for(int i = -7; i < H; i++){
			for(int j = -7; j < W; j++){
				for(int d = 0; d < 4; d++){
					//printf("# -> %d\n",prm[q]*szStone[q]);
					Placement p1 = Placement(q,j,i,0,d,0);
					if(F.CanPut(p1)){
						_V[q].insert(ip(prm[q]*szStone[q],p1));
					}
					Placement p2 = Placement(q,j,i,1,d,0);
					if(F.CanPut(p2)){
						_V[q].insert(ip(prm[q]*szStone[q],p2));
					}
				}
			}
		}
	}

	for(int q = 0; q < N; ++q){
		copy(_V[q].begin(), _V[q].end(), inserter(V[q], V[q].begin())); 
	}

	solve();

	return 0;
}