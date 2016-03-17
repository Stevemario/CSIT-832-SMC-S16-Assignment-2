#ifndef VERTICE_H
#define VERTICE_H
#include <string>
#include <vector>
class vertice {
	private: std::string m_name;
	protected: std::vector <bool> m_hasEdgeTo;
	public: vertice (
		const std::string&,
		const unsigned int&
	);
	protected: vertice (
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
};
template <class weightType>
class weighted_vertice : public vertice {
	private: std::vector <weightType*> m_weight;
	public: weighted_vertice (
		const std::string&,
		const unsigned int&
	);
	public: ~weighted_vertice ();
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
#include "vertice.tpp"
#endif