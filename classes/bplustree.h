#pragma once
#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include "nodes.h"

template <typename T>
class bplustree
{
private:
    nfbpt::node<T>* root;
    std::size_t maxchildren;

public:
    bplustree() = default;
    bplustree(std::size_t _maxchildren): maxchildren(_maxchildren), root(nullptr) {}
    ~bplustree() { clear(this->root); }

    nfbpt::node<T>* GetRoot() const;
    void insert(T key);
    /*remove section*/
    bool search(T key) const;

private:
    int find_index(T* arr, T key, std::size_t len) const;
    nfbpt::node<T>* find_node(nfbpt::node<T>* node, T key) const;
    T* item_insert(T* arr, T key, std::size_t len);
    nfbpt::node<T>** child_insert(nfbpt::node<T>** childArr, nfbpt::node<T>*child, std::size_t len, int index);
    nfbpt::node<T>* child_item_insert(nfbpt::node<T>* node, nfbpt::node<T>* child, T key);
    void insertR(nfbpt::node<T>* node, nfbpt::node<T>* child, T key);
    /*remove section*/
    nfbpt::node<T>* search_node(nfbpt::node<T>* node, T key);
    void clear(nfbpt::node<T>* node);
};

template <typename T>
int bplustree<T>::find_index(T* arr, T key, std::size_t len) const
{
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        if (key < arr[i])
        {
            index = i;
            break;
        }
        if (i == len-1)
        {
            index = len;
            break;
        }
    }
    return index;
}

template <typename T>
nfbpt::node<T>* bplustree<T>::find_node(nfbpt::node<T>* node, T key) const
{
    if (node == nullptr) { return nullptr; }
    else
    {
        nfbpt::node<T>* iterator = node;
        while (!iterator->is_leaf)
        {
            for (int i = 0; i < iterator->size; i++)
            {
                if (key < iterator->data[i])
                {
                    iterator = iterator->children[i];
                    break;
                }
                if (i == (iterator->size)-1)
                {
                    iterator = iterator->children[i+1];
                    break;
                }
            }
        }
        return iterator;
    }
}

template <typename T>
T* bplustree<T>::item_insert(T* arr, T key, std::size_t len)
{
    int index = find_index(arr, key, len);
    for(int i = len; i > index; i--)
    {
        arr[i] = arr[i-1];
    }
    arr[index] = key;
    return arr;
}

template <typename T>
nfbpt::node<T>** bplustree<T>::child_insert(nfbpt::node<T>** childArr, nfbpt::node<T>*child, std::size_t len, int index)
{
    for (int i = len; i > index; i--) { childArr[i] = childArr[i - 1]; }
    childArr[index] = child;
    return childArr;
}

template <typename T>
nfbpt::node<T>* bplustree<T>::child_item_insert(nfbpt::node<T>* node, nfbpt::node<T>* child, T key)
{
    int itemIndex = find_index(node->data, key, node->size);
    int childIndex = find_index(node->data, key, node->size) + 1;
    for(int i = node->size; i > itemIndex; i--){ node->data[i] = node->data[i-1]; }
    for(int i = node->size+1; i > childIndex; i--){ node->children[i] = node->children[i-1]; }
    node->data[itemIndex] = key;
    node->children[childIndex] = child;
    return node;
}

template <typename T>
void bplustree<T>::insertR(nfbpt::node<T>* node, nfbpt::node<T>* child, T key)
{
    nfbpt::node<T>* iterator = node;
    if (iterator->size < this->maxchildren-1)
    {
        iterator = child_item_insert(iterator,child, key);
        iterator->size++;
    }
    else
    {
        nfbpt::node<T>* newNode = new nfbpt::node<T>(this->maxchildren);
        newNode->parent = iterator->parent;

        T* itemCopy = new T[iterator->size+1];
        for (int i = 0; i < iterator->size; i++) { itemCopy[i] = iterator->data[i]; }
        itemCopy = item_insert(itemCopy, key, iterator->size);

        nfbpt::node<T>** childCopy = new nfbpt::node<T>*[iterator->size+2];
        for (int i = 0; i < iterator->size+1; i++) { childCopy[i] = iterator->children[i]; }
        childCopy[iterator->size+1] = nullptr;
        childCopy = child_insert(childCopy, child, iterator->size+1, find_index(itemCopy, key, iterator->size+1));
        
        iterator->size = (this->maxchildren)/2;
        if ((this->maxchildren) % 2 == 0) { newNode->size = (this->maxchildren) / 2 - 1; }
        else { newNode->size = (this->maxchildren) / 2; }
        for (int i = 0; i < iterator->size; i++)
        {
            iterator->data[i] = itemCopy[i];
            iterator->children[i] = childCopy[i];
        }
        iterator->children[iterator->size] = childCopy[iterator->size];

        for (int i = 0; i < newNode->size; i++)
        {
            newNode->data[i] = itemCopy[iterator->size+i+1];
            newNode->children[i] = childCopy[iterator->size+i+1];
            newNode->children[i]->parent = newNode;
        }
        newNode->children[newNode->size] = childCopy[iterator->size+newNode->size+1];
        newNode->children[newNode->size]->parent = newNode;

        T parentItem = itemCopy[this->maxchildren/2];
        delete[] itemCopy;
        delete[] childCopy;
        if (iterator->parent == nullptr)
        {
            nfbpt::node<T>* newParent = new nfbpt::node<T>(this->maxchildren);
            iterator->parent = newParent;
            newNode->parent = newParent;

            newParent->data[0] = parentItem;
            newParent->size++;

            newParent->children[0] = iterator;
            newParent->children[1] = newNode;

            this->root = newParent;
        }
        else
        {
            insertR(iterator->parent, newNode, parentItem);
        }
    }
}

/*remove section*/

template <typename T>
nfbpt::node<T>* bplustree<T>::search_node(nfbpt::node<T>* node, T key)
{
    nfbpt::node<T>* iterator = find_node(node, key);
    for (int i = 0; i < iterator->size; i++) { if (iterator->data[i] == key) { return iterator; } }
    return nullptr;
}

template <typename T>
void bplustree<T>::clear(nfbpt::node<T>* node)
{
    if (node != nullptr)
    {
        if (!node->is_leaf) { for (int i = 0; i <= node->size; i++) { clear(node->children[i]); } }
        delete[] node->data;
        delete[] node->children;
        delete node;
    }
}

template <typename T>
nfbpt::node<T>* bplustree<T>::GetRoot() const { return this->root; }

template <typename T>
void bplustree<T>::insert(T key)
{
    if (this->root == nullptr)
    {
        this->root = new nfbpt::node<T>(this->maxchildren);
        this->root->is_leaf = true;
        this->root->data[0] = key;
        this->root->size = 1;
    }
    else
    {
        nfbpt::node<T>* iterator = this->root;
        
        iterator = find_node(iterator, key);

        if (iterator->size < (this->maxchildren-1))
        {
            iterator->data = item_insert(iterator->data, key, iterator->size);
            iterator->size++;

            iterator->children[iterator->size] = iterator->children[iterator->size-1];
            iterator->children[iterator->size-1] = nullptr;
        }
        else
        {
            nfbpt::node<T>* newNode = new nfbpt::node<T>(this->maxchildren);
            newNode->is_leaf = true;
            newNode->parent = iterator->parent;

            T* itemCopy = new T[iterator->size+1];
            for (int i = 0; i < iterator->size; i++) { itemCopy[i] = iterator->data[i]; }
            itemCopy = item_insert(itemCopy, key, iterator->size);

            iterator->size = (this->maxchildren)/2;
            if ((this->maxchildren) % 2 == 0) { newNode->size = (this->maxchildren) / 2; }
            else { newNode->size = (this->maxchildren) / 2 + 1; }
            for (int i = 0; i < iterator->size; i++){ iterator->data[i] = itemCopy[i]; }
            for (int i = 0; i < newNode->size; i++){ newNode->data[i] = itemCopy[iterator->size + i]; }

            iterator->children[iterator->size] = newNode;
            newNode->children[newNode->size] = iterator->children[this->maxchildren-1];
            iterator->children[this->maxchildren-1] = nullptr;

            delete[] itemCopy;

            T parentItem = newNode->data[0];
            if (iterator->parent == nullptr)
            {
                nfbpt::node<T>* newParent = new nfbpt::node<T>(this->maxchildren);
                iterator->parent = newParent;
                newNode->parent = newParent;

                newParent->data[0] = parentItem;
                newParent->size++;

                newParent->children[0] = iterator;
                newParent->children[1] = newNode;

                this->root = newParent;
            }
            else
            {
                insertR(iterator->parent, newNode, parentItem);
            }
        }
    }        
}

/*remove section*/

template <typename T>
bool bplustree<T>::search(T key) const { return search_node(this->root, key) != nullptr; }

#endif