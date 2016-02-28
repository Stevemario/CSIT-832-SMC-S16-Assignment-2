//Los Angeles Valley College
//CSIT 832
//Spring 2016
//Steve Mario Correa
//Assignment 2
//This software manages GenghisAir flights using graphs to represent the
//available flights.
#include <string>
#include <vector>
class city;
class connection {
	private: city* destination;
	private: int distance;
	public: connection (city*, const int&);
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
	std::vector<int>&,
	std::vector<int>&
);
void fill (
	std::vector<city>&,
	const std::vector<std::string>&
);
void addConnections (
	std::vector<city>&,
	const std::vector<std::string>&,
	const std::vector<int>&,
	const std::vector<int>&
);
void main () {
	std::vector<city> departureCities;
	loadVerticesEdgesAndWeights (departureCities);
}
connection::connection (city* destination_, const int& distance_) {
	destination = destination_;
	distance = distance_;
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
		"Los Angeles,San Diego,125,Phoenix,391,Las Vegas,281,San Francisco,378\n"
		"San Diego,Tucson,418,Phoenix,361,Los Angeles,125\n"
		"Tucson,Phoenix,119,San Diego,423\n"
		"Phoenix,Tucson,118,Las Vegas,300,Los Angeles,391,San Diego,362\n"
		"Las Vegas,Phoenix,301,San Francisco,556,Los Angeles,282\n"
		"San Francisco,Los Angeles,378,Las Vegas,556\n";
	std::vector<std::string> departureCitiesNames;
	std::vector<std::string> departureCitiesConnectionNames;
	std::vector<int> departureCitiesConnectionDistances;
	std::vector<int> departureCitiesConnectionAmounts;
	parseFile (
		sFilePlaceHolder,
		departureCitiesNames,
		departureCitiesConnectionNames,
		departureCitiesConnectionDistances,
		departureCitiesConnectionAmounts
	);
	fill (departureCities, departureCitiesNames);
	addConnections (
		departureCities,
		departureCitiesConnectionNames,
		departureCitiesConnectionDistances,
		departureCitiesConnectionAmounts
	);
}
void parseFile (
	std::string& sFilePlaceHolder,
	std::vector<std::string>& departureCitiesNames,
	std::vector<std::string>& departureCitiesConnectionNames,
	std::vector<int>& departureCitiesConnectionDistances,
	std::vector<int>& departureCitiesConnectionAmounts
) {
	std::string sRead;
	char chRead;
	const int DEPARTURE_NAME = 0;
	const int CONNECTION_NAME = 1;
	const int CONNECTION_DISTANCE = 2;
	int objectReading = DEPARTURE_NAME;
	int nConnections = 0;
	while (sFilePlaceHolder.empty () != true) {
		chRead = sFilePlaceHolder[0];
		sFilePlaceHolder.erase (0, 1);

		switch (chRead) {
			default:
			{
				sRead += chRead;
				break;
			}
			case ',':
			{
				switch (objectReading) {
					case DEPARTURE_NAME:
					{
						departureCitiesNames.push_back (sRead);
						sRead.clear ();
						objectReading = CONNECTION_NAME;
						break;
					}
					case CONNECTION_NAME:
					{
						departureCitiesConnectionNames.push_back (sRead);
						sRead.clear ();
						objectReading = CONNECTION_DISTANCE;
						break;
					}
					case CONNECTION_DISTANCE:
					{
						departureCitiesConnectionDistances.push_back (std::stoi (sRead));
						nConnections++;
						sRead.clear ();
						objectReading = CONNECTION_NAME;
						break;
					}
					default:
					{
						break;
					}
				}
				break;
			}
			case '\n':
			{
				departureCitiesConnectionDistances.push_back (std::stoi (sRead));
				nConnections++;
				sRead.clear ();
				departureCitiesConnectionAmounts.push_back (nConnections);
				nConnections = 0;
				objectReading = DEPARTURE_NAME;
				break;
			}
		}
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
	const std::vector<int>& departureCitiesConnectionDistances,
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
			departureCities[nDepartureCity].addConnection (
				connection (destination, departureCitiesConnectionDistances[nConnectionCity])
			);
			nConnectionCity++;
		}
	}
}