//Los Angeles Valley College
//CSIT 832
//Spring 2016
//Steve Mario Correa
//Assignment 2
//This software uses a graph to represent the GenghisAir flight cities network.
#include "graph.h"
#include "distance.h"
#include "priorityqueue.h"
#include <iostream>
#include <fstream>
typedef weighted_graph <distance> graph_weighted_by_distance;
typedef weighted_connection <distance> connection_weighted_by_distance;
void displayMenu (
	char&
);
void getDepartureCityIndex (
	const graph_weighted_by_distance&,
	unsigned int&
);
void getDestinationCityIndex (
	const graph_weighted_by_distance&,
	const unsigned int&,
	unsigned int&
);
void printNoConnection (
	const graph_weighted_by_distance&,
	const unsigned int&,
	const unsigned int&
);
void printInstructionsToReturnToMenu ();
void printNoDirectConnection (
	const graph_weighted_by_distance&,
	const unsigned int&,
	const unsigned int&
);
void printThroughConnections (
	const graph_weighted_by_distance&,
	const unsigned int&,
	const unsigned int&,
	std::vector <connection_weighted_by_distance>&
);
void printDirectConnection (
	const graph_weighted_by_distance&,
	const unsigned int&,
	const unsigned int&
);
void printNoThroughConnections (
	const graph_weighted_by_distance&,
	const unsigned int&,
	const unsigned int&
);
void main () {
	std::ifstream dataFile ("load.txt");
	graph_weighted_by_distance citiesGraph;
	char userChoice;
	bool programShouldEnd = false;
	unsigned int departureCityIndex;
	unsigned int destinationCityIndex;
	bool thereIsNoDirectConnection;
	bool thereIsNoThroughConnection;
	std::vector <connection_weighted_by_distance> throughConnections;
	citiesGraph.load (dataFile);
	dataFile.close ();
	do {
		displayMenu (userChoice);
		if (userChoice == '2')
			programShouldEnd = true;
		else if (userChoice == '1') {
			getDepartureCityIndex (citiesGraph, departureCityIndex);
			getDestinationCityIndex (citiesGraph, departureCityIndex, destinationCityIndex);
			thereIsNoDirectConnection = citiesGraph.hasDirectConnectionBetween (departureCityIndex, destinationCityIndex) == false;
			thereIsNoThroughConnection = citiesGraph.hasThroughConnectionBetween (
				departureCityIndex,
				destinationCityIndex,
				throughConnections
			) == false;
			if (thereIsNoDirectConnection && thereIsNoThroughConnection) {
			//if there is no direct or through connection between the departure and destination cities
				printNoConnection (citiesGraph, departureCityIndex, destinationCityIndex);
				printInstructionsToReturnToMenu ();
			} else if (thereIsNoDirectConnection && thereIsNoThroughConnection == false) {
				printNoDirectConnection (citiesGraph, departureCityIndex, destinationCityIndex);
				printThroughConnections (citiesGraph, departureCityIndex, destinationCityIndex, throughConnections);
				printInstructionsToReturnToMenu ();
			} else if (thereIsNoDirectConnection == false) {
				printDirectConnection (citiesGraph, departureCityIndex, destinationCityIndex);
				if (thereIsNoThroughConnection)
					printNoThroughConnections (citiesGraph, departureCityIndex, destinationCityIndex);
				else
					printThroughConnections (citiesGraph, departureCityIndex, destinationCityIndex, throughConnections);
				printInstructionsToReturnToMenu ();
			}
			throughConnections.clear ();
		}
	} while (programShouldEnd == false);
}
void displayMenu (
	char& userChoice
) {
	std::cout << "1. Choose departure city\n" <<
		"2. Exit\n";
	std::cin >> userChoice;
	std::cin.ignore (std::numeric_limits <std::streamsize>::max (), '\n');
	std::cout << "\n";
}
void getDepartureCityIndex (
	const graph_weighted_by_distance& citiesGraph,
	unsigned int& departureCityIndex
) {
	const unsigned int nVertices = citiesGraph.nVertices ();
	for (
		unsigned int vertice = 0;
		vertice < nVertices;
		vertice++
	)
		std::cout << vertice + 1 << ". " << citiesGraph.nameOfVertice (vertice) << "\n";
	std::cout << "Choose city: ";
	std::cin >> departureCityIndex;
	std::cin.ignore (std::numeric_limits <std::streamsize>::max (), '\n');
	std::cout << "\n";
	departureCityIndex--;
}
void getDestinationCityIndex (
	const graph_weighted_by_distance& citiesGraph,
	const unsigned int& departureCityIndex,
	unsigned int& destinationCityIndex
) {
	const unsigned int nVertices = citiesGraph.nVertices ();
	for (
		unsigned int vertice = 0;
		vertice < nVertices;
		vertice++
	) {
		if (vertice < departureCityIndex) {
			destinationCityIndex = vertice + 1;
			std::cout << destinationCityIndex << ". " << citiesGraph.nameOfVertice (vertice) << "\n";
		} else if (vertice == departureCityIndex) {
			//don't show this choice;
		} else { //vertice > departureCityIndex
			destinationCityIndex = vertice;
			std::cout << destinationCityIndex << ". " << citiesGraph.nameOfVertice (vertice) << "\n";
		}
	}
	std::cout << "Choose city: ";
	std::cin >> destinationCityIndex;
	std::cin.ignore (std::numeric_limits <std::streamsize>::max (), '\n');
	std::cout << "\n";
	if (destinationCityIndex - 1 < departureCityIndex)
		destinationCityIndex--;
}
void printNoConnection (
	const graph_weighted_by_distance& citiesGraph,
	const unsigned int& departureCityIndex,
	const unsigned int& destinationCityIndex
) {
	std::cout << "No connection between " << citiesGraph.nameOfVertice (departureCityIndex) <<
		" and " << citiesGraph.nameOfVertice (destinationCityIndex) << "\n";
}
void printInstructionsToReturnToMenu () {
	char userChoice;
	std::cout << "Press any key to return to menu.\n";
	std::cin >> userChoice;
	std::cin.ignore (std::numeric_limits <std::streamsize>::max (), '\n');
	std::cout << "\n";
}
void printNoDirectConnection (
	const graph_weighted_by_distance& citiesGraph,
	const unsigned int& departureCityIndex,
	const unsigned int& destinationCityIndex
) {
	std::cout << "No direction connection between " << citiesGraph.nameOfVertice (departureCityIndex) <<
		" and " << citiesGraph.nameOfVertice (destinationCityIndex) << "\n";
}
void printThroughConnections (
	const graph_weighted_by_distance& citiesGraph,
	const unsigned int& departureCityIndex,
	const unsigned int& destinationCityIndex,
	std::vector <connection_weighted_by_distance>& throughConnections
) {
	unsigned int nConnections = throughConnections.size ();
	PriorityQueue <connection_weighted_by_distance> throughConnectionPrioQ;
	connection_weighted_by_distance currentConnection;
	unsigned int nDepartures;
	unsigned int departure;
	std::string weightTotal;
	citiesGraph.calculateWeightSums (throughConnections, destinationCityIndex);
	for (
		unsigned int connection = 0;
		connection < nConnections;
		connection++
	) {
		throughConnectionPrioQ.enqueue (throughConnections [connection]);
	}
	while (throughConnectionPrioQ.bIsEmpty () == false) {
		throughConnectionPrioQ.dequeue (currentConnection);
		nDepartures = currentConnection.nDepartures ();
		std::cout << "Through connection between " << citiesGraph.nameOfVertice (departureCityIndex) << " and " <<
			citiesGraph.nameOfVertice (destinationCityIndex)  << " via ";
		for (
			departure = 1; //0th departure has already been named above
			departure < nDepartures;
			departure++
		) {
			std::cout << citiesGraph.nameOfVertice (currentConnection.indexOfDeparture (departure));
			if (
				nDepartures > 1 &&
				//there are multiple layovers, and
				departure != nDepartures - 1
				//this isnt the last layover
			) {
				std::cout << ", ";
				//oxford comma too
				if (departure == nDepartures - 2) //if this is penultimate departure
					std::cout << "and ";
			}
		}
		getWeight (weightTotal, currentConnection.weightsSum ());
		std::cout << " - " << weightTotal << " miles\n";
	}
}
void printDirectConnection (
	const graph_weighted_by_distance& citiesGraph,
	const unsigned int& departureCityIndex,
	const unsigned int& destinationCityIndex
) {
	std::cout << "Direct connection between " << citiesGraph.nameOfVertice (departureCityIndex) <<
		" and " << citiesGraph.nameOfVertice (destinationCityIndex) << "\n";
}
void printNoThroughConnections (
	const graph_weighted_by_distance& citiesGraph,
	const unsigned int& departureCityIndex,
	const unsigned int& destinationCityIndex
) {
	std::cout << "No through connection between " << citiesGraph.nameOfVertice (departureCityIndex) <<
		" and " << citiesGraph.nameOfVertice (destinationCityIndex) << "\n";
}