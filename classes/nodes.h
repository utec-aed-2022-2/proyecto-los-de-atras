#pragma once
#ifndef NODES_H
#define NODES_H
#include <iostream>

namespace nfdl
{
template<typename T>
struct node
{
    T data;
    nfdl::node<T>* next;
    nfdl::node<T>* prev;

    node() = default;
    ~node() = default;
    node(T data, nfdl::node<T>* next = nullptr, nfdl::node<T>* prev = nullptr): data(data), next(next), prev(prev) {}
};
};

namespace nfbpt
{
template <typename T>
struct node
{   
    bool is_leaf;
    std::size_t maxchildren;
    std::size_t size;
    T* data;
    nfbpt::node<T>** children;
    nfbpt::node<T>* parent;

    node() = default;
    ~node() = default;
    node(std::size_t maxchildren): is_leaf(false), maxchildren(maxchildren), size(0), parent(nullptr)
    {

        T* _data = new T[maxchildren-1];
        for(int i = 0; i < maxchildren-1; i++)
        {
            _data[i] = T();
        }
        this->data = _data;

        nfbpt::node<T>** _children = new nfbpt::node<T>*[maxchildren];
        for(int i = 0; i < maxchildren; i++)
        {
            _children[i] = nullptr;
        }
        this->children = _children;
    }
};
};

namespace nfht
{
template <typename K, typename V>
struct node
{
	V value;
	K key;
    node() = default;
    ~node() = default;
	node(K key, V value): key(key), value(value) {}
};
};

#endif