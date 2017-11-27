///meta class header file for Genetic Algorithm
///author: HU FANGYUAN
///2017.11~
#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <random>
#include <unordered_map>

template <typename T>
class Generation{
public:
	typedef pair<float,T*> pft;
	explicit Generation(const std::vector<T*>& _units) : num(_units.size()), units(_units) {srand(time(NULL));}
	~Generation(){}
	
	void rival(int t){
		std::random_shuffle(units.begin(), units.end());
		std::vector<pft> scores(num,{0,nullptr});
		for(size_t i=0;i<num;i++) scores[i].second = units[i];
		while(t--){
			for(size_t i=0;i<num;i++) {
				const size_t j = rand() % num;
				challenge(i, j, scores);
			}
		}
		std::sort(scores.begin(), scores.end(), std::greater<pft>());
		for(size_t i=0;i<num;i++) units[i] = scores[i].second;
	}
	void survival(){
		std::random_shuffle(units.begin(), units.end());
		std::vector<pft> scores(num,{0,nullptr});
		for(size_t i=0;i<num;i++) {
			scores[i].second = units[i];
			scores[i].first = units[i]->perform();
		}
		std::sort(scores.begin(), scores.end(), std::greater<pft>());
		for(size_t i=0;i<num;i++) units[i] = scores[i].second;
	}
	template <typename Distribution, typename Engine>
	void mutate(int t, const typename Distribution::param_type& pram){
		Engine generator;
		Distribution distrib(pram);
		while(t--){
			size_t id = static_cast<size_t>(distrib(generator));
			units[id]->mutate();
		}
	}
	void eliminate_breed(size_t t, float(*die_possibility)(size_t)){
		t = std::min(t, num-1);
		std::unordered_map<size_t,int> death_list;
		while(death_list.size() < t){
			size_t i = rand() % num;
			if(death_list.count(i)) continue;
			float roll = float(rand()) / RAND_MAX;
			if(roll <= die_possibility(i)) death_list[i]++;
		}
		for(auto it=death_list.begin();it!=death_list.end();++it){
			size_t i = rand() % num;
			while(death_list.count(i)) i = rand() % num;
			units[it->first]->T(*units[i]);
		}
	}
private:
	template <typename P>
	inline void challenge(const size_t a, const size_t b, const std::vector<P>& scores) const{
		if(units[a]->challenge(units[b])) {
			const auto pt = a_beat_b(a, b, scores.first[a], scores.first[b]);
			scores.first[a] += pt;
			scores.first[b] -= pt;
		}
		else {
			const auto pt = a_beat_b(b, a, scores.first[b], scores.first[a]);
			scores.first[b] += pt;
			scores.first[a] -= pt;
		}
	}
	template <typename S>
	inline const S a_beat_b(const size_t a, const size_t b, const S sa, const S sb) const{
		return 1 / (1 + exp(sa-sb));
	}

	size_t num;
	std::vector<T*>& units;
};