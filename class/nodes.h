#pragma once
#ifndef NODES_H
#define NODES_H
#include <iostream>
#include <functional>

template<typename T>
struct nodeList
{
    T data;
    nodeList<T>* next;
    nodeList<T>* prev;

    nodeList() = default;
    ~nodeList() = default;
    nodeList(const T& data, nodeList<T>* next = nullptr, nodeList<T>* prev = nullptr): data(data), next(next), prev(prev) {}
};

template <typename K, typename V>
struct nodeHash
{
	V value;
	K key;
    nodeHash() = default;
    ~nodeHash() = default;
	nodeHash(const K& key, const V& value): key(key), value(value) {}
};

template <typename T>
struct nodeBPlus
{
    bool is_leaf;
    size_t maxchildren;
    size_t size;
    T* data;
    nodeBPlus<T>** children;
    nodeBPlus<T>* parent;

    nodeBPlus() = default;
    ~nodeBPlus() = default;
    nodeBPlus(size_t maxchildren): is_leaf(false), maxchildren(maxchildren), size(0), parent(nullptr)
    {
        this->data = new T[maxchildren-1];
        this->children = new nodeBPlus<T>*[maxchildren];
        for(int i = 0; i < maxchildren; i++){ this->children[i] = nullptr; }
    }
};

#endif