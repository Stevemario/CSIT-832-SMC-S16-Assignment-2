template<class PriorityQueueType>
PriorityQueue<PriorityQueueType>::PriorityQueue () {
	m_nElements = 0;
}
template<class PriorityQueueType>
PriorityQueue<PriorityQueueType>::PriorityQueue (const PriorityQueue& pqToCopy) {
	m_nElements = pqToCopy.nElements ();
	for (int i = 0; i < m_nElements; i++) {
		items.elements.push_back (pqToCopy.element (i));
	}
}
template<class PriorityQueueType>
PriorityQueue<PriorityQueueType>::~PriorityQueue () {
	items.elements.clear ();
}
template<class PriorityQueueType>
bool PriorityQueue<PriorityQueueType>::bIsEmpty () const {
	return (m_nElements == 0);
}
template<class PriorityQueueType>
void PriorityQueue<PriorityQueueType>::enqueue (PriorityQueueType newItem) {
	int nHeight;
	items.elements.push_back (newItem);
	m_nElements++;
	nHeight = nGeneration (m_nElements);
	items.ReheapUp (m_nElements - 1, nHeight - 1, m_nElements);
}
template<class PriorityQueueType>
void PriorityQueue<PriorityQueueType>::dequeue (PriorityQueueType& item) {
	int nHeight;
	item = items.elements[0];
	m_nElements--;
	if (0 < m_nElements) {
		items.elements[0] = items.elements[m_nElements];
		nHeight = nGeneration (m_nElements);
		items.ReheapDown (0, nHeight - 1, m_nElements);
	}
	items.elements.pop_back ();
}
template<class PriorityQueueType>
int PriorityQueue<PriorityQueueType>::nElements () const {
	return m_nElements;
}
template<class PriorityQueueType>
PriorityQueueType PriorityQueue<PriorityQueueType>::element (int nIndex) const {
	PriorityQueueType element = items.elements[nIndex];
	return element;
}
template<class PriorityQueueType>
int PriorityQueue<PriorityQueueType>::nGeneration (const int nIndex) {
	int nGeneration = 0;
	int nFactor = 1;
	while ((nIndex / nFactor) > 0) {
		nGeneration++;
		nFactor *= 2;
	}
	return nGeneration;
}