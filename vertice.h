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
	public: std::string name () const;
	public: bool hasEdgeTo (
		const unsigned int&
	) const;
	public: virtual void considerAnotherVertice ();
};
class weighted_vertice : public vertice {
	private: std::vector <unsigned int> m_weight;
	public: weighted_vertice (
		const std::string&,
		const unsigned int&
	);
	public: unsigned int weight (
		const unsigned int&
	) const;
	public: void considerAnotherVertice ();
	public: void setWeight (
		const unsigned int&,
		const unsigned int&
	);
};
#endif