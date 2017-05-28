#include "Field.h"
int Field::getDepth(int y, int x){
	visited[y] |= 1LL << x;
	int dy[] = { 1, 0, -1, 0 };
	int dx[] = { 0, 1, 0, -1 };
	int ret = 0;
	for (int dir = 0; dir < 4; ++dir){
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		if (ny < 0 || Height <= ny || nx < 0 || Width <= nx)continue;
		if (1 & (this->state[ny] >> nx)){
			isTrueHole = true;
			continue;
		}
		if (1 & (this->visited[ny] >> nx)){
			continue;
		}
		
		
		ret += 1 + getDepth(ny, nx);
	}
	return ret;
}

void Field::calcHole(Placement p,int &one,int &two){
	holes.clear();
	for (int i = 0; i < 32; ++i){
		visited[i] = 0LL;
		state[i] = 0LL;
	}

	for (int i = 0; i < Height; ++i){
		ull tmp = (this->obstacleRow[i] | this->fieldRow[i]);
		for (int j = 0; j < Width; ++j){
			if (1&(tmp>>j)){
				visited[i] |= (1LL << j);
			}
		}
	}


	for (int i = 0; i < Height; ++i){
		state[i] = p.block.blockRow[i];
	}

	/*puts("*****************************************************");

	for (int i = 0; i < Height; ++i){
		for (int j = 0; j < Width; ++j){
			printf("%d", (state[i]>>j&1)? 2 : fieldRow[i] >> j & 1 ? 1 : 0);
		}
		puts("");
	}*/

	for (int i = 0; i < Height; ++i){
		for (int j = 0; j < Width; ++j){
			if (!(1&((this->visited[i])>>j))){
		//		printf("[%d,%d] ", i, j);
				isTrueHole = false;
				int cnt = getDepth(i,j) + 1;
				if (cnt == 1){
					(one)++;
				}
				if (cnt == 2){
					(two)++;
				}
				if (isTrueHole){
					this->holes.push_back(cnt);
			//		printf("%d\n", cnt);
				}
			}
		}
	}
	std::sort(this->holes.begin(), this->holes.end());
	/*
	puts("");

	for (int i = 0; i < Height; ++i){
		for (int j = 0; j < Width; ++j){
			if (1 & ((this->fieldRow[i]|this->obstacleRow[i]) >> j)){
				if (1 & (p.block.blockRow[i] >> j)){
					printf("2");
				}
				else{
					printf("1");
				}
			}
			else{
				printf("0");
			}
		}
		puts("");
	}

	for (int i = 0; i < holes.size(); ++i){
		printf("%d ", holes[i]);
	}
	puts("");
	*/
	if (this->holes.size() == 1 && this->holes[0] > 10){
		this->holes.clear();
	}
	return;
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
	for (int i = 0; i < 32; ++i){
		if (this->fieldCol[i] != f.fieldCol[i])return false;
	}
	return true;
}

Field& Field::operator=(Field f)
{
	for (int i = 0; i < Height; ++i){
		this->fieldRow[i] = f.fieldRow[i];
	}
	for (int j = 0; j < Width; ++j){
		this->fieldCol[j] = f.fieldCol[j];
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
		f.fieldRow[i] = fieldRow[i];
	}

	for (int j = 0; j < Width; ++j){
		f.fieldCol[j] = fieldCol[j];
	}

	for (int i = 0; i < Height; ++i){
		f.obstacleRow[i] = obstacleRow[i];
	}

	for (int j = 0; j < Width; ++j){
		f.obstacleCol[j] = obstacleCol[j];
	}

	f.Height = Height;
	f.Width = Width;
	f.stn = stn;
	f.zk = zk;
	f.circumference = circumference;
	f.holes = holes;
	return f;
}

//placementÇ…è]Ç¡ÇƒblockÇshiftÇµÅCobst,fieldÇ∆&Ç≈false
bool Field::canPut(Placement p)
{
	if (!p.canUse){
		return false;
	}
	for (int i = 0; i < 32; ++i){
		if ((this->fieldRow[i])&(p.block.blockRow[i]))return false;
		if ((this->obstacleRow[i])&(p.block.blockRow[i]))return false;
	}
	return true;
}

//4ï˚å¸shiftÇÃÇ§ÇøÇ«ÇÍÇ©Ç≈fieldÇ∆ÇÃ|Ç™true
bool Field::isConnected(Placement p)
{

	if (!p.canUse){
		return false;
	}

	ull row[32];
	ull column[32];

	for (int i = 0; i < 32; ++i){
		row[i] = p.block.blockRow[i];
		column[i] = p.block.blockCol[i];
	}
	
	//4dir shift
	for (int i = 0; i < Width; ++i){
		column[i] <<= 1;
		if (fieldCol[i] & column[i])return true;
	}
	for (int i = 0; i < 32; ++i){
		column[i] = p.block.blockCol[i];
	}
	for (int i = 0; i < Width; ++i){
		column[i] >>= 1;
		if (fieldCol[i] & column[i])return true;
	}

	for (int j = 0; j < Height; ++j){
		row[j] <<= 1;
		if (fieldRow[j] & row[j])return true;
	}

	for (int j = 0; j < 32; ++j){
		row[j] = p.block.blockRow[j];
	}

	for (int j = 0; j < Height; ++j){
		row[j] >>= 1;
		if (fieldRow[j] & row[j])return true;
	}


	return false;
}

//fieldÇ∆ÇÃ|
bool Field::put(Placement p, bool isCount)
{
	if (!canPut(p)){
		return false;
	}

	if (!p.canUse){
		return false;
	}

	//cirÇãÅÇﬂÇÈÇÃÇO(WH)Ç∂Ç·Ç»Ç¢Ç‚Ç¬ÇçlÇ¶ÇƒÅD
	int dy[] = { 1, 0, -1, 0 };
	int dx[] = { 0, 1, 0, -1 };
	for (int y = 0; y < Height; ++y){
		for (int x = 0; x < Width; ++x){
			if (1 & (p.block.blockRow[y] >> x)){
				for (int dir = 0; dir < 4; ++dir){
					int ny = y + dy[dir];
					int nx = x + dx[dir];
					if (ny < 0 || Height <= ny || nx < 0 || Width <= nx){
						(this->circumference)--;
					}
					else if (1 & ((fieldRow[ny] | obstacleRow[ny]) >> nx)){
						(this->circumference)--;
					}
				}
				fieldRow[y] |= 1LL << x;
				fieldCol[x] |= 1LL << y;
			}
		}
	}

	(this->circumference) += p.block.getCircumference();

	/*
	puts("*************************************");

	for (int i = 0; i < Height; ++i){
		for (int j = 0; j < Width; ++j){
			printf("%d", 1 & (fieldRow[i] | obstacleRow[i]) >> j);
		}
		puts("");
	}

	std::cout << (this->circumference) << "\n";
	*/
	if (isCount){
		zk -= p.block.getZk();
	}
	
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
	return circumference;
}

int Field::getZk(){
	return zk;
}

std::vector<int> Field::getHole(Placement p,int &one,int &two){
	calcHole(p,one,two);
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
			int tmp = sub[j] - '0';
			if (tmp){
				obstacleRow[i] |= 1LL << j;
				obstacleCol[j] |= 1LL << i;
			}
			zk -= tmp;
		}
	}


	for (int j = WIDTHMAX - 1; j >= 0; --j){
		bool flagment = true;
		for (int i = 0; i < HEIGHTMAX; ++i){
			if (!(1&(obstacleRow[i]>>j))){
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
			if (!(1&(obstacleRow[i]>>j))){
				flagment = false;
			}
		}
		if (!flagment || i == 0){
			_H = i + 1;
			break;
		}
	}

	int dy[] = { 1, 0, -1, 0 };
	int dx[] = { 0, 1, 0, -1 };


	ull memo[32];
	int c = 0;
	for (int i = 0; i < 32; ++i){
		memo[i] = 0LL;
	}

	for (int y = 0; y < Height; ++y){
		for (int x = 0; x < Width; ++x){
			if (1 & (obstacleRow[y] >> x)){
				for (int dir = 0; dir < 4; ++dir){
					int ny = y + dy[dir];
					int nx = x + dx[dir];

					if (ny < 0 || Height <= ny || nx < 0 || Width <= nx)continue;
					if (1 & (memo[ny] >> nx)){
						c-=2;
					}
					c++;
				}
				memo[y] |= 1LL << x;
			}
		}
	}
	circumference = c;
	Width = _W;
	Height = _H;
	return;
}

void Field::out()
{
	for (int i = 0; i < Height; ++i){
		for (int j = 0; j < Width; ++j){
			printf("%d", 1 & (fieldRow[i] >> j));
		}
		printf("\n");
	}
	return;
}

