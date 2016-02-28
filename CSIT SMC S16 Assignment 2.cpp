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
	private: std::string name;
	private: std::vector <connection*> connections;
	public: city (std::string);
};
void loadVerticesEdgesAndWeights (std::vector<city>& cities);
void parseFile (
	std::string&,
	std::vector<std::string>&,
	std::vector<std::string>&,
	std::vector<int>&
);
void fill (
	std::vector<city>&,
	const std::vector<std::string>&
);
void main () {
	std::vector<city> departureCities;
	loadVerticesEdgesAndWeights (departureCities);
}
city::city (std::string cityName) {
	name = cityName;
}
//Loads, as vertices, cities,
//loads, as edges, connections, and
//loads, as weights, distances in miles between two connected cities,
//and saves all that information into my cities vector.
void loadVerticesEdgesAndWeights (std::vector<city>& departureCities) {
	std::string sFilePlaceHolder =
		"Los Angeles, San Diego, Phoenix, Las Vegas, San Fransisco\n"
		"San Diego, Tucson, Phoenix, Los Angeles\n"
		"Tucson, Phoenix, San Diego\n"
		"Phoenix, Tucson, Las Vegas, Los Angeles, San Diego\n"
		"Las Vegas, Phoenix, San Francisco, Los Angeles\n"
		"San Francisco, Los Angeles, Las Vegas\n";
	std::vector<std::string> departureCitiesNames;
	std::vector<std::string> departureCitiesConnectionNames;
	std::vector<int> departureCitiesConnectionAmounts;
	parseFile (
		sFilePlaceHolder,
		departureCitiesNames,
		departureCitiesConnectionNames,
		departureCitiesConnectionAmounts
	);
	fill (departureCities, departureCitiesNames);
}
void parseFile (
	std::string& sFilePlaceHolder,
	std::vector<std::string>& departureCitiesNames,
	std::vector<std::string>& departureCitiesConnectionNames,
	std::vector<int>& departureCitiesConnectionAmounts
) {
	std::string cityName;
	char chRead;
	bool bEditingCityName = true;
	int nConnections = 0;
	while (sFilePlaceHolder.empty () != true) {
		chRead = sFilePlaceHolder[0];
		sFilePlaceHolder.erase (0, 1);

		if (chRead == ',') {
			if (bEditingCityName) {
				bEditingCityName = false;
				departureCitiesNames.push_back (cityName);
				cityName.clear ();
			} else {
				departureCitiesConnectionNames.push_back (cityName);
				nConnections++;
				cityName.clear ();
			}
		} else if (chRead == '\n') {
			departureCitiesConnectionNames.push_back (cityName);
			nConnections++;
			cityName.clear ();
			departureCitiesConnectionAmounts.push_back (nConnections);
			nConnections = 0;
			bEditingCityName = true;
		} else
			cityName += chRead;
	}
}
void fill (
	std::vector<city>& departureCities,
	const std::vector<std::string>& departureCitiesNames
) {
	int nDepartureCities = departureCitiesNames.size ();
	for (int nCity = 0; nCity < nDepartureCities; nCity++) {
		departureCities.push_back (city (departureCitiesNames[nCity]));
	}
}