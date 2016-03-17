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
	parseFile (
		dataFile,
		departureVerticesNames,
		destinationVerticesNames,
		destinationVerticesWeights,
		destinationVerticesAmounts
	);
	addVertices (departureVerticesNames);
	addDestinationVerticesAndEdges (
		destinationVerticesNames,
		destinationVerticesWeights,
		destinationVerticesAmounts
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
	std::vector<connection>& throughConnections
) const {
	connection potentialConnection;
	bool hasThroughConnection = false;
	if (departureIndex != destinationIndex) {
		potentialConnection.push_back (departureIndex);
		findThroughConnectionsTo (destinationIndex, throughConnections, potentialConnection);
		if (throughConnections.empty () == false)
			hasThroughConnection = true;
	}
	return hasThroughConnection;
}
template <class weightType>
void weighted_graph <weightType>::addVertices (
	const std::vector <std::string>& verticesNames
) {
	unsigned int nVertices = verticesNames.size ();
	for (
		unsigned int nVertice = 0;
		nVertice < nVertices;
		nVertice++
	) {
		addVertice (verticesNames [nVertice]);
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
	vertices.push_back (weighted_vertice <weightType> (verticeName, m_nVertices));
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
	std::vector <connection>& throughConnections,
	connection& potentialConnection
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
		nConnections = potentialConnection.size ();
		goingSomewhereTwice = false;
		for (
			nConnection = 0;
			nConnection < nConnections;
			nConnection++
		) {
			indexOfLastConnection = potentialConnection[nConnection];
			if (vertice == indexOfLastConnection)
			//because of loop this tells us if the vertice is ANY connection
				goingSomewhereTwice = true;
		}
		if (goingSomewhereTwice == false) {
			potentialConnection.push_back (vertice);
			if (vertice == destinationIndex) {
				potentialConnection.pop_back ();
				if (potentialConnection.size () > 1 &&
					this->hasEdge (indexOfLastConnection, vertice)
				)
					throughConnections.push_back (potentialConnection);
			} else {
				if (this->hasEdge (indexOfLastConnection, vertice)) {
				//if connection found
					findThroughConnectionsTo (destinationIndex, throughConnections, potentialConnection); //recursive
				} else {
				//if connection not found
					potentialConnection.pop_back ();
				}
			}
		}
	}
	potentialConnection.pop_back ();
}
template <class weightType>
void weighted_graph <weightType>::sort (
	std::vector<connection>& throughConnections,
	std::vector<weightType>& weightTotals,
	const unsigned int& destinationIndex
) const {
	unsigned int throughConnection;
	unsigned int nThroughConnections = throughConnections.size ();
	weightType weightTotal;
	unsigned int nDepartures;
	unsigned int departure;
	unsigned int currentDestination;
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
				currentDestination = throughConnections [throughConnection] [departure + 1];
			else
				currentDestination = destinationIndex;
			weightTotal += weight (
				throughConnections [throughConnection] [departure],
				currentDestination
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
						destinationVerticesWeights.push_back (std::stoi (sRead));
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
				destinationVerticesWeights.push_back (std::stoi (sRead));
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
		destinationVerticesAmount = destinationVerticesAmounts [nDepartureVertice]; //don't change
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
template <class weightType>
void weighted_graph <weightType>::addEdge (
	const unsigned int& departureIndex,
	const unsigned int& destinationIndex,
	const weightType& weight
) {
	vertices [departureIndex].setWeight (destinationIndex, weight);
}
template <class weightType>
void weighted_graph <weightType>::swap (
	std::vector<connection>& throughConnections,
	std::vector<weightType>& weightTotals,
	const unsigned int& index1,
	const unsigned int& index2
) {
		connection tempConnection = throughConnections [index1];
		weightType tempWeightTotal = weightTotals [index1];
		throughConnections [index1] = throughConnections [index2];
		weightTotals [index1] = weightTotals [index2];
		throughConnections [index2] = tempConnection;
		weightTotals [index2] = tempWeightTotal;
}