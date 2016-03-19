#ifndef HEAP_H
#define HEAP_H
#include <vector>
template<class HeapType>
struct Heap {
	std::vector<HeapType> elements;
	void ReheapUp (int, int, const int);
	void ReheapDown (int, int, const int);
	void Swap (HeapType&, HeapType&);
};
#include "heap.tpp"
#endif