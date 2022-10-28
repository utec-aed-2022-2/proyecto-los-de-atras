#pragma once
#ifndef NODE_H
#define NODE_H
#include <iostream>

namespace nl
{
template<typename T>
struct node
{
    T data;
    node<T>* next;
    node<T>* prev;

    node(T data, node<T>* next = nullptr, node<T>* prev = nullptr): data(data), next(next), prev(prev) {}

    ~node() = default;
};  
};

namespace nbpt
{
template <typename T>
struct node
{
    std::size_t maxchildren;
    std::size_t size;
    T* item;
    Node<T>** children;
    Node<T>* parent;

public:
    Node(std::size_t maxchildren): maxchildren(maxchildren)
    {
        this->size = 0;

        T* _item = new T[maxchildren-1];
        for(int i = 0; i < maxchildren-1; i++){
            _item[i] = T();
        }
        this->item = _item;

        Node<T>** _children = new Node<T>*[maxchildren];
        for(int i = 0; i < maxchildren; i++){
            _children[i] = nullptr;
        }
        this->children = _children;

        this->parent = nullptr;
    }
};
};

#endif