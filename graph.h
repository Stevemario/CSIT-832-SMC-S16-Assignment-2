#ifndef GRAPH_H
#define GRAPH_H
#include "vertice.h"
typedef unsigned int distance;
typedef std::vector <unsigned int> connection;
bool canReadALineInto (
	std::string&,
	std::ifstream&
);
void setWeight (
	distance&,
	const std::string&
);
void getWeight (
	std::string&,
	const distance&
);
void setEmpty (
	distance&
);
class graph {
	protected: unsigned int m_nVertices;
	protected: graph ();
	public: unsigned int nVertices () const;
	public: virtual std::string nameOfVertice (
		const unsigned int&
	) const = 0;
	public: virtual bool hasEdge (
		const unsigned int&,
		const unsigned int&
	) const = 0;
	public: virtual void load (
		std::ifstream&
	) = 0;
	public: virtual bool hasDirectConnectionBetween (
		const unsigned int&,
		const unsigned int&
	) const = 0;
	public: virtual bool hasThroughConnectionBetween (
		const unsigned int&,
		const unsigned int&,
		std::vector <connection>&
	) const = 0;
	public: virtual void addVertices (
		const std::vector <std::string>&
	) = 0;
	public: virtual void addVertice (
		const std::string&
	) = 0;
	public: virtual bool contains (
		const std::string&,
		unsigned int&
	) const = 0;
	public: virtual void findThroughConnectionsTo (
		const unsigned int&,
		std::vector <connection>&,
		connection&
	) const = 0;
};
class non_weighted_graph : public graph {
	enum class string_destinations {
	DEPARTURE_NAME = 0,
	DESTINATION_NAME = 1,
	};
	private: std::vector <vertice> vertices;
	public: std::string nameOfVertice (
		const unsigned int&
	) const;
	public: bool hasEdge (
		const unsigned int&,
		const unsigned int&
	) const;
	public: distance weight (
		const unsigned int&,
		const unsigned int&
	) const;
	//Loads, as vertices, cities, and
	//loads, as edges, connections,
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
	private: void addVertices (
		const std::vector <std::string>&
	);
	private: void addVertice (
		const std::string&
	);
	private: bool contains (
		const std::string&,
		unsigned int&
	) const;
	private: void findThroughConnectionsTo (
		const unsigned int&,
		std::vector <connection>&,
		connection&
	) const;
	private: static void parseFile (
		std::ifstream&,
		std::vector <std::string>&,
		std::vector <std::string>&,
		std::vector <unsigned int>&
	);
	private: void addDestinationVerticesAndEdges (
		const std::vector <std::string>&,
		const std::vector <unsigned int>&
	);
	private: void addEdge (
		const unsigned int&,
		const unsigned int&
	);
};
template <class weightType>
//weighted_graph uses the following weightType classes functions:
//1. void setWeight (
//	weightType&,
//	const std::string
//);
//2. void getWeight (
//	std::string&,
//	const distance&
//);
//3. void setEmpty (
//	distance&
//);
//4. operator+= for weightType
//5. operator< for weightType
//SO YOU MUST HAVE THEM!
class weighted_graph : public graph {
	enum class string_destinations {
	DEPARTURE_NAME = 0,
	DESTINATION_NAME = 1,
	DESTINATION_WEIGHT = 2,
	};
	private: std::vector <weighted_vertice <weightType>> vertices;
	public: std::string nameOfVertice (
		const unsigned int&
	) const;
	public: bool hasEdge (
		const unsigned int&,
		const unsigned int&
	) const;
	public: weightType weight (
		const unsigned int&,
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
	private: void addVertices (
		const std::vector <std::string>&
	);
	private: void addVertice (
		const std::string&
	);
	private: bool contains (
		const std::string&,
		unsigned int&
	) const;
	private: void findThroughConnectionsTo (
		const unsigned int&,
		std::vector <connection>&,
		connection&
	) const;
	public: void sort (
		std::vector <connection>&,
		std::vector <weightType>&,
		const unsigned int&
	) const;
	private: static void parseFile (
		std::ifstream&,
		std::vector <std::string>&,
		std::vector <std::string>&,
		std::vector <weightType>&,
		std::vector <unsigned int>&
	);
	private: void addDestinationVerticesAndEdges (
		const std::vector <std::string>&,
		const std::vector <weightType>&,
		const std::vector <unsigned int>&
	);
	private: void addEdge (
		const unsigned int&,
		const unsigned int&,
		const weightType&
	);
	private: static void swap (
		std::vector <connection>&,
		std::vector <weightType>&,
		const unsigned int&,
		const unsigned int&
	);
};
#include "graph.tpp"
#endif