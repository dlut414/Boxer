///meta class header file for Genetic Algorithm
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>

template <typename T>
class Generation{
public:
	Generation(const int n=1000) : num(n){}
	~Generation(){}
	void generate(){
		units = std::vector<T>(num, T());
	}
	void rival(){
		
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