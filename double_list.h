#pragma once
#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H
#include "list.h"

template<typename T>
class double_list : public list<T>
{
private:
    node<T>* _front;
    node<T>* _back;
    size_t _size;

public:
    double_list(): _front(nullptr), _back(nullptr), _size(0) {}

    ~double_list() { clear(); }

    T front()
    {   
        if (!is_empty()) { return _front->data; }
        else { throw ("empty"); }
    }

    T back()
    {
        if (!is_empty()) { return _back->data; }
        else { throw ("empty"); }
    }

    void push_front(T data)
    {
        if (is_empty())
        {
            _front = new node<T>(data);
            _back = _front;
        }
        else
        {
            node<T>* newN = new node<T>(data, _front);
            _front->prev = newN;
            _front = newN;
        }

        _size++;
    }

    void push_back(T data)
    {
        if (is_empty())
        {
            push_front(data);
        }
        else
        {
            _back->next = new node<T>(data, nullptr, _back);
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
                node<T>* temp = _front->next;
                delete _front;
                _front = temp;
                _front->prev = nullptr;
            }
            _size--;
        }
        else { throw ("empty"); }
    }

    void pop_back()
    {
        if (!is_empty())
        {
            if (_size == 1)
            {
                pop_front();
            }
            else
            {
                node<T>* temp = _back->prev;
                delete _back;
                _back = temp;
                _back->next = nullptr;

                _size--;
            }
        }
        else { throw ("empty"); }
    }

    bool is_empty() const
    {
        return _size == 0;
    }

    void clear()
    {
        node<T>* iter = _front;
        while (iter != nullptr)
        {
            node<T>* next = iter->next;
            delete iter;
            iter = next;
        }

        _front = nullptr;
        _back = nullptr;
        _size = 0;
    }

    // ---
    void insert(T data, int pos)
    {
        if (!is_empty() && pos < _size)
        {
            node<T>* iter = _front;
            for(int i = 0; i <= pos - 1; i++){
                iter = iter->next;
            }
            node<T>* newN = new node<T>(data, iter->next, iter);
            iter->next = newN;
            newN->next->prev = newN;
            _size++;
        }
        else
        {
            throw ("error");
        }
    }

    void remove(int pos)
    {
        if (!is_empty() && pos < _size)
        {
            if (pos == 0)
            {
                this->pop_front();
            }
            else if (pos == _size - 1)
            {
                this->pop_back();
            }
            else
            {
                node<T>* iter = _front;
                for(int i = 0; i <= pos - 1; i++){
                    iter = iter->next;
                }
                iter->prev->next = iter->next;
                iter->next->prev = iter->prev;
                _size--;
                delete iter;
            }
        }
        else
        {
            throw ("error");
        }
    }

    T& operator[](int pos)
    {
        if (!is_empty() && pos < _size)
        {
            node<T>* iter = _front;
            for(int i = 0; i <= pos - 1; i++){
                iter = iter->next;
            }
            return iter->data;
        }
        else
        {
            throw ( "error");
        }
    }

    size_t size() { return _size; }
    // ---
};

#endif