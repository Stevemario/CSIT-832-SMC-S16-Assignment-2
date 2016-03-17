#ifndef GRAPH_H
#define GRAPH_H
#include "vertice.h"
typedef unsigned int distance;
typedef std::vector <unsigned int> connection;
class graph {
	private: std::vector <weighted_vertice <distance>> vertices;
	private: unsigned int m_nVertices;
	public: graph ();
	public: unsigned int nVertices () const;
	public: std::string nameOfVertice (
		const unsigned int&
	) const;
	//Loads, as vertices, cities,
	//loads, as edges, connections, and
	//loads, as weights, distances in miles between two connected cities,
	//and saves all that information into my graph.
	public: void load (
		std::ifstream&
	);
	public: bool hasDirectConnectionBetween (
		const unsigned int&,
		const unsigned int&
	) const;
	public: bool hasThroughConnectionBetween (
		const unsigned int&,
		const unsigned int&,
		std::vector <connection>&
	) const;
	public: void sort (
		std::vector <connection>&,
		std::vector <distance>&,
		const unsigned int&
	) const;
	private: static void parseFile (
		std::ifstream&,
		std::vector <std::string>&,
		std::vector <std::string>&,
		std::vector <distance>&,
		std::vector <unsigned int>&
	);
	private: static bool canReadALineInto (
		std::string&,
		std::ifstream&
	);
	private: void addDepartureVertices (
		const std::vector <std::string>&
	);
	private: void addVertice (
		const std::string&
	);
	private: void addDestinationVerticesAndEdges (
		const std::vector <std::string>&,
		const std::vector <distance>&,
		const std::vector <unsigned int>&
	);
	private: bool contains (
		const std::string&,
		unsigned int&
	) const;
	private: void addEdge (
		const unsigned int&,
		const unsigned int&,
		const distance&
	);
	private: void findThoroughConnectionsTo (
		const unsigned int&,
		std::vector <connection>&,
		connection&
	) const;
	private: static void swap (
		std::vector <connection>&,
		std::vector <distance>&,
		const unsigned int&,
		const unsigned int&
	);
};
#endif