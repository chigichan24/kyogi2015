#include "Field.h"

int Field::getDepth(int y, int x){
	visited[y][x] = 1;
	int dy[] = { 1, 0, -1, 0 };
	int dx[] = { 0, 1, 0, -1 };
	int ret = 0;
	for (int dir = 0; dir < 4; ++dir){
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (ny < 0 || Height <= ny || nx < 0 || Width <= nx)continue;
		if (this->visited[ny][nx] == 1)continue;
		if (this->visited[ny][nx] == 2){
			isTrueHole = true;
			continue;
		}
		ret += 1 + getDepth(ny, nx);
	}
	return ret;
}

void Field::calcHole(Placement p){
	holes.clear();
	for(int i = 0; i < Height; ++i){
		for(int j = 0; j < Width; ++j){
			visited[i][j] = 0;
		}
	}
	for (int i = 0; i < Height; ++i){
		for (int j = 0; j < Width; ++j){
			if (this->field[i][j] != 0){
				visited[i][j] = 1;
			}
		}
	}

	Block A = p.block.clone();
	if (p.frip){
		A.frip();
	}
	A.rotate(p.dir);

	for (int y = 0; y < Block::BLOCKHEIGHT; ++y){
		for (int x = 0; x < Block::BLOCKWIDTH; ++x){
			if (A[y][x]){
				if (y + p.y < 0 || Height <= y + p.y || x + p.x < 0 || Width <= x + p.x)continue;
				visited[y + p.y][x + p.x] = 2;
			}
		}
	}
/*
	puts("*************************************************");

	for(int i = 0; i < Height; ++i){
		for(int j = 0; j < Width; ++j){
			printf("%d",field[i][j]);
		}
		puts("");
	}

	puts("");

	for(int i = 0; i < Height; ++i){
		for(int j = 0; j < Width; ++j){
			printf("%d",visited[i][j]);
		}
		puts("");
	}
*/
	for (int i = 0; i < Height; ++i){
		for (int j = 0; j < Width; ++j){
			if (visited[i][j] == 0){
				isTrueHole = false;
				int cnt = getDepth(i,j) + 1;
				if(isTrueHole)this->holes.push_back(cnt);
			}
		}
	}
	std::sort(this->holes.begin(), this->holes.end());
	if (this->holes.size() == 1 && this->holes[0] > 2){
		this->holes.clear();
	}
	return;
}

int *Field::operator[](int i)
{
	return field[i];
}

bool Field::operator<(Field f)
{
	return zk == f.zk ? stn < f.stn : zk < f.zk;
}

bool Field::operator>(Field f)
{
	return zk == f.zk ? stn > f.stn : zk > f.zk;
}

bool Field::operator<=(Field f)
{
	return zk == f.zk ? stn <= f.stn : zk <= f.zk;
}

bool Field::operator>=(Field f)
{
	return zk == f.zk ? stn >= f.stn : zk >= f.zk;
}

bool Field::operator==(Field f)
{
	for (int i = 0; i < Height; ++i){
		for (int j = 0; j < Width; ++j){
			if (field[i][j] != f[i][j]){
				return false;
			}
		}
	}
	return true;
}

Field& Field::operator=(Field f)
{
	for (int i = 0; i < Height; ++i){
		for (int j = 0; j < Width; ++j){
			this->field[i][j] = f[i][j];
		}
	}
	this->Height = f.Height;
	this->Width = f.Width;
	this->stn = f.stn;
	this->zk = f.zk;
	this->holes = f.holes;
	this->circumference = f.circumference;
	return (*this);
}


Field::Field()
{

}


Field::~Field()
{

}

Field Field::clone()
{
	Field f;
	for (int i = 0; i < Height; ++i){
		for(int j = 0; j < Width; ++j){
			f.field[i][j] = field[i][j];
		}
	}
	f.Height = Height;
	f.Width = Width;
	f.stn = stn;
	f.zk = zk;
	f.circumference = circumference;
	f.holes = holes;
	return f;
}

bool Field::canPut(Placement p)
{
	Block a = p.block.clone();
	if (p.frip){
		a.frip();
	}
	a.rotate(p.dir);
	bool flg = true;
	for (int y = 0; y < Block::BLOCKHEIGHT; ++y){
		for (int x = 0; x < Block::BLOCKWIDTH; ++x){
			if (y + p.y < 0 || Height <= y + p.y || x + p.x < 0 || Width <= x + p.x){
				if (a[y][x]){
					flg = false;
					break;
				}
			}
			if (a[y][x] && field[y + p.y][x + p.x] != 0){
				flg = false;
				break;
			}
		}
		if (!flg){
			break;
		}
	}
	return flg;
}

bool Field::isConnected(Placement p)
{
	Block a = p.block.clone();
	if (p.frip){
		a.frip();
	}
	a.rotate(p.dir);
	bool flg = false;
	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { 1, 0, -1, 0 };

	for (int y = 0; y < Block::BLOCKHEIGHT; ++y){
		for (int x = 0; x < Block::BLOCKWIDTH; ++x){
			for (int dir = 0; dir < 4; ++dir){
				int ny = p.y + dy[dir];
				int nx = p.x + dx[dir];
				if (y + ny < 0 || Height <= y + ny || x + nx < 0 || Width <= x + nx){
					continue;
				}
				if (a[y][x] && field[y + ny][x + nx] == 2){
					flg = true;
					break;
				}
 			}
		}
		if (flg){
			break;
		}
	}

	return flg;
}

bool Field::put(Placement p, bool isCount)
{
	int dy[] = { 1, 0, -1, 0 };
	int dx[] = { 0, 1, 0, -1 };

	if (!canPut(p))return false;
	Block a = p.block.clone();
	if (p.frip)a.frip();
	a.rotate(p.dir);

	for (int y = 0; y < Block::BLOCKHEIGHT; ++y){
		for (int x = 0; x < Block::BLOCKWIDTH; ++x){
			if (y + p.y < 0 || Height <= y + p.y || x + p.x < 0 || Width <= x + p.x){
				continue;
			}
			if (a[y][x]){
				int stagey = y + p.y;
				int stagex = x + p.x;
				field[stagey][stagex] = 2;
				if (isCount)(this->zk)--;
			}
		}
	}
	int cnt = 0;
	for(int y = 0; y < Height; ++y){
		for(int x = 0; x < Width; ++x){
			if(field[y][x]==0){
				for(int dir = 0; dir < 4; ++dir){
					int ny = dy[dir] + y;
					int nx = dx[dir] + x;
					if(ny < 0 || Height <= ny || nx < 0 || Width <= nx){
						cnt++;
						break;
					}
					if(field[ny][nx]){
						cnt++;
						break;
					}
				}
			}
		}
	}

	(this->circumference) = cnt;
	if (isCount){
		++stn;
	}
	return true;
}

int Field::getHeight(){
	return Height;
}

int Field::getWidth(){
	return Width;
}

int Field::getCircumference(){
	int dy[] = {0,1,0,-1};
	int dx[] = {1,0,-1,0};
	int cnt = 0;
	for(int y = 0; y < Height; ++y){
		for(int x = 0; x < Width; ++x){
			if(field[y][x]==0){
				for(int dir = 0; dir < 4; ++dir){
					int ny = dy[dir] + y;
					int nx = dx[dir] + x;
					if(ny < 0 || Height <= ny || nx < 0 || Width <= nx){
						cnt++;
						break;
					}
					if(field[ny][nx]){
						cnt++;
						break;
					}
				}
			}
		}
	}
	(this->circumference) = cnt;
	
	return circumference;
}

int Field::getZk(){
	return zk;
}

std::vector<int> Field::getHole(Placement p){
	calcHole(p);
	return this->holes;
}

void Field::in()
{
	int _H, _W;
	_H = 32;
	_W = 32;
	zk = HEIGHTMAX * WIDTHMAX;
	for (int i = 0; i < HEIGHTMAX; ++i){
		char sub[50];
		scanf("%s", sub);
		for (int j = 0; j < WIDTHMAX; ++j){
			field[i][j] = (sub[j] - '0');
			zk -= field[i][j];
		}
	}
	for (int j = WIDTHMAX - 1; j >= 0; --j){
		bool flagment = true;
		for (int i = 0; i < HEIGHTMAX; ++i){
			if (field[i][j] == 0){
				flagment = false;
			}
		}
		if (!flagment || j == 0){
			_W = j + 1;
			break;
		}
	}
	for (int i = HEIGHTMAX - 1; i >= 0; --i){
		bool flagment = true;
		for (int j = 0; j < WIDTHMAX; ++j){
			if (field[i][j] == 0){
				flagment = false;
			}
		}
		if (!flagment || i == 0){
			_H = i + 1;
			break;
		}
	}
	Width = _W;
	Height = _H;
	return;
}

void Field::out()
{
	for (int i = 0; i < Height; ++i){
		for (int j = 0; j < Width; ++j){
			printf("%d", field[i][j]);
		}
		printf("\n");
	}
	return;
}

