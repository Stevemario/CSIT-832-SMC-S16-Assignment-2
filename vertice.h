#ifndef VERTICE_H
#define VERTICE_H
#include <string>
#include <vector>
class graph;
class vertice {
	private: std::string m_name;
	private: std::vector <unsigned int> m_weight;
	public: vertice (const std::string&, const unsigned int&);
	public: std::string name () const;
	public: unsigned int weight (const unsigned int&) const;
	public: void addWeight (const unsigned int&);
	public: void setWeight (const unsigned int&, const unsigned int&);
};
#endif