#include "connection.h"
int connection::indexOfDeparture (
	const unsigned int& departure
) const {
	return m_indexOfDeparture [departure];
}
int connection::nDepartures () const {
	return m_indexOfDeparture.size ();
}
void connection::addDeparture (
	const unsigned int& departure
) {
	m_indexOfDeparture.push_back (departure);
}
void connection::removeLastDeparture () {
	m_indexOfDeparture.pop_back ();
}