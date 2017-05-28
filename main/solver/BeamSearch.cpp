#include "BeamSearch.h"

BeamSearch::BeamSearchData::BeamSearchData()
{

}

BeamSearch::BeamSearchData::BeamSearchData(std::vector<int> history, double score, int blank, int circumference,std::vector<int> dbg)
{
	this->history = history;
	this->score = score;
	this->blank = blank;
	this->circumference = circumference;
	this->dbg = dbg;
}

BeamSearch::BeamSearchData::~BeamSearchData()
{

}

bool BeamSearch::BeamSearchData::operator<(const BeamSearchData &data)const
{
	return this->score > data.score;
}


BeamSearch::BeamSearch()
{

}

BeamSearch::BeamSearch(int H,int W,int N,Field f)
{
	this->H = H;
	this->W = W;
	this->N = N;
	this->f = f.clone();
	for(int i = 0; i < 32; ++i){
		for(int j = 0; j < 32; ++j){
			(this->f[i][j]) = f[i][j];
		}
	}
}

BeamSearch::~BeamSearch()
{

}

void BeamSearch::init(int blank)
{
	//puts("INIT\n");
	zobrist = ZobristHashing(H, W);
	zobrist.init();
	utility.initXor128();
	std::vector < int > start;
	Q[0].push(BeamSearchData(start, 1e9,blank,0,start));
	this->step = N;
}

void BeamSearch::run(double f_pass,double f_cir,double f_hole,double m_pass,double m_cir,double m_hole)
{
	//puts("RUN\n");
	while (step--){
		int depth = N - step - 1;
		int times = 40;

		if((double)step < (double)N*0.1){
			times = 200;
		}
		else {

			times = 60;
		}

		memo.clear();
		while (true){

			if (Q[0].size() == 0 || times-- == 0)break;
			BeamSearchData data = Q[0].top(); Q[0].pop();
			/*
			for(int i = 0; i < data.dbg.size(); ++i){
				printf("%d ",data.dbg[i]);
			}
			puts("");
			*/
			Field base = f.clone();

			//復元
			bool isPut = false;
			for (int q = 0; q < data.history.size(); ++q){
				if (data.history[q] == -1)continue;
				base.put(V[q][data.history[q]].placement, true);
				isPut = true;
			}

			//試す
			//#pragma omp parallel
			{
				//#pragma omp for  
				for (int i = 0; i < V[depth].size(); ++i){
					Placement p = V[depth][i].placement;
					//double eval = V[depth][i].eval;
					if (!isPut || base.isConnected(p)){
						Field next = base.clone();
						if (next.put(p, true)){

							ull hashed = zobrist.hash(next.field);
							if (memo.find(hashed) != memo.end())continue;

							////////*評価値の計算ここから*///////


							//まだ埋めていない面積
							int area = next.getZk();
							int diff_area = data.blank - area;

							//周長
							int circumference = next.getCircumference();
							int diff_circumference = circumference - data.circumference;

							//穴となっている面積
							std::vector <int> holes = base.getHole(p);


							//表面の粗さ
							//double roughness = getRoughness(base, next, p.block);

							int hole = 0;
							if (holes.size() > 0){
								hole = holes[0];
							}

							/*if(hole > 0){
								continue;
							}*/

							//printf("%d\n",hole);

							//今のdepth埋めることができるか
							//bool filled = canFill(next, depth + 1, hole);

							double eval = 0.0;

							//外部からの係数の指定なし
							if (f_pass == Utility::INF){
								if ((double)step > N*0.66666){

									if (hole > ave[depth]){
										hole = 0.0;
									}
									eval = (double)area + 0.1*(double)diff_circumference;
									//printf("%d\n",data.circumference - circumference);
								}
								else if ((double)step > N*0.33333){
									if (hole > ave[depth]){
										hole = 0.0;
									}
									eval = (double)area + 0.1*(double)diff_circumference;
								}
								else{
									eval = (double)area;
								}

								////////*評価値の計算ここまで*///////
								
								memo.insert(hashed);
								data.history.push_back(i);
								Q[1].push(BeamSearchData(data.history, eval, area, circumference,holes));
								data.history.pop_back();
							}

							//外部からの係数の指定あり
							else{
								bool pass = false;
								if ((double)step > N*0.6){

									if (hole > ave[depth]){
										hole = 0.0;
									}

									eval = (double)area + f_cir*(double)diff_circumference + f_hole*hole;
									pass = canPass(f_pass);
								}
								else if ((double)step > N*0.1){
									
									if (hole > ave[depth]){
										hole = 0.0;
									}
									pass = canPass(m_pass);
									eval = (double)area + m_cir*(double)diff_circumference + m_hole*hole;
								}
								else{
									eval = (double)area;
								}

								////////*評価値の計算ここまで*///////
								memo.insert(hashed);
									
								if (pass){
									data.history.push_back(-1);
									Q[1].push(BeamSearchData(data.history, eval, area, circumference,holes));
									data.history.pop_back();
								}
								else{
									data.history.push_back(i);
									Q[1].push(BeamSearchData(data.history, eval, area, circumference,holes));
									data.history.pop_back();
								}
							}
						}
					}
				}

				//置かない
				ull hashed = zobrist.hash(base.field);
				if (memo.find(hashed) == memo.end()){
					memo.insert(hashed);
					data.history.push_back(-1);
					std::vector < int > emp;
					emp.push_back(-1);
					Q[1].push(BeamSearchData(data.history, data.blank, data.blank, base.getCircumference(),emp));
					data.history.pop_back();
				}
			}
		}

		swap(Q[0], Q[1]);
		while (Q[1].size())Q[1].pop();
	}
	return;
}

void BeamSearch::out(std::string option)
{
	//puts("OUT");
	int ans = 1e10;
	int blank = 256;
	int cnt = 0;

	while (!Q[0].empty()){
		BeamSearchData data = Q[0].top(); Q[0].pop();
		if (data.score < ans){
			ans = data.score;
			blank = data.blank;
			answer.clear();
			for (int q = 0; q < N; ++q){
				if (data.history[q] == -1){
					answer.push_back(Placement(true));
				}
				else{
					++cnt;
					answer.emplace_back(V[q][data.history[q]].placement);
				}
			}
		}
	}
	if (option == "-check" || option == "-GA"){
		std::cout << blank << " " << cnt << "\n";
	}
	else{
		std::cout << blank << " " << cnt << "\n";
		for (int q = 0; q < answer.size(); ++q){
			answer[q].out();
		}
	}
	return;
}

void BeamSearch::out(std::string option,std::string dir)
{
	//puts("OUT");
	int ans = 1e10;

	while (!Q[0].empty()){
		BeamSearchData data = Q[0].top(); Q[0].pop();
		if (data.score < ans){
			ans = data.score;
			answer.clear();
			for (int q = 0; q < N; ++q){
				if (data.history[q] == -1){
					answer.push_back(Placement(true));
				}
				else{
					answer.emplace_back(V[q][data.history[q]].placement);
				}
			}
		}
	}
	
	FILE *fp;
	char file[128];
	sprintf(file, "%sanswer.txt", dir.c_str());
	
	fp = fopen(file, "w");

	for (int q = 0; q < answer.size(); ++q){
		if (answer[q].isPassed){
			fprintf(fp, "\n");
		}
		else{
			fprintf(fp, "%d %d %c %d\n", answer[q].x, answer[q].y, answer[q].frip ? 'T' : 'H', answer[q].dir * 90);
		}
	}
	fclose(fp);
	std::cout << file << "\n";
	return;
}

double BeamSearch::getRoughness(Field &f, Field &g, Block b){
	int w = f.getCircumference();
	int v = g.getCircumference();
	int m = b.getCircumference();

	double ans = (double)(v - w) / (double)m;
	
	return ans;
}

//idx以降のPlacementでfを埋めることができるか
bool BeamSearch::canFill(Field &f, int idx,double hole){
	if (hole == 0.0)return true;
	for (int q = idx; q < N; ++q){
		for (int i = 0; i < V[q].size(); ++i){
			if (f.canPut(V[q][i].placement)){
				return true;
			}
		}
	}
	return false;
}

// 1/pの確率でtrue
bool BeamSearch::canPass(ull p){
	ull r = utility.xor128();
	if (r % p == 0){
		return true;
	}
	return false;
}
