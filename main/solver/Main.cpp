#include "bits/stdc++.h"
#include "Field.h"
#include "Block.h"
#include "Placement.h"
#include "ZobristHashing.h"
#include "BeamSearch.h"

using namespace std;

typedef unsigned long long ull;

//const
const int stoneSizeMax = 256;
const int BEAM_SEARCH_HIGH = 300;
const int BEAM_SEARCH_MED = 150;
const int BEAM_SEARCH_LOW = 50;

//global 
int W, H, N;
Field f; //start field
Block blocks[300]; //blocks which use in search part
vector < BeamSearch::PutData > BeamSearch::V[256];
double BeamSearch::ave[256];

void in(){
	f.in();
	H = f.getHeight();
	W = f.getWidth();
	//cout << H << " " << W << "\n";
	scanf("%d", &N);

	for (int q = 0; q < N; ++q){
		blocks[q].in();
	}

	int sum = 0;

	for (int q = 0; q < N; ++q){
		sum += blocks[q].getZk();
	}

	for (int q = 0; q < N; ++q){
		if (q == N - 1){
			BeamSearch::ave[q] = 0.0;
			continue;
		}
		sum -= blocks[q].getZk();
		BeamSearch::ave[q] = (double)sum / (double)(N-q-1);
	}

	return;
}

void createPlacements(){
	
	multiset < BeamSearch::PutData > _V[stoneSizeMax];
	Utility u;
	u.initXor128();
	for (int q = 0; q < N; ++q){
		for (int y = -7; y < H; ++y){
			for (int x = -7; x < W; ++x){
				for (int dir = 0; dir < 4; ++dir){
					
					//線形和で各Placementに事前評価値を入れる
					
					Placement p1 = Placement(blocks[q], x, y, 0, dir, false);
					if (f.canPut(p1)){
						_V[q].insert(BeamSearch::PutData(p1, 0.0));
					}
					Placement p2 = Placement(blocks[q], x, y, 1, dir, false);
					if (f.canPut(p2)){
						_V[q].insert(BeamSearch::PutData(p2, 0.0));
					}
				}
			}
		}
	}

	for (int q = 0; q < N; ++q){
		copy(_V[q].begin(), _V[q].end(), inserter(BeamSearch::V[q], BeamSearch::V[q].begin()));
	}
	/*
	for(int q = 0; q < N; ++q){
		random_shuffle(BeamSearch::V[q].begin(),BeamSearch::V[q].end());
	}*/
}


int main(int argc, char *argv[]){
	srand(time(NULL));
	int t = clock();

	//引数を調べる
	vector < string > optionLists = { "-answer", "-GA", "-file", "-check" };
	
	string option = "";
	if(argc > 1)option= argv[1];
	bool isCorrectOption = false;
	
	for (int i = 0; i < optionLists.size(); ++i){
		if (option == optionLists[i]){
			isCorrectOption = true;
		}
	}

	if (argc == 1)isCorrectOption = true;

	if (!isCorrectOption){
		cout << "Option Error!" << "\n";
		exit(0);
	}


	//input 
	//最初の入力
	in();

	//Placemets
	//すべての置き方の列挙
	//事前に評価値を振るならここ
	createPlacements();

	//beamSearch
	//探索を実際に始める
	BeamSearch beamsearch = BeamSearch(H, W, N, f);
	beamsearch.init(f.getZk());
	
	bool GAflg = false;

	if (option == "-GA"){
		double f_pass = atof(argv[2]);
		double f_cir = atof(argv[3]);
		double f_hole = atof(argv[4]);
		double m_pass = atof(argv[5]);
		double m_cir = atof(argv[6]);
		double m_hole = atof(argv[7]);
		if (argc == 9 && std::strcmp(argv[8], "-answer") == 0){
			GAflg = true;
		}
		beamsearch.run(f_pass,f_cir,f_hole,m_pass,m_cir,m_hole);
	}
	else{
		beamsearch.run(Utility::INF, Utility::INF, Utility::INF, Utility::INF, Utility::INF, Utility::INF);
	}

	if (GAflg){
		option = "-answer";
	}

	if (option == "-check" || option == "-answer" || option == "-GA" || option == ""){
		beamsearch.out(option);
	}
	else if (option == "-file"){
		beamsearch.out(option, argv[2]);
	}
	//printf("%d\n", clock() - t);
	return 0;
}
