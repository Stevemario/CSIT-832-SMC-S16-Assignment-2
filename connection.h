#ifndef CONNECTION_H
#define CONNECTION_H
#include <vector>
//typedef std::vector <unsigned int> connection;
class connection {
	private: std::vector <unsigned int> m_indexOfDeparture;
	public: int indexOfDeparture (
		const unsigned int&
	) const;
	public: int nDepartures () const;
	public: virtual void addDeparture (
		const unsigned int&
	);
	public: virtual void removeLastDeparture ();
};
template <class weightType>
class weighted_connection : public connection {
	private: weightType m_weightsSum;
	public: weightType weightsSum () const;
	public: void set_weightsSum (weightType);
};
#include "connection.tpp"
#endif