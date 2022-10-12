#pragma once
#ifndef NODE_H
#define NODE_H
#include <iostream>

template<typename T>
struct node
{
    T data;
    node<T>* next;
    node<T>* prev;

    node(T data, node<T>* next = nullptr, node<T>* prev = nullptr): data(data), next(next), prev(prev) {}

    ~node() = default;
};

#endif