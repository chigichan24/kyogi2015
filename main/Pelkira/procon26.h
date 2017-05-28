/*
	version 2.0
	add function(s) -> major update
	bug fix ->minor update
*/
#include<bits/stdc++.h>
using namespace std;
extern int W,H,N;
class Block{
public:
	bool sc[10][10];
	bool *operator[](int i){
		return sc[i];
	}
	Block(){
		for(int i = 0;i < 10;i++){
			for(int j = 0;j < 10;j++){
				sc[i][j] = 0;
			}
		}
	}
	Block Clone(){
		Block B;
		for(int i = 0;i < 8;i++){
			for(int j = 0;j < 8;j++){
				B[i][j] = sc[i][j];
			}
		}
		return B;
	}
	void Rotate(int angle){
		if(90 <= angle)angle /= 90;
		angle %= 4;
		while(angle--){
			for(int i = 0;i < 4;i++){
				for(int j = 0;j < 4;j++){
					bool sub = sc[i][j];
					sc[i][j] = sc[7 - j][i];
					sc[7 - j][i] = sc[7 - i][7 - j];
					sc[7 - i][7 - j] = sc[j][7 - i];
					sc[j][7 - i] = sub;
				}
			}
		}
	}
	void Frip(){
		for(int i = 0;i < 8;i++){
			for(int j = 0;j < 4;j++){
				bool sub = sc[i][j];
				sc[i][j] = sc[i][7 - j];
				sc[i][7 - j] = sub;
			}
		}
	}
	void In(){
		for(int i = 0;i < 8;i++){
			char s[10];
			scanf("%s",s);
			for(int j = 0;j < 8;j++){
				sc[i][j] = s[j] - '0';
			}
		}
	}
	void Out(){
		for(int i = 0;i < 8;i++){
			for(int j = 0;j < 8;j++){
				printf("%d",sc[i][j]);
			}
			printf("\n");
		}
	}
};
extern Block blocks[300];
class Placement{
public:
	int id;
	bool isPassed;
	int x,y,frip,dir;
	bool operator==(Placement P){
		Block A = blocks[id].Clone();
		Block B = blocks[P.id].Clone();
		if(frip)A.Frip();
		if(P.frip)B.Frip();
		A.Rotate(dir);
		B.Rotate(P.dir);
		for(int i = 0;i < 8;i++){
			for(int j = 0;j < 8;j++){
				int Y = P.y - y;
				int X = P.x - x;
				if (Y < 0 || 8 <= Y || X < 0 || 8 <= X)
                {
                    if (A[i][j])return false;
                }
				if(A[i][j] != B[i+Y][j+X])return false;
			}
		}
		return true;
	}
	Placement(){
		x = y = frip = dir = isPassed = 0;
		id = -1;
	}
	Placement(int _id,bool _p){
		id = _id,isPassed = _p;
	}
	Placement(int _id,int _x,int _y,int _f,int _d,bool _p){
		id = _id,x = _x,y = _y,frip = _f,dir = _d,isPassed = _p;
	}
	void Out(){
		if(isPassed)printf("\n");
		else printf("%d %d %c %d\n",x,y,frip ? 'T' : 'H',dir);
	}
};
class Field{
public:
	int sc[50][50];
	int zk;
	int stn;
	int *operator[](int i){
		return sc[i];
	}
	bool operator<(Field F){
		return zk == F.zk ? stn < F.stn : zk < F.zk;
	}
	bool operator>(Field F){
		return zk == F.zk ? stn > F.stn : zk > F.zk;
	}
	bool operator==(Field F){
		for(int i = 0;i < H;i++){
			for(int j = 0;j < W;j++){
				if(F[i][j] != sc[i][j])return false;
			}
		}
		return true;
	}
	bool operator<=(Field F){
		return zk == F.zk ? stn <= F.stn : zk <= F.zk;
	}

	bool operator>=(Field F){
		return zk == F.zk ? stn >= F.stn : zk >= F.zk;
	}
	Field Clone(){
		Field F;
		for(int i = 0;i < H;i++){
			for(int j = 0;j < W;j++){
				F[i][j] = sc[i][j];
			}
		}
		F.stn = stn;
		F.zk = zk;
		return F;
	}
	bool CanPut(Placement P){
		Block B = blocks[P.id].Clone();
		if(P.frip)B.Frip();
		B.Rotate(P.dir);
		bool flg = true;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (i + P.y < 0 || H <= i + P.y || j + P.x < 0 || W <= j + P.x)
                {
                    if (B[i][j]) flg = false;
                    continue;
                }
                if (B[i][j] && sc[i + P.y][j + P.x] != 0) flg = false;
            }
        }
        return flg;
    }
    bool isConnected(Placement P){
		Block B = blocks[P.id].Clone();
		if(P.frip)B.Frip();
		B.Rotate(P.dir);
		bool flg = false;
        int dx[] = { 0, 1, 0, -1 };
        int dy[] = { 1, 0, -1, 0 };
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    int nx = P.x + dx[k];
                    int ny = P.y + dy[k];
                    if (j + nx < 0 || W <= j + nx || i + ny < 0 || H <= i + ny) continue;
                    if (B[i][j] && sc[i + ny][j + nx] == 2) flg = true;
                }
            }
        }
        return flg;
    }
    bool Put(Placement P, bool isCount){
    	//connect undone
    	if(!CanPut(P))return false;
		Block B = blocks[P.id].Clone();
		if(P.frip)B.Frip();
		B.Rotate(P.dir);
		for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (i + P.y < 0 || H <= i + P.y || j + P.x < 0 || W <= j + P.x)
                {
                    continue;
                }
                if(B[i][j]){
                	sc[i + P.y][j + P.x] = 2;
                	if(isCount)zk--;
                }
            }
        }
        if(isCount){
        	stn++;
    	}
        return true;
    }

	void In(){
		zk = 32*32;
		for(int i = 0;i < 32;i++){
			char s[50];
			scanf("%s",s);
			for(int j = 0;j < 32;j++){
				sc[i][j] = (s[j] - '0');
				zk -= sc[i][j];
			}
		}

		int _W = 32;
	    for (int i = _W - 1; i >= 0; i--)
	    {
	        bool flg = true;
	        for (int j = 0; j < 32; j++)
	        {
	            if (sc[j][i] == 0) flg = false;
	        }
	        if (!flg || i == 0)
	        {
	            _W = i + 1;
	            break;
	        }
	    }
	    int _H = 32;
        for (int i = _H - 1; i >= 0; i--)
        {
            bool flg = true;
            for (int j = 0; j < 32; j++)
            {
                if (sc[i][j] == 0) flg = false;
            }
            if (!flg || i == 0)
            {
                _H = i + 1;
                break;
            }
        }
        W = _W,H = _H;
	}
	void Out(){
		for(int i = 0;i < H;i++){
			for(int j = 0;j < W;j++){
				printf("%d",sc[i][j]);
			}
			printf("\n");
		}
	}
};