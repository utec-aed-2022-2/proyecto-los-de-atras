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
    node<T>* next;
    node<T>* prev;

    node() = default;
    ~node() = default;
    node(T data, node<T>* next = nullptr, node<T>* prev = nullptr): data(data), next(next), prev(prev) {}
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
    node<T>** children;
    node<T>* parent;

    node() = default;
    ~node() = default;
    node(std::size_t maxchildren, node<T>* parent = nullptr): is_leaf(false), maxchildren(maxchildren), size(0)
    {

        T* _data = new T[maxchildren-1];
        for(int i = 0; i < maxchildren-1; i++)
        {
            _data[i] = T();
        }
        this->data = _data;

        node<T>** _children = new node<T>*[maxchildren];
        for(int i = 0; i < maxchildren; i++)
        {
            _children[i] = nullptr;
        }
        this->children = _children;
    }
};
};

#endif