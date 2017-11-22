///meta class header file for Genetic Algorithm
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <algorithm>

template <typename T>
class Generation{
public:
	Generation(const int n=1000) : num(n){}
	~Generation(){}
	void generate(){
		units = std::vector<T>(num, T());
	}
	void rival(){
		std::random_shuffle(units.begin(), units.end());
		typedef std::pair<int,int> pii;
		std::vector<pii> scores_id(num);
		for(int i=0;i<num-1;i+=2){
			if(units[i].challenge(units[i+1])){
				
			}
			else{
				
			}
		}
	}
	void survival(){
		
	}
	void mutate(){
		
	}
	void eliminate(){
		
	}
	void breed(){
		
	}
private:
	int num;
	std::vector<T> units;
};