
#include <iostream>
#include <stdexcept>
#include "QueueADT.h"

using namespace std;

template <typename E> 
class PriorityQueue :  Queue<E> {
private:

	E *items;
	unsigned int count = 0;
	bool(*compareFunction)(E, E);
	void operator =(const PriorityQueue&) { }; 
	PriorityQueue(const PriorityQueue&){ }; 

	void init() 
	{  
		this->items = new E[10]();
		this->count = 0;
	}

	void removeall() { }

	//void printInOrder(int index) {  // not sure if needed.
	//	if (index > count) {
	//		return;
	//	}
	//	cout << items[index] << " ";

	//}

public:
	PriorityQueue( bool(*func)(E, E) )
	{
		compareFunction = func;
		init();
	} 
	void print() const
	{
		for (int i = 1; i <= count; ++i) {
			cout << items[i] << " ";
		}
	}
	 ~PriorityQueue() { } 
	 void clear(){ } 

	// Place an element at the position 
	// based on its prioity of the queue.
	// it: The element being enqueued.
	 void enqueue(const E& it)	 {
		
		 // Needs to be written
	 }

	// Remove and return element at the front of the queue.
	// Return: The element at the front of the queue.
	 E dequeue() {

		 // Needs to be written
		 
		 return E();		  
	 }

	// Return: A copy of the front element.
	 const E& frontValue() const
	 {
		 return items[1];
		
	 }

	// Return: The number of elements in the queue.
	 int length() const
	 {
		 // needs to be written

		 return 0;
	 }
};
