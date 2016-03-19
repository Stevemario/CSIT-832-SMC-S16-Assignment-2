template <class weightType>
weightType weighted_connection <weightType>::weightsSum () const {
	return m_weightsSum;
}
template <class weightType>
void weighted_connection <weightType>::set_weightsSum (weightType weightsSum) {
	m_weightsSum = weightsSum;
}
template <class weightType>
bool  weighted_connection <weightType>::operator< (
	const weighted_connection <weightType>& comparison
) const {
	bool lesser = false;
	if (this->weightsSum () > comparison.weightsSum ())
		lesser = true;
	return lesser;
}