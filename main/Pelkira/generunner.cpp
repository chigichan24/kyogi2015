#include<bits/stdc++.h>
#include<direct.h>
using namespace std;
string sc[50];
const int dx[] = {0,1,0,-1},dy[] = {1,0,-1,0};
bool vis[50][50];
int W,H,N;
FILE *writer;
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
int cnt;
void Read(){

    FILE *fp;
    char filename[] = "All.txt";
    if ((fp = fopen(filename, "r")) == NULL) {
    	cout<<"!"<<endl;
    }
    fill(border,border + 20,-1);
    char c;
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
    fclose(fp);
}
void Write(char fn[], int obsRate,int minB,int maxB){
    FILE *fp;
    //fp = fopen(fn, "w");
    //_mkdir(fn);
    if ((fp = fopen(fn, "w")) == NULL) {

    }
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
		fprintf(fp,"%s\n",sc[i].c_str());
	}
    fprintf(fp,"\n%d\n",N);
    for(int q = 0;q < N;q++){
        int s = minB + rand() % (maxB - minB + 1);
        int len = border[s];
        if(len != 0)len -= border[s-1];
    	int r = border[s] + rand() % (len+1);
    	if(true){//minB <= siz[r] && siz[r] <= maxB){
            fprintf(fp,"\n");
    		for(int i = 0;i < 8;i++){
    			for(int j = 0;j < 8;j++){
                    fprintf(fp,"%d",blocks[r][i][j]);
    			}
                fprintf(fp,"\n");
    		}
    	}
    }
    fclose(fp);
}
int main(){
	Read();
	_mkdir("quests1");
	for(int i = 0;i < 5;i++){
        int a[] = {8,12,16,24,32};
        char wc[10][10] = {"08","12","16","24","32"};
        int w = a[i];
        for(int j = 0;j < 3;j++){
            if(i+j >= 5)continue;
            int h = a[min(i+j,4)];
            if(j == 2)h = 32;
            char cc[100] = "quests1\\";
            strcat(cc,wc[i]);
            _mkdir(strcat(cc , (j == 2 ? wc[4] : wc[i+j])));
            for(int k = 0;k < 3;k++){
                int c[] = {5,15,25};
                int obs = c[k];
                for(int l = 0;l < 8;l++){
                    int r = l;
                    int mi[] = {1,1,1,3,4,6,8,9};
                    int ma[] = {4,8,13,6,9,13,8,13};
                    int minb = mi[r];
                    int maxb = ma[r];
                    for(int z = 0;z < 4;z++){
                        int S = w*h*(1.00 - obs/100.0);
                        int x = S / (minb+maxb)/1.90;
                        int d[] = {1,2,5,10};
                        int n = x * d[z];
                        n = min(n,256);
                        n = max(n,1);
                        W = w,H = h,N = n;
                        cout<<w<<" "<<h<<" "<<n<<" "<<obs<<" "<<minb<<" "<<maxb<<endl;
                        char s[20] = "";
                        for(int q = 2;q >= 0;q--){
                            s[2 - q] = (n%(int)pow(10,(double)(q+1)))/((int)pow(10,(double)(q))) + '0';
                        }
                        strcat(s,"-");
                        char t[20] = "";
                        for(int q = 1;q >= 0;q--){
                            t[1 - q] = (obs%(int)pow(10,(double)(q+1)))/((int)pow(10,(double)(q))) + '0';
                        }
                        strcat(s,t);
                        strcat(s,"%[");
                        char mis[20] = "",mas[20] = "";
                        for(int q = 1;q >= 0;q--){
                            mis[1 - q] = (minb%(int)pow(10,(double)(q+1)))/((int)pow(10,(double)(q))) + '0';
                            mas[1 - q] = (maxb%(int)pow(10,(double)(q+1)))/((int)pow(10,(double)(q))) + '0';
                        }
                        strcat(s,mis);
                        strcat(s,",");
                        strcat(s,mas);
                        strcat(s,"]");
                        char fn[100] = "";
                        strcat(fn,cc);
                        strcat(fn,"\\");
                        strcat(fn,s);
                        strcat(fn,".txt");
                        //fopen(strcat(cc,,"w");
                        Write(fn,obs,minb,maxb);
                    }
                }
            }
        }
	}
}
