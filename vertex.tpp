template <class weightType>
weighted_vertex <weightType>::weighted_vertex (
	const std::string& name,
	const unsigned int& nVertices
) : vertex (name) {
	for (
		unsigned int vertice = 0;
		vertice <= nVertices;
		vertice++
	) {
		considerAnotherVertice ();
	}
}
template <class weightType>
weighted_vertex <weightType>::weighted_vertex (
	const weighted_vertex <weightType>& source
) : vertex (source.name ()) {
	unsigned int nVerticesConsidered = source.nVerticesConsidered ();
	for (
		unsigned int vertexIndex = 0;
		vertexIndex < nVerticesConsidered;
		vertexIndex++
	) {
		considerAnotherVertice ();
		if (source.hasEdgeTo (vertexIndex)) {
			m_hasEdgeTo [vertexIndex] = true;
			m_weight [vertexIndex] = new weightType (source.weight (vertexIndex));
		}
	}
}
template <class weightType>
weighted_vertex <weightType>::~weighted_vertex () {
	unsigned int nVertices = m_hasEdgeTo.size ();
	for (
		unsigned int vertice = 0;
		vertice < nVertices;
		vertice++
	) {
		if (m_hasEdgeTo [vertice])
			delete m_weight [vertice];
	}
}
template <class weightType>
weightType weighted_vertex <weightType>::weight (
	const unsigned int& index
) const {
	return *m_weight [index];
}
template <class weightType>
void weighted_vertex <weightType>::addEdge (
	const unsigned int& index
) {
	//DO NOTHING
	//THIS IS HERE SO YOU DON'T CALL THE BASE CLASS FUNCTION
}
template <class weightType>
void weighted_vertex <weightType>::considerAnotherVertice () {
	m_hasEdgeTo.push_back (false);
	m_weight.push_back (nullptr);
}
template <class weightType>
void weighted_vertex <weightType>::setWeight (
	const unsigned int& index,
	const weightType& weight
) {
	if (m_hasEdgeTo [index]) {
		weightType temp = weight;
		m_weight [index] = &temp;
	} else {
		m_hasEdgeTo [index] = true;
		m_weight [index] =  new weightType (weight);
	}
}