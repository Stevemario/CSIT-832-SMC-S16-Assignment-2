template <class weightType>
std::string weighted_graph <weightType>::nameOfVertice (
	const unsigned int& index
) const {
	return vertices [index].name ();
}
template <class weightType>
bool weighted_graph <weightType>::hasEdge (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex
) const {
	return vertices [departureIndex].hasEdgeTo (destinationIndex);
}
template <class weightType>
weightType weighted_graph <weightType>::weight (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex
) const {
	return vertices [departureIndex].weight (destinationIndex);
}
template <class weightType>
void weighted_graph <weightType>::load (
	std::ifstream& dataFile
) {
	std::vector <std::string> departureVerticesNames;
	std::vector <std::string> destinationVerticesNames;
	std::vector <weightType> destinationVerticesWeights;
	std::vector <unsigned int> destinationVerticesAmounts;
	std::vector <unsigned int> departureVerticesIndexes;
	parseFile (
		dataFile,
		departureVerticesNames,
		destinationVerticesNames,
		destinationVerticesWeights,
		destinationVerticesAmounts
	);
	addVertices (departureVerticesNames, departureVerticesIndexes);
	addDestinationVerticesAndEdges (
		destinationVerticesNames,
		destinationVerticesWeights,
		destinationVerticesAmounts,
		departureVerticesIndexes
	);
}
template <class weightType>
bool weighted_graph <weightType>::hasDirectConnectionBetween (
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
template <class weightType>
bool weighted_graph <weightType>::hasThroughConnectionBetween (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex,
	std::vector <weighted_connection <weightType>>& throughConnections
) const {
	weighted_connection <weightType> potentialConnection;
	bool hasThroughConnection = false;
	if (departureIndex != destinationIndex) {
		potentialConnection.addDeparture (departureIndex);
		findThroughConnectionsTo (destinationIndex, throughConnections, potentialConnection);
		if (throughConnections.empty () == false)
			hasThroughConnection = true;
	}
	return hasThroughConnection;
}
template <class weightType>
void weighted_graph <weightType>::addVertices (
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
			departureVertexIndex = nVertice;
		}
		departureVerticesIndexes.push_back (departureVertexIndex);
	}
}
template <class weightType>
void weighted_graph <weightType>::addVertice (
	const std::string& verticeName
) {
	for (
		unsigned int verticeIndex = 0;
		verticeIndex < m_nVertices;
		verticeIndex++
	) {
		vertices [verticeIndex].considerAnotherVertice ();
	}
	vertices.push_back (weighted_vertex <weightType> (verticeName, m_nVertices));
	m_nVertices++;
}
template <class weightType>
bool weighted_graph <weightType>::contains (
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
template <class weightType>
void weighted_graph <weightType>::findThroughConnectionsTo (
	const unsigned int& destinationIndex,
	std::vector <weighted_connection <weightType>>& throughConnections,
	weighted_connection <weightType>& potentialConnection
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
					potentialConnection = weighted_connection <weightType> (potentialConnection);
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
template <class weightType>
void weighted_graph <weightType>::calculateWeightSums (
	std::vector <weighted_connection <weightType>>& throughConnections,
	const unsigned int& destinationIndex
) const {
	unsigned int throughConnection;
	unsigned int nThroughConnections = throughConnections.size ();
	weightType weightTotal;
	unsigned int nDepartures;
	unsigned int departure;
	unsigned int currentDestination;
	for (
		throughConnection = 0;
		throughConnection < nThroughConnections;
		throughConnection++
	) {
		setEmpty (weightTotal);
		nDepartures = throughConnections [throughConnection].nDepartures ();
		for (
			departure = 0;
			departure < nDepartures;
			departure++
		) {
			if (departure != nDepartures - 1)
				currentDestination = throughConnections [throughConnection].indexOfDeparture (departure + 1);
			else
				currentDestination = destinationIndex;
			weightTotal += weight (
				throughConnections [throughConnection].indexOfDeparture (departure),
				currentDestination
			);
		}
		throughConnections [throughConnection].set_weightsSum (weightTotal);
	}
}
template <class weightType>
void weighted_graph <weightType>::parseFile (
	std::ifstream& dataFile,
	std::vector <std::string>& departureVerticesNames,
	std::vector <std::string>& destinationVerticesNames,
	std::vector <weightType>& destinationVerticesWeights,
	std::vector <unsigned int>& destinationVerticesAmounts
) {
	std::string lineRead;
	char chRead;
	std::string sRead;
	weightType temp;

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
						sRead.clear ();
						destination = string_destinations::DESTINATION_WEIGHT;
						break;
					}
					case string_destinations::DESTINATION_WEIGHT:
					{
						setWeight (temp, sRead);
						destinationVerticesWeights.push_back (temp);
						nConnections++;
						sRead.clear ();
						destination = string_destinations::DESTINATION_NAME;
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
				setWeight (temp, sRead);
				destinationVerticesWeights.push_back (temp);
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
template <class weightType>
void weighted_graph <weightType>::addDestinationVerticesAndEdges (
	const std::vector <std::string>& destinationVerticesNames,
	const std::vector <weightType>& destinationVerticesWeights,
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
				nDestinationGraphIndex =  m_nVertices - 1;
			}
			addEdge (
				departureVerticesIndexes [departure],
				nDestinationGraphIndex,
				destinationVerticesWeights [nDestinationParametersIndex]
			);
			nDestinationParametersIndex++;
		}
	}
}
template <class weightType>
void weighted_graph <weightType>::addEdge (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex,
	const weightType& weight
) {
	vertices [departureIndex].setWeight (destinationIndex, weight);
}