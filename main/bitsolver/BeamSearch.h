#pragma once
#include "bits/stdc++.h"
#include "Block.h"
#include "Field.h"
#include "Placement.h"
#include "ZobristHashing.h"
typedef unsigned long long ull;

class BeamSearch
{
private:
	//struct
	struct BeamSearchData{
		std::vector < int > history;
		double score;
		int blank;
		int circumference;
		int oneZkHole;
		int twoZkhole;
		BeamSearchData();
		BeamSearchData(std::vector < int > history, double score,int blank,int circumference,int oneZkHole,int twoZkHole);
		~BeamSearchData();
		bool operator<(const BeamSearchData &data)const;
	};
	//const
	const int BEAM_SEARCH_HIGH = 300;
	const int BEAM_SEARCH_MED = 150;
	const int BEAM_SEARCH_LOW = 50;

	//variable
	int H, W, N;
	Field f;
	std::priority_queue < BeamSearchData > Q[2];
	std::set < ull > memo;
	int step;
	std::vector < Placement > answer;

	//method
	bool canFill(Field &f, int idx, double hole);
	double getRoughness(Field &f, Field &g, Block b);
	bool canPass(ull p);


	//ˆêŽž“I‚ÉŽg‚Á‚Ä‚é
	ZobristHashing zobrist;
	Utility utility;

public:
	struct PutData{
		Placement placement;
		double eval;
		PutData(){}
		PutData(Placement placement, double eval){
			this->placement = placement;
			this->eval = eval;
		}
		~PutData(){}
		bool operator<(const PutData &putdata)const{
			return eval < putdata.eval;
		}
	};
	static std::vector < BeamSearch::PutData > V[256]; //placements
	static double ave[256];
	static int onezk[256];
	static int twozk[256];
	BeamSearch();
	BeamSearch(int H, int W, int N, Field f);
	~BeamSearch();
	void init(int blank);
	void run();
	void run(double f_pass, double f_cir, double f_hole, double m_pass, double m_cir, double m_hole);
	void out(std::string option);
	void out(std::string option, std::string dir);
};
