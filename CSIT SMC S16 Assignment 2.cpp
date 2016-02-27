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
	std::string sFilePlaceHolder =
		"Los Angeles, San Diego, Phoenix, Las Vegas, San Fransisco\n"
		"San Diego, Tucson, Phoenix, Los Angeles\n"
		"Tucson, Phoenix, San Diego\n"
		"Phoenix, Tucson, Las Vegas, Los Angeles, San Diego\n"
		"Las Vegas, Phoenix, San Francisco, Los Angeles\n"
		"San Francisco, Los Angeles, Las Vegas\n";
}