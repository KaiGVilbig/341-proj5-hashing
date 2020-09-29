// CMSC 341 - Fall 2019 - Project 5
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.

  // *********************************************
  // Private helper function declarations go here!
  // *********************************************

  //make sure maxheap property is good. if not. fix
  void upHeap();
  void downHeap();
};

// ***************************************
// Templated function definitions go here!
// ***************************************

template <class T> 
Heap<T>::Heap()
{
	vector<T> _heap;
	_used = false;
}

template <class T>
void Heap<T>::insert(const T& object)
{
	if (empty())
	{
		if (_heap.size() == 0)
		{
			T holder;
			_heap.push_back(holder);
		}
		_used = true;
	}
	_heap.push_back(object);
	if (!empty()) upHeap();
}

template <class T>
void Heap<T>::upHeap()
{

	unsigned int i = size();
	while (i > 1)
	{
		if (_heap[i].priority() > _heap[(i / 2)].priority())
		{
			swap(_heap[i], _heap[(i / 2)]);
			i = i / 2;
		}
		else
		{
			break;
		}
	}
}

template <class T>
T Heap<T>::readTop() const
{
	if (empty())
	{
		throw range_error("Attempted to read from an empty heap");
	}
	else
	{
		return _heap[1];
	}
}

template <class T>
void Heap<T>::removeTop()
{
	if (empty())
	{
		throw range_error("Attempted to remove from an empty heap");
	}
	else
	{
		swap(_heap[1], _heap.back());
		_heap.pop_back();
		downHeap();

		if (empty())
		{
			_used = false;
		}
	}
}

template <class T>
void Heap<T>::downHeap()
{
	unsigned int i = 1;

	while ((i * 2) < _heap.size() && (i * 2 + 1) < _heap.size())
	{
		if (_heap[i * 2].priority() < _heap[i * 2 + 1].priority())
		{
			swap(_heap[i], _heap[i * 2]);
			i = i * 2;
		}
		else
		{
			swap(_heap[i], _heap[i * 2 + 1]);
			i = i * 2 + 1;
		}
	}
	if ((i * 2) < _heap.size() && _heap[i].priority() < _heap[i * 2].priority())
	{
		swap(_heap[i], _heap[i * 2]);
	}
}

template <class T>
void Heap<T>::dump() const
{
	for (unsigned int i = 1; i <= size(); i++)
	{
		cout << _heap[i] << endl;
	}
}
#endif
