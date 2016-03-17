#include "vertex.h"
vertex::vertex (
	const std::string& name,
	const unsigned int& nVertices
) {
	m_name = name;
	for (
		unsigned int vertice = 0;
		vertice <= nVertices;
		vertice++
	) {
		considerAnotherVertice ();
	}
}
vertex::vertex (
	const std::string& name
) {
	m_name = name;
}
std::string vertex::name () const {
	return m_name;
}
bool vertex::hasEdgeTo (
	const unsigned int& index
) const {
	return m_hasEdgeTo [index];
}
void vertex::addEdge (
	const unsigned int& index
) {
	m_hasEdgeTo [index] = true;
}
void vertex::considerAnotherVertice () {
	m_hasEdgeTo.push_back (false);
}