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

    T front()
    {   
        if (!is_empty()) { return _front->data; }
        else { throw std::runtime_error("empty"); }
    }

    T back()
    {
        if (!is_empty()) { return _back->data; }
        else { throw std::runtime_error("empty"); }
    }

    void push_front(T data)
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

    void push_back(T data)
    {
        if (is_empty()) { push_front(data); }
        else
        {
            _back->next = new nfdl::node<T>(data, nullptr, _back);
            _back = _back->next;

            _size++;
        }
    }

    void pop_front()
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

    void pop_back()
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

    bool is_empty() const
    {
        return _size == 0;
    }

    void clear()
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

    // extra
    void insert(T data, int pos)
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

    void remove(int pos)
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

    T& operator[](int pos)
    {
        if (!is_empty() && pos < _size)
        {
            nfdl::node<T>* iter = _front;
            for(int i = 0; i <= pos - 1; i++) { iter = iter->next; }
            return iter->data;
        }
        else { throw std::runtime_error("error"); }
    }

    std::size_t size() const { return _size; }
};

#endif