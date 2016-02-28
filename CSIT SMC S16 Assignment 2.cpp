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
	private: city* destination;
	private: int distance;
	public: connection (city*);
};
class city {
	private: std::string name;
	private: std::vector <connection> connections;
	public: city (std::string);
	public: void addConnection (connection);
	public: std::string name_ ();
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
void addConnections (
	std::vector<city>&,
	const std::vector<std::string>&,
	const std::vector<int>&
);
void main () {
	std::vector<city> departureCities;
	loadVerticesEdgesAndWeights (departureCities);
}
connection::connection (city* destination_) {
	destination = destination_;
}
city::city (std::string cityName) {
	name = cityName;
}
void city::addConnection (connection connection_) {
	connections.push_back (connection_);
}
std::string city::name_ () {
	return name;
}
//Loads, as vertices, cities,
//loads, as edges, connections, and
//loads, as weights, distances in miles between two connected cities,
//and saves all that information into my cities vector.
void loadVerticesEdgesAndWeights (std::vector<city>& departureCities) {
	std::string sFilePlaceHolder =
		"Los Angeles,San Diego,Phoenix,Las Vegas,San Francisco\n"
		"San Diego,Tucson,Phoenix,Los Angeles\n"
		"Tucson,Phoenix,San Diego\n"
		"Phoenix,Tucson,Las Vegas,Los Angeles,San Diego\n"
		"Las Vegas,Phoenix,San Francisco,Los Angeles\n"
		"San Francisco,Los Angeles,Las Vegas\n";
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
	addConnections (departureCities, departureCitiesConnectionNames, departureCitiesConnectionAmounts);
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
void addConnections (
	std::vector<city>& departureCities,
	const std::vector<std::string>& departureCitiesConnectionNames,
	const std::vector<int>& departureCitiesConnectionAmounts
) {
	int nDepartureCity;
	int nDepartureCities = departureCities.size ();
	int nConnections;
	int nDepartureCityConnection;
	int nConnectionCity = 0;
	std::string connectionCityName;
	int nDepartureCityForLoop2;
	bool bDestinationFound;
	std::string departureCityName;
	city* destination;
	int nNonDepartureCities;
	std::vector<city*> nonDepartureCities;
	std::string nonDepartureCityName;
	int nNonDepartureCity;
	for (nDepartureCity = 0; nDepartureCity < nDepartureCities; nDepartureCity++) {
		nConnections = departureCitiesConnectionAmounts[nDepartureCity];
		for (nDepartureCityConnection = 0; nDepartureCityConnection < nConnections; nDepartureCityConnection++) {
			connectionCityName = departureCitiesConnectionNames[nConnectionCity];
			bDestinationFound = false;
			for (
				nDepartureCityForLoop2 = 0;
				nDepartureCityForLoop2 < nDepartureCities && bDestinationFound == false;
				nDepartureCityForLoop2++
			) {
				departureCityName = departureCities[nDepartureCityForLoop2].name_ ();
				bDestinationFound = connectionCityName.compare (departureCityName) == 0;
				if (bDestinationFound)
					destination = &departureCities[nDepartureCityForLoop2];
			}
			if (bDestinationFound == false) {
				nNonDepartureCities = nonDepartureCities.size ();
				for (
					nNonDepartureCity = 0;
					nNonDepartureCity < nNonDepartureCities && bDestinationFound == false;
					nNonDepartureCity++
				) {
					nonDepartureCityName = nonDepartureCities[nNonDepartureCity]->name_ ();
					bDestinationFound = connectionCityName.compare (nonDepartureCityName) == 0;
					if (bDestinationFound)
						destination = nonDepartureCities[nNonDepartureCity];
				}
				if (bDestinationFound == false) {
					destination = new city (connectionCityName);
					nonDepartureCities.push_back (destination);
				}
			}
			departureCities[nDepartureCity].addConnection (connection (destination));
			nConnectionCity++;
		}
	}
}