#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "nodes.h"

template <typename K, typename V>
class hashtable
{
private:
    nfht::node<K, V>** array;
	std::size_t capacity;
	std::size_t size;

public:
	hashtable(): capacity(20), size(0) { array = new hashtable<K, V>*[capacity]; }

	void insert(K key, V value);

private:
	int hashCode(K key)
	{
		return key % capacity;
	}
};

#endif