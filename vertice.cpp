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
		considerAnotherVertice ();
	}
}
vertice::vertice (
	const std::string& name
) {
	m_name = name;
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