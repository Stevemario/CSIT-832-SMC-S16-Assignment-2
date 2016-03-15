#include "vertice.h"
vertice::vertice (
	const std::string& name_,
	const unsigned int& nVertices
) {
	m_name = name_;
	for (
		unsigned int vertice = 0;
		vertice <= nVertices;
		vertice++
	) {
		m_weight.push_back (0);
	}
}
std::string vertice::name () const {
	return m_name;
}
unsigned int vertice::weight (const unsigned int& index) const {
	return m_weight[index];
}
void vertice::addWeight (const unsigned int& weight_) {
	m_weight.push_back (weight_);
}
void vertice::setWeight (const unsigned int& index, const unsigned int& weight_) {
	m_weight[index] =  weight_;
}