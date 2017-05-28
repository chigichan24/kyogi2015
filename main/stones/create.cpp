#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/param.h>
#include <windows.h>
using namespace std;
const int dx[]={1,0,0,-1,1,-1,-1,1,2,0,-2,0};
const int dy[]={0,1,-1,0,1,1,-1,-1,0,2,0,-2};
const int INF = 1<<30;
const double EPS = 1e-8;
#define ll unsigned long long
#define PB push_back
#define mk make_pair
#define fr first
#define sc second
#define reps(i,j,k) for(ll i = (j); i < (k); i++)
#define rep(i,j) reps(i,0ll,j)
#define MOD 1000000007
#define lengthof(x) (sizeof(x) / sizeof(*(x)))
#define MAXMEMORY 2075000000
#define BLOCKHEIGHT 8
#define BLOCKWIDTH 8
const ll HEIGHTMASK = 255ll;
const ll WIDTHMASK = 72340172838076673ll;
const ll BLOCKFILLED = -1ll;
#define NG 0ll
typedef pair<int,int> Pii;
typedef pair<ll,Pii> P;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector <Pii> vp;

struct info_t{
    DWORD cb;
    DWORD PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
};
typedef BOOL(WINAPI*func_t)(HANDLE,info_t*,DWORD);
static func_t func; static enum{FIRST ,OK,ERR} flag;
static HANDLE proc; info_t info; HINSTANCE dll;

struct data{
    int depth;
    ll state;
    Pii shift;
    data(){}
    data(int _depth,ll _state, Pii _shift){
        depth = _depth;
        state = _state;
        shift = _shift;
    }
};

int size;
queue < data > Q;
set < ll > memo;
vector < P > ans;
set < ll > mino;

inline void in(){
    scanf("%d",&size);
    return ;
}
inline int workSize(){
    if(flag == FIRST){
        if((dll=LoadLibraryA("psapi"))==0){flag=ERR; return 0;}
        func=(func_t)GetProcAddress(dll,"GetProcessMemoryInfo");
        if(func == 0){flag=ERR; return 0;}
        proc=GetCurrentProcess();flag=OK;
    }
    if(flag==ERR)return 0;
    func(proc,&info,sizeof info);
    return(int)info.WorkingSetSize;
}
inline void holeDfs(int y,int x,ll *visited){
    *visited += 1ll<<(y*8+x);
    int ny,nx;
    int k;
    for(k = 0; k < 4; k++){
        ny = y + dy[k];
        nx = x + dx[k];
        if(ny < 0 || ny > 7 || nx < 0 || nx > 7)continue;
        if(!(1ll&(*visited>>ny*8+nx)))holeDfs(ny,nx,visited);
    }
}
inline bool isHole(ll state){
    ll visited = state;
    int i,j;
    for(i=0;i<BLOCKHEIGHT;++i){
        for(j=0;j<BLOCKWIDTH;++j){
            if(i == 0 || i == 7 || j == 0 || j == 7){
                if(!(1ll&(visited>>(i*8+j)))){
                    holeDfs(i,j,&visited);
                }
            }
        }
    }
    return !(visited==BLOCKFILLED);
}
inline ll close(ll state,int *h,int *w){
    int heightShiftCount = 0;
    int widthShiftCount = 0;
    while(!(WIDTHMASK&state)) {
        state >>= 1;
        widthShiftCount++;
    }
    while(!(HEIGHTMASK&state)) {
        state >>= 8;
        heightShiftCount++;
    }
    *h = heightShiftCount;
    *w = widthShiftCount;
    return state;
}
inline ll close(ll state){
    while(!(WIDTHMASK&state)){
        state >>= 1;
    }
    while(!(HEIGHTMASK&state)){
        state >>= 8;
    }
    return state;
}
inline ll rotate(ll state, int depth){
    if(depth == 0)return state;
    ll sub = 0ll;
    int i,j;
    for(i=0;i<BLOCKHEIGHT;++i){
        for(j=0;j<BLOCKWIDTH;++j){
            if(1&(state>>(i*8+j)))sub += 1ll<<(j*8+7-i);
        }
    }
    return rotate(close(sub),depth-1);
}
inline ll rev(ll state){
    int i,j;
    for(i=0;i<BLOCKHEIGHT;++i){
        for(j=0;j<BLOCKWIDTH/2;++j){
            if((1&state>>(i*8+j))^(1&state>>(i*8+7-j))){
                state ^= 1ll<<(i*8+j);
                state ^= 1ll<<(i*8+7-j);
            }
        }
    }
    return close(state);
}
inline ll getForm(Pii *list,int length,int *H,int *W){
    int minY,minX;
    int maxY,maxX;
    int i,j;
    minY = minX = INF;
    maxY = maxX = -INF;
    for(i=0;i<length;++i){
        minY = min(minY,list[i].fr);
        minX = min(minX,list[i].sc);
        maxY = max(maxY,list[i].fr);
        maxX = max(maxX,list[i].sc);
    }
    *H = maxY - minY + 1;
    *W = maxX - minX + 1;
    if(max(*H,*W)>8){
        return NG;
    }
    ll stonel = 0ll;
    for(i=0;i<length;++i){
        stonel |= 1ll<<((list[i].fr)*8+list[i].sc-minX);
    }
    ll ret = 0ll;
    for(i=0;i<BLOCKHEIGHT;++i){
        for(j=0;j<BLOCKWIDTH;++j){
            if(1ll&stonel>>(i*8+j)){
                ret += 1ll<<(i*BLOCKWIDTH+j);
            }
        }
    }
    int a,b;
    if(isHole(close(ret,&a,&b)))return NG;
    return close(ret);
}
inline ll getForm(Pii *list,int length,int *H,int *W,int *shiftH,int *shiftW){
    int minY,minX;
    int maxY,maxX;
    int i,j;
    minY = minX = INF;
    maxY = maxX = -INF;
    for(i=0;i<length;++i){
        minY = min(minY,list[i].fr);
        minX = min(minX,list[i].sc);
        maxY = max(maxY,list[i].fr);
        maxX = max(maxX,list[i].sc);
    }
    *H = maxY - minY + 1;
    *W = maxX - minX + 1;
    if(max(*H,*W)>8){
        return NG;
    }
    ll stonel = 0ll;
    for(i=0;i<length;++i){
        stonel |= 1ll<<((list[i].fr)*8+list[i].sc-minX);
    }
    ll ret = 0ll;
    for(i=0;i<BLOCKHEIGHT;++i){
        for(j=0;j<BLOCKWIDTH;++j){
            if(1ll&stonel>>(i*8+j)){
                ret += 1ll<<(i*BLOCKWIDTH+j);
            }
        }
    }
    int a,b;
    if(isHole(close(ret,&a,&b)))return NG;
    return close(ret,shiftH,shiftW);
}
inline void init(){
    int depth = 0;
    ll s = 1ll;
    Pii shift = Pii(0,0);
    Q.push(data(depth,s,shift));
    return ;
}
inline bool inField(int y,int x){
    if(y < 0)return false;
    if(y == 0 && x < 0)return false;
    return true;
}
inline bool isSame(int y,int x,Pii *list,int length){
    int i;
    for(i=0;i<length;++i){
        if(y == list[i].fr && x == list[i].sc){
            return true;
        }
    }
    return false;
}
inline bool getStatus(ll state){
    ll s = close(state);
    ll m = rev(s);
    int k;
    for(k=0;k<4;++k){
        ll ns = rotate(s,k);
        ll nm = rotate(m,k);
        if(mino.find(ns) != mino.end()){
            return false;
        }
        if(mino.find(nm) != mino.end()){
            return false;
        }
    }
    mino.insert(s);
    return true;
}

inline void decode(Pii *list, ll state, Pii shift){
    int cnt = 0;
    int i,j;
    for(i=0;i<8;++i){
        for(j=0;j<8;++j){
            if(1&(state>>(i*8+j))){
                list[cnt] = Pii(i+shift.fr,j+shift.sc);
                cnt++;
            }
        }
    }
    return ;
}

inline void bfs(){
    int M = 0;
    data d;
    int shiftH,shiftW;
    int h,w;    
    Pii list[16];
    int y,x;
    int ny,nx;
    ll nextstate;
    int i,k;
    while(!Q.empty()){
        d = Q.front();Q.pop();
        decode(list,d.state,d.shift);
        /*
        if(getStatus(d.state) && d.depth == size-1){
            getForm(list,d.depth+1,&h,&w);
            ans.push_back(P(d.state,Pii(h,w)));
            continue;
        }
        */
        if(d.depth == size-1)continue;
        for(k=0;k<d.depth+1;++k){
            y = list[k].fr;
            x = list[k].sc;
            for(i=0;i<4;++i){
                ny = y + dy[i];
                nx = x + dx[i];
                if(inField(ny,nx) && !isSame(ny,nx,list,d.depth+1)){
                    list[d.depth+1] = Pii(ny,nx);
                    nextstate = getForm(list,d.depth+2,&h,&w,&shiftH,&shiftW);
                    if(nextstate == NG)continue;
                    if(M < d.depth+1){
                        printf("%d\n",M+1);
                        M++;
                        mino.clear();
                        memo.clear();
                    }
                    if(memo.find(nextstate) == memo.end()){
                        memo.insert(nextstate);
                        if(getStatus(nextstate)){
                            if(d.depth+1 == size-1){
                                ans.push_back(P(nextstate,Pii(h,w)));
                                continue;
                            }
                        }
                        if(d.depth+1 == size-1)continue;
                        Q.push(data(d.depth+1,nextstate,Pii(shiftH,shiftW)));
                    }
                }
            }
        }
    }
    return ;
}
inline void outPut(){
    FILE *fp;
    char buf[100],cur[100];
    getcwd(cur,sizeof(cur));
    sprintf(buf,"%s/blocks/%d.txt",cur,size);
    fp = fopen(buf,"w");
    sort(ans.begin(),ans.end());
    int len = ans.size();
    printf("SZ : %d\n",len);
    if(fp == NULL){
        puts("ERROR!!!!");
        return ;
    }
    rep(i,len){
        bool stone[8][8]={{0}};
        int h = ans[i].sc.fr;
        int w = ans[i].sc.sc;
        rep(y,BLOCKHEIGHT){
            rep(x,BLOCKWIDTH){
                if(1&(ans[i].fr>>(y*BLOCKWIDTH+x))){
                    stone[y+(BLOCKHEIGHT-h)/2][x+(BLOCKWIDTH-w)/2] = 1;
                }
            }
        }
        rep(y,BLOCKHEIGHT){
            rep(x,BLOCKWIDTH){
                fprintf(fp, "%d", stone[y][x]);
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return ;
}
int main(){
    in();
    int t = clock();
    init();
    bfs();
    outPut();
    //printf("SZ : %d\n",ans.size());
    printf("TIME : %dms\nMEMORY : %d\n",clock()-t,workSize());
    return 0;
}