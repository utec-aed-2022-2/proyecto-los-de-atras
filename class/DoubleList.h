#ifndef DOUBLELIST_H
#define DOUBLELIST_H
#include "nodes.h"

template<typename T>
class list
{
public:
    list() {};
    virtual ~list() {};

    virtual T front() = 0;
    virtual T back() = 0;
    virtual nodeList<T>* begin() = 0;
    virtual nodeList<T>* end() = 0;
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
    virtual size_t size() const = 0;
};

template<typename T>
class doubleList : public list<T>
{
private:
    nodeList<T>* _front;
    nodeList<T>* _back;
    size_t _size;

public:
    doubleList();
    ~doubleList();

    T front();
    T back();
    nodeList<T>* begin();
    nodeList<T>* end();
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
doubleList<T>::doubleList()
{
    this->_front = nullptr;
    this->_back = nullptr;
    this->_size = 0;
}

template<typename T>
doubleList<T>::~doubleList() { clear(); }

template<typename T>
T doubleList<T>::front()
{   
    if (!is_empty()) { return _front->data; }
    else { throw std::runtime_error("empty"); }
}

template<typename T>
T doubleList<T>::back()
{
    if (!is_empty()) { return _back->data; }
    else { throw std::runtime_error("empty"); }
}

template<typename T>
nodeList<T>* doubleList<T>::begin() { return _front; }

template<typename T>
nodeList<T>* doubleList<T>::end() { return _back->next; }

template<typename T>
void doubleList<T>::push_front(T data)
{
    if (is_empty())
    {
        _front = new nodeList<T>(data);
        _back = _front;
    }
    else
    {
        nodeList<T>* newN = new nodeList<T>(data, _front);
        _front->prev = newN;
        _front = newN;
    }

    _size++;
}

template<typename T>
void doubleList<T>::push_back(T data)
{
    if (is_empty()) { push_front(data); }
    else
    {
        _back->next = new nodeList<T>(data, nullptr, _back);
        _back = _back->next;

        _size++;
    }
}

template<typename T>
void doubleList<T>::pop_front()
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
            nodeList<T>* temp = _front->next;
            delete _front;
            _front = temp;
            _front->prev = nullptr;
        }
        _size--;
    }
    else { throw std::runtime_error("empty"); }
}

template<typename T>
void doubleList<T>::pop_back()
{
    if (!is_empty())
    {
        if (_size == 1) { pop_front(); }
        else
        {
            nodeList<T>* temp = _back->prev;
            delete _back;
            _back = temp;
            _back->next = nullptr;

            _size--;
        }
    }
    else { throw std::runtime_error("empty"); }
}

template<typename T>
bool doubleList<T>::is_empty() const { return _size == 0; }

template<typename T>
void doubleList<T>::clear()
{
    nodeList<T>* iter = _front;
    while (iter != nullptr)
    {
        nodeList<T>* next = iter->next;
        delete iter;
        iter = next;
    }

    _front = nullptr;
    _back = nullptr;
    _size = 0;
}

template<typename T>
void doubleList<T>::insert(T data, int pos)
{
    if (!is_empty() && pos < _size)
    {
        nodeList<T>* iter = _front;
        for(int i = 0; i <= pos - 1; i++) { iter = iter->next; }
        nodeList<T>* newN = new nodeList<T>(data, iter->next, iter);
        iter->next = newN;
        newN->next->prev = newN;
        _size++;
    }
    else {  throw std::runtime_error("error"); }
}

template<typename T>
void doubleList<T>::remove(int pos)
{
    if (!is_empty() && pos < _size)
    {
        if (pos == 0) { this->pop_front(); }
        else if (pos == _size - 1) { this->pop_back(); }
        else
        {
            nodeList<T>* iter = _front;
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
T& doubleList<T>::operator[](int pos)
{
    if (!is_empty() && pos < _size)
    {
        nodeList<T>* iter = _front;
        for(int i = 0; i <= pos - 1; i++) { iter = iter->next; }
        return iter->data;
    }
    else { throw std::runtime_error("error"); }
}

template<typename T>
size_t doubleList<T>::size() const { return _size; }

#endif