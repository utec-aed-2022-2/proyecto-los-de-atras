#pragma once
#ifndef HASHMAP_H
#define HASHMAP_H
#include "nodes.h"

const double maxFillFactor = 0.8;

template <typename K, typename V>
class HashMap
{
private:
	nodeHash<K, V>** array;
	size_t capacity;
	size_t size;

public:
	HashMap();
	~HashMap();
	HashMap(size_t capacity);

	void set(const K& key, const V& value);
	V get(const K& key);
	/*remove section*/

private:
	int hashFunction(const K& key);
	double fillFactor();
	void rehashing();
};

template <typename K, typename V>
HashMap<K, V>::HashMap()
{
	this->capacity = 23;
	this->size = 0;
	this->array = new nodeHash<K, V>*[capacity];
	for (int i = 0; i < capacity; i++) { array[i] = nullptr; }
}

template <typename K, typename V>
HashMap<K, V>::~HashMap() {}

template <typename K, typename V>
HashMap<K, V>::HashMap(size_t capacity)
{
	this->capacity = capacity;
	this->size = 0;
	this->array = new nodeHash<K, V>*[capacity];
	for (int i = 0; i < capacity; i++) { array[i] = nullptr; }
}

template <typename K, typename V>
void HashMap<K, V>::set(const K& key, const V& value)
{
	if(fillFactor() >= maxFillFactor) { rehashing(); }

	nodeHash<K, V>* newNode = new nodeHash<K, V>(key, value);
	int hashIndex = hashFunction(key);

	while (array[hashIndex] != nullptr && array[hashIndex]->key != key)
	{
		hashIndex++;
		hashIndex %= capacity;
	}

	if (array[hashIndex] == nullptr) { size++; }
	array[hashIndex] = newNode;
}

template <typename K, typename V>
V HashMap<K, V>::get(const K& key)
{
	int hashIndex = hashFunction(key);
	int counter = 0;

	while (array[hashIndex] != nullptr)
	{
		if (counter++ > capacity) { throw std::runtime_error("error"); }
		if (array[hashIndex]->key == key) { return array[hashIndex]->value; }
		hashIndex++;
		hashIndex %= capacity;
	}

	throw std::runtime_error("error");
}

template <typename K, typename V>
int HashMap<K, V>::hashFunction(const K& key)
{
	std::hash<K> ptr_hash;
	return ptr_hash(key)%capacity;
}

/*remove section*/

template <typename K, typename V>
double HashMap<K, V>::fillFactor() { return size / (capacity); }

template <typename K, typename V>
void HashMap<K, V>::rehashing()
{
	int prev_capacity = capacity;
	capacity = capacity*2;
	nodeHash<K, V>** prev_array = array;
	array = new nodeHash<K, V>*[capacity];

	for (int i = 0; i < prev_capacity; i++)
	{
		if (prev_array[i] != nullptr)
		{
			int index = hashFunction(prev_array[i]->key);
			nodeHash<K, V>* newNode = new nodeHash<K, V>;
			newNode->key = prev_array[i]->key;
			newNode->value = prev_array[i]->value;
			array[index] = newNode;
		}
	}
	delete [] prev_array;
}

#endif