#include "graph.h"
#include <fstream>
bool canReadALineInto (
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
graph::graph () {
	m_nVertices = 0;
}
unsigned int graph::nVertices () const {
	return m_nVertices;
}
std::string non_weighted_graph::nameOfVertice (
	const unsigned int& index
) const {
	return vertices [index].name ();
}
bool non_weighted_graph::hasEdge (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex
) const {
	return vertices [departureIndex].hasEdgeTo (destinationIndex);
}
void non_weighted_graph::load (
	std::ifstream& dataFile
) {
	std::vector <std::string> departureVerticesNames;
	std::vector <std::string> destinationVerticesNames;
	std::vector <unsigned int> destinationVerticesAmounts;
	std::vector <unsigned int> departureVerticesIndexes;
	parseFile (
		dataFile,
		departureVerticesNames,
		destinationVerticesNames,
		destinationVerticesAmounts
	);
	addVertices (departureVerticesNames, departureVerticesIndexes);
	addDestinationVerticesAndEdges (
		destinationVerticesNames,
		destinationVerticesAmounts,
		departureVerticesIndexes
	);
}
bool non_weighted_graph::hasDirectConnectionBetween (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex
) const {
	bool hasDirectConnection = false;
	if (departureIndex != destinationIndex &&
		this->hasEdge (departureIndex, destinationIndex)
	)
		hasDirectConnection = true;
	return hasDirectConnection;
}
bool non_weighted_graph::hasThroughConnectionBetween (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex,
	std::vector <connection>& throughConnections
) const {
	connection potentialConnection;
	bool hasThroughConnection = false;
	if (departureIndex != destinationIndex) {
		potentialConnection.addDeparture (departureIndex);
		findThroughConnectionsTo (destinationIndex, throughConnections, potentialConnection);
		if (throughConnections.empty () == false)
			hasThroughConnection = true;
	}
	return hasThroughConnection;
}
void non_weighted_graph::addVertices (
	const std::vector <std::string>& verticesNames,
	std::vector <unsigned int>& departureVerticesIndexes
) {
	unsigned int nVertices = verticesNames.size ();
	std::string vertexName;
	unsigned int departureVertexIndex;
	for (
		unsigned int nVertice = 0;
		nVertice < nVertices;
		nVertice++
	) {
		vertexName = verticesNames [nVertice];
		if (this->contains (vertexName, departureVertexIndex) == false) {
			addVertice (vertexName);
			departureVertexIndex = m_nVertices - 1;
		}
		departureVerticesIndexes.push_back (departureVertexIndex);
	}
}
void non_weighted_graph::addVertice (
	const std::string& verticeName
) {
	for (
		unsigned int verticeIndex = 0;
		verticeIndex < m_nVertices;
		verticeIndex++
	) {
		vertices [verticeIndex].considerAnotherVertice ();
	}
	vertices.push_back (vertex (verticeName, m_nVertices));
	m_nVertices++;
}
bool non_weighted_graph::contains (
	const std::string& destinationName,
	unsigned int& nDestinationGraphIndex
) const {
	bool contained = false;
	for (
		unsigned int verticeIndex = 0;
		contained == false && verticeIndex < m_nVertices;
		verticeIndex++
	) {
		if (nameOfVertice (verticeIndex).compare (destinationName) == 0) {
			contained = true;
			nDestinationGraphIndex = verticeIndex;
		}
	}
	return contained;
}
void non_weighted_graph::findThroughConnectionsTo (
	const unsigned int& destinationIndex,
	std::vector <connection>& throughConnections,
	connection& potentialConnection
) const {
	unsigned int vertice;
	unsigned int departure;
	unsigned int nDepartures;
	unsigned int indexOfLastConnection;
	bool goingSomewhereTwice;
	for (
		vertice = 0;
		vertice < m_nVertices;
		vertice++
	) {
	//for every vertice
		nDepartures = potentialConnection.nDepartures ();
		goingSomewhereTwice = false;
		for (
			departure = 0;
			departure < nDepartures;
			departure++
		) {
			indexOfLastConnection = potentialConnection.indexOfDeparture (departure);
			if (vertice == indexOfLastConnection)
			//because of loop this tells us if the vertice is ANY connection
				goingSomewhereTwice = true;
		}
		if (goingSomewhereTwice == false) {
			potentialConnection.addDeparture (vertice);
			if (vertice == destinationIndex) {
				potentialConnection.removeLastDeparture ();
				if (potentialConnection.nDepartures () > 1 &&
					this->hasEdge (indexOfLastConnection, vertice)
				) {
					throughConnections.push_back (potentialConnection);
					potentialConnection = connection (potentialConnection);
				}
			} else {
				if (this->hasEdge (indexOfLastConnection, vertice)) {
				//if connection found
					findThroughConnectionsTo (destinationIndex, throughConnections, potentialConnection); //recursive
				} else {
				//if connection not found
					potentialConnection.removeLastDeparture ();
				}
			}
		}
	}
	potentialConnection.removeLastDeparture ();
}
void non_weighted_graph::parseFile (
	std::ifstream& dataFile,
	std::vector <std::string>& departureVerticesNames,
	std::vector <std::string>& destinationVerticesNames,
	std::vector <unsigned int>& destinationVerticesAmounts
) {
	std::string lineRead;
	char chRead;
	std::string sRead;

	string_destinations destination = string_destinations::DEPARTURE_NAME;
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
				switch (destination) {
					case string_destinations::DEPARTURE_NAME:
					{
						departureVerticesNames.push_back (sRead);
						sRead.clear ();
						destination = string_destinations::DESTINATION_NAME;
						break;
					}
					case string_destinations::DESTINATION_NAME:
					{
						destinationVerticesNames.push_back (sRead);
						nConnections++;
						sRead.clear ();
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
				destinationVerticesNames.push_back (sRead);
				nConnections++;
				sRead.clear ();
				destinationVerticesAmounts.push_back (nConnections);
				nConnections = 0;
				destination = string_destinations::DEPARTURE_NAME;
				break;
			}
		}
	}
}
void non_weighted_graph::addDestinationVerticesAndEdges (
	const std::vector <std::string>& destinationVerticesNames,
	const std::vector <unsigned int>& destinationVerticesAmounts,
	const std::vector <unsigned int>& departureVerticesIndexes
) {
	unsigned int departure;
	const unsigned int nDepartures = destinationVerticesAmounts.size ();
	unsigned int nDestinations;
	unsigned int destination;
	std::string destinationName;
	unsigned int nDestinationParametersIndex = 0;
	unsigned int nDestinationGraphIndex;
	unsigned int nDepartureGraphIndex;
	for (
		departure = 0;
		departure < nDepartures;
		departure++
	) {
	//for every departure
		nDestinations = destinationVerticesAmounts [departure]; //don't change
		for (
			destination = 0;
			destination < nDestinations;
			destination++
		) {
		//for every destination
			destinationName = destinationVerticesNames [nDestinationParametersIndex];
			if (this->contains (destinationName, nDestinationGraphIndex) == false) {
				addVertice (destinationName);
				nDestinationGraphIndex = m_nVertices - 1;
			}
			nDepartureGraphIndex = departureVerticesIndexes [departure];
			addEdge (
				nDepartureGraphIndex,
				nDestinationGraphIndex
			);
			nDestinationParametersIndex++;
		}
	}
}
void non_weighted_graph::addEdge (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex
) {
	vertices [departureIndex].addEdge (destinationIndex);
}