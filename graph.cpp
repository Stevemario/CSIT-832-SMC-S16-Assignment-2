#include "graph.h"
#include <fstream>
std::vector <connection> graph::s_thoroughConnections;
connection graph::s_potentialConnection;
graph::graph () {
	m_nVertices = 0;
}
unsigned int graph::nVertices () const {
	return m_nVertices;
}
std::string graph::nameOfVertice (
	const unsigned int& index
) const {
	return vertices [index].name ();
}
void graph::load (
	std::ifstream& dataFile
) {
	std::vector <std::string> departureVerticesNames;
	std::vector <std::string> destinationVerticesNames;
	std::vector <distance> destinationVerticesWeights;
	std::vector <unsigned int> destinationVerticesAmounts;
	parseFile (
		dataFile,
		departureVerticesNames,
		destinationVerticesNames,
		destinationVerticesWeights,
		destinationVerticesAmounts
	);
	addDepartureVertices (departureVerticesNames);
	addDestinationVerticesAndEdges (
		destinationVerticesNames,
		destinationVerticesWeights,
		destinationVerticesAmounts
	);
}
bool graph::hasDirectConnectionBetween (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex
) const {
	bool hasDirectConnection = false;
	if (departureIndex != destinationIndex &&
		vertices [departureIndex].hasEdgeTo (destinationIndex)
	)
		hasDirectConnection = true;
	return hasDirectConnection;
}
bool graph::hasThroughConnectionBetween (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex,
	std::vector<connection>& throughConnections,
	std::vector<distance>& weightTotals
) const {
	bool hasThroughConnection = false;
	if (departureIndex != destinationIndex) {
		s_potentialConnection.push_back (departureIndex);
		findThoroughConnectionsTo (destinationIndex);
		s_potentialConnection.clear ();
		throughConnections = s_thoroughConnections;
		s_thoroughConnections.clear ();
		if (throughConnections.empty () == false) {
			hasThroughConnection = true;
			sort (throughConnections, weightTotals, destinationIndex);
		}
	}
	return hasThroughConnection;
}
void graph::parseFile (
	std::ifstream& dataFile,
	std::vector <std::string>& departureVerticesNames,
	std::vector <std::string>& destinationVerticesNames,
	std::vector <distance>& destinationVerticesWeights,
	std::vector <unsigned int>& destinationVerticesAmounts
) {
	std::string lineRead;
	char chRead;
	std::string sRead;
	const int DEPARTURE_NAME = 0;
	const int DESTINATION_NAME = 1;
	const int DESTINATION_WEIGHT = 2;
	int objectReading = DEPARTURE_NAME;
	unsigned int nConnections = 0;
	while (lineRead.empty () == false ||
		canReadALineInto (lineRead, dataFile)
	) {
		chRead = lineRead [0];
		lineRead.erase (0, 1);

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
						departureVerticesNames.push_back (sRead);
						sRead.clear ();
						objectReading = DESTINATION_NAME;
						break;
					}
					case DESTINATION_NAME:
					{
						destinationVerticesNames.push_back (sRead);
						sRead.clear ();
						objectReading = DESTINATION_WEIGHT;
						break;
					}
					case DESTINATION_WEIGHT:
					{
						destinationVerticesWeights.push_back (std::stoi (sRead));
						nConnections++;
						sRead.clear ();
						objectReading = DESTINATION_NAME;
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
				destinationVerticesWeights.push_back (std::stoi (sRead));
				nConnections++;
				sRead.clear ();
				destinationVerticesAmounts.push_back (nConnections);
				nConnections = 0;
				objectReading = DEPARTURE_NAME;
				break;
			}
		}
	}
}
bool graph::canReadALineInto (
	std::string& lineRead,
	std::ifstream& dataFile
) {
	bool canReadALine = false;
	std::getline (dataFile, lineRead);
	if (lineRead.empty () == false) {
		canReadALine = true;
		lineRead += '\n';
	}
	return canReadALine;
}
void graph::addDepartureVertices (
	const std::vector <std::string>& departureVerticesNames
) {
	unsigned int nDepartureVertices = departureVerticesNames.size ();
	for (
		unsigned int nVertice = 0;
		nVertice < nDepartureVertices;
		nVertice++
	) {
		addVertice (departureVerticesNames [nVertice]);
	}
}
void graph::addVertice (
	const std::string& verticeName
) {
	for (
		unsigned int verticeIndex = 0;
		verticeIndex < m_nVertices;
		verticeIndex++
	) {
		vertices [verticeIndex].considerAnotherVertice ();
	}
	vertices.push_back (weighted_vertice <distance> (verticeName, m_nVertices));
	m_nVertices++;
}
void graph::addDestinationVerticesAndEdges (
	const std::vector <std::string>& destinationVerticesNames,
	const std::vector <distance>& destinationVerticesWeights,
	const std::vector <unsigned int>& destinationVerticesAmounts
) {
	unsigned int nDepartureVertice;
	const unsigned int nDepartureVertices = m_nVertices;
	unsigned int destinationVerticesAmount;
	unsigned int nDestinationVertice;
	std::string destinationName;
	unsigned int nDestinationParametersIndex = 0;
	unsigned int nDestinationGraphIndex;
	for (
		nDepartureVertice = 0;
		nDepartureVertice < nDepartureVertices;
		nDepartureVertice++
	) {
	//for every departure vertice
		destinationVerticesAmount = destinationVerticesAmounts[nDepartureVertice]; //don't change
		for (
			nDestinationVertice = 0;
			nDestinationVertice < destinationVerticesAmount;
			nDestinationVertice++
		) {
		//for every destination
			destinationName = destinationVerticesNames [nDestinationParametersIndex];
			if (this->contains (destinationName, nDestinationGraphIndex))
				addEdge (nDepartureVertice, nDestinationGraphIndex, destinationVerticesWeights [nDestinationParametersIndex]);
			else {
				addVertice (destinationName);
				addEdge (nDepartureVertice, m_nVertices - 1, destinationVerticesWeights [nDestinationParametersIndex]);
			}
			nDestinationParametersIndex++;
		}
	}
}
bool graph::contains (
	const std::string& destinationName,
	unsigned int& nDestinationGraphIndex
) const {
	bool contained = false;
	for (
		unsigned int verticeIndex = 0;
		contained == false && verticeIndex < m_nVertices;
		verticeIndex++
	) {
		if (vertices [verticeIndex].name ().compare (destinationName) == 0) {
			contained = true;
			nDestinationGraphIndex = verticeIndex;
		}
	}
	return contained;
}
void graph::addEdge (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex,
	const distance& weight
) {
	vertices [departureIndex].setWeight (destinationIndex, weight);
}
void graph::findThoroughConnectionsTo (
	const unsigned int& destinationIndex
) const {
	unsigned int vertice;
	unsigned int nConnection;
	unsigned int nConnections;
	unsigned int indexOfLastConnection;
	bool goingSomewhereTwice;
	for (
		vertice = 0;
		vertice < m_nVertices;
		vertice++
	) {
	//for every vertice
		nConnections = s_potentialConnection.size ();
		goingSomewhereTwice = false;
		for (
			nConnection = 0;
			nConnection < nConnections;
			nConnection++
		) {
			indexOfLastConnection = s_potentialConnection[nConnection];
			if (vertice == indexOfLastConnection)
			//because of loop this tells us if the vertice is ANY connection
				goingSomewhereTwice = true;
		}
		if (goingSomewhereTwice == false) {
			s_potentialConnection.push_back (vertice);
			if (vertice == destinationIndex) {
				s_potentialConnection.pop_back ();
				if (s_potentialConnection.size () > 1 &&
					vertices [indexOfLastConnection].hasEdgeTo (vertice)
				)
					s_thoroughConnections.push_back (s_potentialConnection);
			} else {
				if (vertices [indexOfLastConnection].hasEdgeTo (vertice)) {
				//if connection found
					findThoroughConnectionsTo (destinationIndex); //recursive
				} else {
				//if connection not found
					s_potentialConnection.pop_back ();
				}
			}
		}
	}
	s_potentialConnection.pop_back ();
}
void graph::sort (
	std::vector<connection>& throughConnections,
	std::vector<distance>& weightTotals,
	const unsigned int& destinationIndex
) const {
	unsigned int throughConnection;
	unsigned int nThroughConnections = throughConnections.size ();
	distance weightTotal;
	unsigned int nDepartures;
	unsigned int departure;
	unsigned int successorConnection;
	for (
		throughConnection = 0;
		throughConnection < nThroughConnections;
		throughConnection++
	) {
		weightTotal = 0;
		nDepartures = throughConnections [throughConnection].size ();
		for (
			departure = 0;
			departure < nDepartures;
			departure++
		) {
			if (departure != nDepartures - 1)
				weightTotal +=
					vertices [throughConnections [throughConnection] [departure]].weight (
					throughConnections [throughConnection] [departure + 1]
					);
			else
				weightTotal +=
					vertices [throughConnections [throughConnection] [departure]].weight (
					destinationIndex
					);
		}
		weightTotals.push_back (weightTotal);
	}
	for (
		throughConnection = 0;
		throughConnection < nThroughConnections;
		throughConnection++
	) {
		for (
			successorConnection = throughConnection + 1;
			successorConnection < nThroughConnections;
			successorConnection++
		) {
			if (weightTotals [successorConnection] < weightTotals [throughConnection])
				swap (throughConnections, weightTotals, throughConnection, successorConnection);
		}
	}
}
void graph::swap (
	std::vector<connection>& throughConnections,
	std::vector<distance>& weightTotals,
	const unsigned int& index1,
	const unsigned int& index2
) {
		connection tempConnection = throughConnections [index1];
		distance tempWeightTotal = weightTotals [index1];
		throughConnections [index1] = throughConnections [index2];
		weightTotals [index1] = weightTotals [index2];
		throughConnections [index2] = tempConnection;
		weightTotals [index2] = tempWeightTotal;
}