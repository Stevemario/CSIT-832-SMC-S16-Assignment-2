//Los Angeles Valley College
//CSIT 832
//Spring 2016
//Steve Mario Correa
//Assignment 2
//This software manages GenghisAir flights using graphs to represent the
//available flights.
#include <vector>
class city;
class connection {
	public: city* destination;
	public: int distance;
};
class city {
	private: std::string sName;
	private: std::vector <connection*> connections;
};
void loadVerticesEdgesAndWeights (std::vector<city>& cities);
void main () {
	std::vector<city> cities;
	loadVerticesEdgesAndWeights (cities);
}
//Loads, as vertices, cities,
//loads, as edges, connections, and
//loads, as weights, distances in miles between two connected cities,
//and saves all that information into my cities vector.
void loadVerticesEdgesAndWeights (std::vector<city>& cities) {
}