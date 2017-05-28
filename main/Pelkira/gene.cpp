#include<bits/stdc++.h>
using namespace std;
int W,H,N;
string sc[50];
const int dx[] = {0,1,0,-1},dy[] = {1,0,-1,0};
bool vis[50][50];
void dfs(int x,int y){
	vis[y][x] = true;
	for(int i = 0;i < 4;i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(nx < 0 || W <= nx || ny < 0 || H <= ny)continue;
		if(sc[ny][nx] == '1' || vis[ny][nx])continue;
		dfs(nx,ny);
	}
}
bool check(){
	for(int i = 0;i < 50;i++){
		for(int j = 0;j < 50;j++){
			vis[i][j] = false;
		}
	}
	for(int i = 0;i < H;i++){
		for(int j = 0;j < W;j++){
			if(!vis[i][j]){
				dfs(j,i);
				goto next;
			}
		}
	}
	next:;
	bool flg = false;
	for(int i = 0;i < H;i++){
		for(int j = 0;j < W;j++){
			if(!vis[i][j] && sc[i][j] == '0'){
				return true;
			}
		}
	}
	return false;
}

bool blocks[4000000][8][8];
int border[20];
int siz[4000000];
int main(){
	cin>>W>>H>>N;
	int obsRate,minB,maxB;
	cin>>obsRate>>minB>>maxB;
	for(int i = 0;i < 32;i++){
		sc[i] = "";
		for(int j = 0;j < 32;j++){
			sc[i] += (i < H && j < W ? "0" : "1");
		}
	}
	srand(time(NULL));
	int Q = obsRate * W * H / 100;
	for(int q = 0;q < Q;q++){
		int x = rand()%W,y = rand()%H;
		if(sc[y][x] == '1'){
			q--;
			continue;
		}
		sc[y][x] = '1';
		if(check()){
			sc[y][x] = '0';
			q--;
		}
	}
	for(int i = 0;i < 32;i++){
		cout<<sc[i]<<endl;
	}
	cout<<endl<<N<<endl;
    FILE *fp;
    char filename[] = "blocks13.txt";
    if ((fp = fopen(filename, "r")) == NULL) {
    	cout<<"!"<<endl;
    }
    fill(border,border + 20,-1);
    char c;
    int cnt = 0;
    while(true){
	    for(int i = 0;i < 8;i++){
	    	for(int j = 0;j < 8;j++){
	    		c = fgetc(fp);
	    		if(c == '\r' || c == '\n'){
	    			j--;
	    			continue;
	    		}
	    		if(c == EOF){
	    			goto end;
	    		}
	    		blocks[cnt][i][j] = c - '0';
	    		siz[cnt] += blocks[cnt][i][j];
	    	}
	    }
	    if(border[siz[cnt]] == -1)border[siz[cnt]] = cnt;
	    cnt++;
	}
    end:;
    cnt++;
    for(int q = 0;q < N;q++){
        int s = minB + rand() % (maxB - minB + 1);
        int len = border[s];
        if(len != 0)len -= border[s-1];
    	int r = border[s] + rand() % len;
    	if(true){//minB <= siz[r] && siz[r] <= maxB){
    		cout<<endl;
    		for(int i = 0;i < 8;i++){
    			for(int j = 0;j < 8;j++){
    				cout<<blocks[r][i][j];
    			}
    			cout<<endl;
    		}
    	}
    }
}
