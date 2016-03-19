//  IMPLEMENTATION  OF RECURSIVE HEAP MEMBER FUNCTIONS
template<class HeapType>
void Heap<HeapType>::ReheapUp (int nIndexOfNodeToMove, int nGenerations, const int nElements)
//This function checks
//if a node has greater priority than a number of its predecessors, and
//if it does,
//it swaps the node's place in the heap with its predecessors.
{
	int nIndexOfNodeParent;

	if (nIndexOfNodeToMove > 0 && nIndexOfNodeToMove < nElements && nGenerations > 0) {
	//if the node's index is positive, and
	//   the node's index is an index for a placed node, and
	//   the number of generations to heap up is positive

		//A node X has 2 children at:
		//A. 2 * X's index + 1, and
		//B. 2 * X's index + 2.
		//So a node Y can have a parent at:
		//A. (Y's index - 1) / 2, or
		//B. (Y's index - 2) / 2,
		//depending on which child it is,
		//left child or right child.
		//Left children's indexes are always odd, meaning
		//left chidren's indexes % 2 will equal 1.
		//Right children's indexes are always even, meaning
		//right children's indexes % 2 will equal 0.

		if (nIndexOfNodeToMove % 2 == 0) {
		//if the node's index is even, meaning
		//if the node is a right child

			nIndexOfNodeParent = (nIndexOfNodeToMove - 2) / 2;
			//the node's parent's index is the difference of
			//the node's index and two,
			//divided by two.
		} else {
		//if the node's index is not even, meaning
		//if the node's index is odd, meaning
		//if the node is a left child

			nIndexOfNodeParent = (nIndexOfNodeToMove - 1) / 2;
			//the node's parent's index is the difference of
			//the node's index and one,
			//divided by two.
		}

		//Using what we know about even numbers, and integers,
		//we can simplify to
		//PROFESSOR KENT'S CODE:
		//parent = (bottom - 1) / 2;

		if (elements[nIndexOfNodeParent] < elements[nIndexOfNodeToMove]) {
		//if the parent node's priority
		//is lesser than
		//the child node's priority

			//the heap's rules are violated.
			//To fix that we start by

			Swap (elements[nIndexOfNodeParent], elements[nIndexOfNodeToMove]);
			//swapping the node with it's parent

			nGenerations--;
			//note that we've gone up a generation

			ReheapUp (nIndexOfNodeParent, nGenerations, nElements);
			//and repeating until the requirements are met.
		}
	}
}
template<class HeapType>
void Heap<HeapType>::ReheapDown (int nIndexOfNodeToMove, int nGenerations, const int nElements)
//This function checks
//if a node has lesser priority than a number of its children, and
//if it does,
//it swaps the node's place in the heap with its successor.
{
	int nIndexOfNodeChildLeft;
	int nIndexOfNodeChildRight;
	int nIndexOfNodeChildWithHigherPriority;

	nIndexOfNodeChildLeft = 2 * nIndexOfNodeToMove + 1;
	nIndexOfNodeChildRight = 2 * nIndexOfNodeToMove + 2;

	if (nIndexOfNodeToMove >= 0 && nIndexOfNodeToMove < nElements  && nGenerations > 0) {
	//if the node's index is positive, or zero, and
	//   the node's index is an index for a placed node, and
	//   the number of generations to heap up is positive.

		if (nIndexOfNodeChildLeft <= nElements - 1) {
		//if the left child is within the heap

			if (nIndexOfNodeChildLeft == nElements - 1)
			//if the left child is the last element

				nIndexOfNodeChildWithHigherPriority = nIndexOfNodeChildLeft;
				//the right child is not within the heap, so
				//the left child is the higher priority valid child

			else {
			//if the left child is not the last element, meaning
			//both left and right children could be promoted

				if (elements[nIndexOfNodeChildLeft] < elements[nIndexOfNodeChildRight])
				//if the left child's priority
				//is lesser than
				//the right child's priority

					nIndexOfNodeChildWithHigherPriority = nIndexOfNodeChildRight;
					//the right child is the higher priority child

				else
				//if the left child's priority
				//is not lesser than
				//the right child's priority

					nIndexOfNodeChildWithHigherPriority = nIndexOfNodeChildLeft;
					//the left child is the higher priority child,
					//in this case, due the job class member
					//job will prevent equal priority.
					//in other cases, ties are possible,
					//but not important, left child is chosen
					//just because one has to be chosen.
			}
			if (elements[nIndexOfNodeToMove] < elements[nIndexOfNodeChildWithHigherPriority]) {
			//if the node's priority
			//is lesser than
			//the bigger child's priority
				
				//the heap's rules are violated.
				//To fix that we start by

				Swap (elements[nIndexOfNodeToMove], elements[nIndexOfNodeChildWithHigherPriority]);
				//swapping the node with it's bigger child

				nGenerations--;
				//note that we've gone down a generation

				ReheapDown (nIndexOfNodeChildWithHigherPriority, nGenerations, nElements);
				//and repeating until the requirements are met.
			}
		}
	}
}
template<class HeapType>
void Heap<HeapType>::Swap (HeapType& a, HeapType& b) {
	HeapType temp;
	temp = a;
	a = b;
	b = temp;
}