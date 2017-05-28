#include "bits/stdc++.h"

struct GAData{
	int score,time;
	double f_pass,f_cir,f_hole;
	double m_pass,m_cir,m_hole;
	GAData(){}
	GAData(int score,int time,double f_pass,double f_cir,double f_hole,double m_pass,double m_cir,double m_hole){
		this->score  = score;
		this->time   = time;
		this->f_pass = f_pass;
		this->f_cir  = f_cir;
		this->f_hole = f_hole;
		this->m_pass = m_pass;
		this->m_cir  = m_cir;
		this->m_hole = m_hole;
	}
	bool operator<(const GAData &data)const{
		if(score == data.score)return time<data.time;
		return score < data.score;
	}
};

GAData data[32];
GAData next[32];
int N;
int bestscore;
int besttime;

void init(){

	/*
	pass : 5 < x < 300 , 1刻み
	cir  : -4 < x < 4 , 0.1刻み
	hole :  0 < x < 20 , 0.1刻み
	 */
	
	for(int i = 0; i < N; ++i){
		int a = rand()%295+5;
		int b = rand()%80-40;
		int c = rand()%200;
		int d = rand()%295+5;
		int e = rand()%80-40;
		int f = rand()%200;
		data[i] = GAData(0,0,(double)a,(double)b/10.0,(double)c/10.0,(double)d,(double)d/10.0,(double)f/10.0);
	}

	bestscore = 1e9;
	besttime = 1e9;

	return ;
}

void copy(){
	for(int i = 0; i < N; ++i){
		data[i] = next[i];
	}
	return ;
}

int main(){
	N = 30;
	char problemFile[128];
	scanf("%s",problemFile);
	srand(time(NULL));

	init();
	int cnt = 0;

	while(true){
		for(int i = 0; i < N; ++i){
			char target[256];
			sprintf(target,"Main.exe -GA %lf %lf %lf %lf %lf %lf -answer < %s > out.txt",data[i].f_pass,data[i].f_cir,data[i].f_hole,
					data[i].m_pass,data[i].m_cir,data[i].m_hole,problemFile);
			system(target);
			FILE *fp;
			fp = fopen("./out.txt","r");
			int score,time;
			fscanf(fp,"%d %d",&score,&time);
			data[i].score = score;
			data[i].time = time;
			fclose(fp);
			printf("%d %d\n",score,time);
			if(bestscore > score || (bestscore == score && besttime > time)){
				bestscore = score;
				besttime = time;
				char answerfile[256];
				sprintf(answerfile,"cp ./out.txt ./result/answer%d.txt",cnt);
				
				system(answerfile);	
				++cnt;
			}

			
		}

		std::sort(data,data+N);

		int nextIdx = 0;

		for(int i = 0; i < 3; ++i){
			next[nextIdx] = data[i];
			nextIdx++;
		}

		double p[32];
		std::vector<int> roulette;

		for(int i = 0; i < N; ++i){
			for(int j = 0; j < 1024 - data[i].score; ++j){
				roulette.push_back(i);
			}
		}

		random_shuffle(roulette.begin(),roulette.end());

		for(int i = 0; i < 30; i+=2){
			GAData a = data[roulette[i]];
				GAData b = data[roulette[i+1]];

				if(rand()%2)std::swap(a.f_pass,b.f_pass);
				if(rand()%2)std::swap(a.f_cir,b.f_cir);
				if(rand()%2)std::swap(a.f_hole,b.f_hole);
				if(rand()%2)std::swap(a.m_pass,b.m_pass);
				if(rand()%2)std::swap(a.m_cir,b.m_cir);
				if(rand()%2)std::swap(a.m_hole,b.m_hole);

				next[nextIdx] = a;
				nextIdx++;
		}
		for(int i = 0; i < 5; ++i){
			random_shuffle(roulette.begin(),roulette.end());
			GAData a;
			int tmp = 0;
			a.f_pass = data[roulette[tmp]].f_pass; ++tmp;
			a.f_cir = data[roulette[tmp]].f_cir; ++tmp;
			a.f_hole = data[roulette[tmp]].f_hole; ++tmp;
			a.m_pass = data[roulette[tmp]].m_pass; ++tmp;
			a.m_cir = data[roulette[tmp]].m_cir; ++tmp;
			a.m_hole = data[roulette[tmp]].m_hole; ++tmp;
			next[nextIdx] = a;
			nextIdx++;
		}
		copy();
	}
}