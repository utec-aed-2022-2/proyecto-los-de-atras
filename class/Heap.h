#pragma once
#ifndef HEAP_H
#define HEAP_H
#include "../utility/swap.h"

template<typename T, bool activate = false>
class Heap
{
private:
    T* A;
    size_t capacity;
    size_t size;
    std::function<bool(const T&, const T&)> less;
    std::function<bool(const T&, const T&)> greater;

public:
    Heap();
    ~Heap();
    Heap(size_t capacity);
    Heap(size_t capacity, std::function<bool(const T&, const T&)> less, std::function<bool(const T&, const T&)> greater);

    void push(T key);
    void pop();
    T top() const;
    bool empty() const;

private:
    int PARENT(int index) const;
    int LEFT(int index) const;
    int RIGHT(int index) const;
    void heapifyDown(int index);
    void heapifyUp(int index);
};

template<typename T, bool activate>
Heap<T, activate>::Heap()
{
    this->capacity = 7;
    this->size = 0;
    this->A = new T[7];
    if (activate == false)
    {
        this->less = [](const T& first, const T& second) { return first < second; };
        this->greater = [](const T& first, const T& second) { return second < first; };
    }
    else
    {
        this->less = [](const T& first, const T& second) { return second < first; };
        this->greater = [](const T& first, const T& second) { return first < second; };
    }
}

template<typename T, bool activate>
Heap<T, activate>::~Heap() { delete[] A; }

template<typename T, bool activate>
Heap<T, activate>::Heap(size_t capacity)
{
    this->capacity = capacity;
    this->size = 0;
    this->A = new T[capacity];
    if (activate == false)
    {
        this->less = [](const T& first, const T& second) { return first < second; };
        this->greater = [](const T& first, const T& second) { return second < first; };
    }
    else
    {
        this->less = [](const T& first, const T& second) { return second < first; };
        this->greater = [](const T& first, const T& second) { return first < second; };
    }
}

template<typename T, bool activate>
Heap<T, activate>::Heap(size_t capacity, std::function<bool(const T&, const T&)> less, std::function<bool(const T&, const T&)> greater)
{
    this->capacity = capacity;
    this->size = 0;
    this->A = new T[capacity];
    if (activate == false)
    {
        this->less = less;
        this->greater = greater;
    }
    else
    {
        this->less = greater;
        this->greater = less; 
    }
}

template<typename T, bool activate>
void Heap<T, activate>::push(T key)
{
    if (size == capacity)
    {
        T* prevA = A;
        size_t prevCapacity = capacity;
        capacity = capacity*2;
        A = new T[capacity];
        for (int i = 0; i < prevCapacity; i++) { A[i] = prevA[i]; }
        delete prevA;
    }

    A[size] = key;
    size += 1;
    int index = size - 1;
    heapifyUp(index);
}

template<typename T, bool activate>
void Heap<T, activate>::pop()
{
    if (size == 0) { throw std::out_of_range("error"); }
    A[0] = A[size-1];
    size -= 1;
    heapifyDown(0);
}

template<typename T, bool activate>
T Heap<T, activate>::top() const
{
    if (size == 0) { throw std::out_of_range("error"); }
    return A[0];
}

template<typename T, bool activate>
bool Heap<T, activate>::empty() const { return size == 0; }

template<typename T, bool activate>
int Heap<T, activate>::PARENT(int index) const { return (index - 1) / 2; }

template<typename T, bool activate>
int Heap<T, activate>::LEFT(int index) const { return (2*index + 1); }

template<typename T, bool activate>
int Heap<T, activate>::RIGHT(int index) const { return (2*index + 2); }

template<typename T, bool activate>
void Heap<T, activate>::heapifyDown(int index)
{
    int left = LEFT(index);
    int right = RIGHT(index);
    int largest = index;
    if (left < size && greater(A[left], A[index]) /*A[left] > A[index]*/) { largest = left; }
    if (right < size && greater(A[right], A[largest]) /*A[right] > A[largest]*/) { largest = right; }
    if (largest != index)
    {
        swap(A[index], A[largest]);
        heapifyDown(largest);
    }
}

template<typename T, bool activate>
void Heap<T, activate>::heapifyUp(int index)
{
    if (index && less(A[PARENT(index)], A[index]) /*A[PARENT(index)] < A[index]*/)
    {
        swap(A[index], A[PARENT(index)]);
        heapifyUp(PARENT(index));
    }
}

#endif