#ifndef GRAPH_H
#define GRAPH_H
#include "vertice.h"
typedef std::vector<unsigned int> connection;
class graph {
	private: std::vector <vertice> list;
	private: unsigned int m_nVertices;
	private: static std::vector<connection> s_thoroughConnections;
	private: static connection s_potentialConnection;
	public: graph ();
	//Loads, as vertices, cities,
	//loads, as edges, connections, and
	//loads, as weights, distances in miles between two connected cities,
	//and saves all that information into my graph.
	public: void load (
		std::ifstream&
	);
	private: static void parseFile (
		std::ifstream&,
		std::vector<std::string>&,
		std::vector<std::string>&,
		std::vector<unsigned int>&,
		std::vector<unsigned int>&
	);
	private: static bool canReadALineInto (
		std::string&,
		std::ifstream&
	);
	private: void addDepartureVertices (
		const std::vector<std::string>&
	);
	private: void addVertice (
		const std::string&
	);
	private: void addDestinationVerticesAndEdges (
		const std::vector<std::string>&,
		const std::vector<unsigned int>&,
		const std::vector<unsigned int>&
	);
	private: bool contains (
		const std::string&,
		unsigned int&
	) const;
	private: void addEdge (
		const unsigned int&,
		const unsigned int&,
		const unsigned int&
	);
	public: unsigned int nVertices () const;
	public: std::string nameOfVertice (
		const unsigned int&
	) const;
	public: bool hasDirectConnectionBetween (
		const unsigned int&,
		const unsigned int&
	) const;
	public: bool hasThroughConnectionBetween (
		const unsigned int&,
		const unsigned int&,
		std::vector<connection>&,
		std::vector<unsigned int>&
	) const;
	private: void findThoroughConnectionsTo (
		const unsigned int&
	) const;
	private: void sort (
		std::vector<connection>&,
		std::vector<unsigned int>&,
		const unsigned int&
	) const;
	private: static void swap (
		std::vector<connection>&,
		std::vector<unsigned int>&,
		const unsigned int&,
		const unsigned int&
	);
};
#endif