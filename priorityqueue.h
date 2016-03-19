#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "heap.h"
template<class PriorityQueueType>
class PriorityQueue {
	public: PriorityQueue ();
	public: PriorityQueue (const PriorityQueue&);
	public: ~PriorityQueue ();
	public: bool bIsEmpty () const;
	public: void enqueue (PriorityQueueType);
	public: void dequeue (PriorityQueueType&);
	private: int m_nElements;
	public: int nElements () const;
	private: Heap<PriorityQueueType> items;
	public: PriorityQueueType element (int) const;
	public: static int nGeneration (const int);
};
#include "priorityqueue.tpp"
#endif