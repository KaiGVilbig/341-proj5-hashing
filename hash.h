// CMSC 341 - Fall 2019 - Project 5
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************

  //return object because this is not only used for inseret but remove aswell which must print
  //the object aftwr removeing?...
  T tableNum(int loc, bool insert, const T& object, string key)
  {
	  T object1;

	  if (!_table[loc].used() || _table[loc].readTop().key() == key)
	  {
		  if (insert)
		  {
			  _table[loc].insert(object);
			  _n++;
		  }
		  else
		  {
			  object1 = _table[loc].readTop();
			  _table[loc].removeTop();
			  _n--;
		  }
	  }
	  else if (_table[loc].used())
	  {
		  for (unsigned i = 1; i < _N; i++)
		  {
			  loc = (loc + 1) % _N;
			  if (!_table[loc].used() || _table[loc].readTop().key() == key)
			  {
				  if (insert)
				  {
					  _table[loc].insert(object);
					  _n++;
				  }
				  else
				  {
					  object1 = _table[loc].readTop();
					  _table[loc].removeTop();
					  _n--;
				  }
				  break;
			  }
		  }
	  }
	  if (insert)
	  {
		  return object;
	  }
	  else
	  {
		  return object1;
	  }
  }
};

// *****************************************
// Templated function definitions go here! *
// *****************************************

template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash)
{
	_hash = hash;
	_N = size;
	_table = new Heap<T>[_N];
}

template <class T>
HashTable<T>::~HashTable()
{
	delete[] _table;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& ht)
{
	_hash = ht._hash;
	_N = ht._N;
	_table = new Heap<T>[_N];
	for (unsigned i = 0; i < _N; i++)
	{
		_table[i] = ht._table[i];
	}
}

template <class T>
const HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht)
{
	_hash = ht._hash;
	_N = ht._N;
	_table = new Heap<T>[_N];
	for (unsigned i = 0; i < _N; i++)
	{
		_table[i] = ht._table[i];
	}
	return _hash;
}

template <class T>
bool HashTable<T>::insert(const T& object)
{
	int insert = _hash(object.key()) % _N;

	//insert into the appropreate spot
	T o = tableNum(insert, true, object, object.key());

	return true;
}

template <class T>
bool HashTable<T>::getNext(string key, T& obj)
{
	int find = _hash(key) % _N;
	if (!_table[find].empty())
	{
		//change obj to the second intem in the table because next the code 
		//prints the object out but the first item is a holder item.
		obj = tableNum(find, false, obj, key);
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
void HashTable<T>::dump() const
{
	for (unsigned i = 0; i < _N; i++)
	{
		cout << "[" << i << "]: " << endl;
		if (_table[i].used())
		{
			_table[i].dump();
		}
	}
}
#endif
