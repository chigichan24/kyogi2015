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

	return ;
}


void copy(){
	for(int i = 0; i < N; ++i){
		data[i] = next[i];
	}
	return ;
}
void save(int cnt,int idx){
	FILE *fp;
	char filename[128];
	sprintf(filename,"./result/answer%d.txt",cnt);
	fp = fopen(filename,"a");
	fprintf(fp,"%d %d %lf %lf %lf %lf %lf %lf\n",data[idx].score,data[idx].time,data[idx].f_pass,data[idx].f_cir,data[idx].f_hole,data[idx].m_pass,data[idx].m_cir,data[idx].m_hole);
	fclose(fp);

	return ;

}

int main(){
	N = 30;
	char str[10];
	scanf("%s",str);
	srand(time(NULL));

	init();
	int cnt = 0;
	while(true){

		for(int i = 0; i < N; ++i){
			FILE *quest;
			char x[30];
			sprintf(x,"quest%s.txt",str);
			quest = fopen(x,"r");
			char target[128];
			sprintf(target,"./Main -GA %lf %lf %lf %lf %lf %lf < %s  > out.txt",data[i].f_pass,data[i].f_cir,data[i].f_hole,
					data[i].m_pass,data[i].m_cir,data[i].m_hole,x);
			fclose(quest);
			system(target);
			FILE *fp;
			fp = fopen("./out.txt","r");
			int score,time;
			fscanf(fp,"%d %d",&score,&time);
			fclose(fp);
			std::cout << score << " " << time << "\n";
			data[i].score = score;
			data[i].time = time;
			save(cnt,i);
		}

		std::sort(data,data+N);
		//ストレートで取る
		
		int nextIdx = 0;

		for(int i = 0; i < 3; ++i){
			next[nextIdx] = data[i];
			nextIdx++;
		}

		//ルーレット
		double p[32];
		std::vector < int > roulette;
		for(int i = 0 ; i < N; ++i){
			for(int j = 0; j < 1024 - data[i].score; ++j){
				roulette.push_back(i);
			}
		}

		random_shuffle(roulette.begin(),roulette.end());

		//上から7はnextにルーレットで入れる
		for(int i = 0; i < 7; ++i){
			next[nextIdx] = data[roulette[i]];
			nextIdx++;
		}

		random_shuffle(roulette.begin(),roulette.end());

		//15は交叉する
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

		//5を突然変異
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
        cnt++;

	}

	return 0;
}


