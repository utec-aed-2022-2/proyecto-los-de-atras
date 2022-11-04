#pragma once
#ifndef LIST_H
#define LIST_H
#include "nodes.h"

template<typename T>
class list
{
public:
    list() {};
    virtual ~list() {};
    virtual T front() = 0;
    virtual T back() = 0;
    virtual void push_front(T) = 0;
    virtual void push_back(T) = 0;
    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
    virtual bool is_empty() const = 0;
    virtual void clear() = 0;
    //
    virtual void insert(T, int) = 0;
    virtual void remove(int) = 0;
    virtual T& operator[](int) = 0;
    virtual std::size_t size() const = 0;
};

#endif