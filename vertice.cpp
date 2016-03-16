#include "vertice.h"
vertice::vertice (
	const std::string& name,
	const unsigned int& nVertices
) {
	m_name = name;
	for (
		unsigned int vertice = 0;
		vertice <= nVertices;
		vertice++
	) {
		m_hasEdgeTo.push_back (false);
	}
}
std::string vertice::name () const {
	return m_name;
}
bool vertice::hasEdgeTo (
	const unsigned int& index
) const {
	return m_hasEdgeTo [index];
}
void vertice::considerAnotherVertice () {
	m_hasEdgeTo.push_back (false);
}
weighted_vertice::weighted_vertice (
	const std::string& name,
	const unsigned int& nVertices
) : vertice (name, nVertices) {
	for (
		unsigned int vertice = 0;
		vertice <= nVertices;
		vertice++
	) {
		m_weight.push_back (0);
	}
}
unsigned int weighted_vertice::weight (
	const unsigned int& index
) const {
	return m_weight [index];
}
void weighted_vertice::considerAnotherVertice () {
	m_hasEdgeTo.push_back (false);
	m_weight.push_back (0);
}
void weighted_vertice::setWeight (
	const unsigned int& index,
	const unsigned int& weight
) {
	if (m_hasEdgeTo [index])
		m_weight [index] =  weight;
	else {
		m_hasEdgeTo [index] = true;
		m_weight [index] =  weight;
	}
}