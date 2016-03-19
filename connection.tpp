template <class weightType>
weightType weighted_connection <weightType>::weightsSum () const {
	return m_weightsSum;
}
template <class weightType>
void weighted_connection <weightType>::set_weightsSum (weightType weightsSum) {
	m_weightsSum = weightsSum;
}