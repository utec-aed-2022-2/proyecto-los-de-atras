#pragma once
#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H
#include "list.h"

template<typename T>
class double_list : public list<T>
{
private:
    nfdl::node<T>* _front;
    nfdl::node<T>* _back;
    std::size_t _size;

public:
    double_list(): _front(nullptr), _back(nullptr), _size(0) {}
    ~double_list() { clear(); }

    T front();
    T back();
    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    bool is_empty() const;
    void clear();
    //
    void insert(T data, int pos);
    void remove(int pos);
    T& operator[](int pos);
    size_t size() const;
};

template<typename T>
T double_list<T>::front()
{   
    if (!is_empty()) { return _front->data; }
    else { throw std::runtime_error("empty"); }
}

template<typename T>
T double_list<T>::back()
{
    if (!is_empty()) { return _back->data; }
    else { throw std::runtime_error("empty"); }
}

template<typename T>
void double_list<T>::push_front(T data)
{
    if (is_empty())
    {
        _front = new nfdl::node<T>(data);
        _back = _front;
    }
    else
    {
        nfdl::node<T>* newN = new nfdl::node<T>(data, _front);
        _front->prev = newN;
        _front = newN;
    }

    _size++;
}

template<typename T>
void double_list<T>::push_back(T data)
{
    if (is_empty()) { push_front(data); }
    else
    {
        _back->next = new nfdl::node<T>(data, nullptr, _back);
        _back = _back->next;

        _size++;
    }
}

template<typename T>
void double_list<T>::pop_front()
{
    if (!is_empty())
    {
        if (_size == 1)
        {
            delete _front;
            _front = nullptr;
            _back = nullptr;
        }
        else
        {
            nfdl::node<T>* temp = _front->next;
            delete _front;
            _front = temp;
            _front->prev = nullptr;
        }
        _size--;
    }
    else { throw std::runtime_error("empty"); }
}

template<typename T>
void double_list<T>::pop_back()
{
    if (!is_empty())
    {
        if (_size == 1) { pop_front(); }
        else
        {
            nfdl::node<T>* temp = _back->prev;
            delete _back;
            _back = temp;
            _back->next = nullptr;

            _size--;
        }
    }
    else { throw std::runtime_error("empty"); }
}

template<typename T>
bool double_list<T>::is_empty() const { return _size == 0; }

template<typename T>
void double_list<T>::clear()
{
    nfdl::node<T>* iter = _front;
    while (iter != nullptr)
    {
        nfdl::node<T>* next = iter->next;
        delete iter;
        iter = next;
    }

    _front = nullptr;
    _back = nullptr;
    _size = 0;
}

template<typename T>
void double_list<T>::insert(T data, int pos)
{
    if (!is_empty() && pos < _size)
    {
        nfdl::node<T>* iter = _front;
        for(int i = 0; i <= pos - 1; i++) { iter = iter->next; }
        nfdl::node<T>* newN = new nfdl::node<T>(data, iter->next, iter);
        iter->next = newN;
        newN->next->prev = newN;
        _size++;
    }
    else {  throw std::runtime_error("error"); }
}

template<typename T>
void double_list<T>::remove(int pos)
{
    if (!is_empty() && pos < _size)
    {
        if (pos == 0) { this->pop_front(); }
        else if (pos == _size - 1) { this->pop_back(); }
        else
        {
            nfdl::node<T>* iter = _front;
            for(int i = 0; i <= pos - 1; i++) { iter = iter->next; }
            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;

            _size--;
            delete iter;
        }
    }
    else { throw std::runtime_error("error"); }
}

template<typename T>
T& double_list<T>::operator[](int pos)
{
    if (!is_empty() && pos < _size)
    {
        nfdl::node<T>* iter = _front;
        for(int i = 0; i <= pos - 1; i++) { iter = iter->next; }
        return iter->data;
    }
    else { throw std::runtime_error("error"); }
}

template<typename T>
size_t double_list<T>::size() const { return _size; }

#endif