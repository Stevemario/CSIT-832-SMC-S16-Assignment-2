#ifndef VERTEX_H
#define VERTEX_H
#include <string>
#include <vector>
class vertex {
	private: std::string m_name;
	protected: std::vector <bool> m_hasEdgeTo;
	public: vertex (
		const std::string&,
		const unsigned int&
	);
	protected: vertex (
		const std::string&
	);
	public: std::string name () const;
	public: bool hasEdgeTo (
		const unsigned int&
	) const;
	public: virtual void addEdge (
		const unsigned int&
	);
	public: virtual void considerAnotherVertice ();
	public: unsigned int nVerticesConsidered () const;
};
template <class weightType>
class weighted_vertex : public vertex {
	private: std::vector <weightType*> m_weight;
	public: weighted_vertex (
		const std::string&,
		const unsigned int&
	);
	public: weighted_vertex (
		const weighted_vertex <weightType>&
	);
	public: ~weighted_vertex ();
	public: weightType weight (
		const unsigned int&
	) const;
	private: void addEdge (
		const unsigned int&
	);
	public: void considerAnotherVertice ();
	public: void setWeight (
		const unsigned int&,
		const weightType&
	);
};
#include "vertex.tpp"
#endif