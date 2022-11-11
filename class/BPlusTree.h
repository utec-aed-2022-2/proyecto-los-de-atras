#pragma once
#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include "nodes.h"

template <typename T>
class BPlusTree
{
private:
    nodeBPlus<T>* root;
    size_t maxchildren;
    std::function<bool(const T&, const T&)> less;
    std::function<bool(const T&, const T&)> greater;

public:
    BPlusTree();
    ~BPlusTree();
    BPlusTree(size_t maxchildren, std::function<bool(const T&, const T&)> less, std::function<bool(const T&, const T&)> greater);

    nodeBPlus<T>* GetRoot() const;
    void insert(const T& key);
    /*remove section*/
    bool search(const T& key);

    void min() const;
    void max() const;

private:
    int find_index(T* arr, const T& key, size_t len) const;
    nodeBPlus<T>* find_node(nodeBPlus<T>* node, const T& key) const;
    T* item_insert(T* arr, const T& key, size_t len);
    nodeBPlus<T>** child_insert(nodeBPlus<T>** childArr, nodeBPlus<T>*child, size_t len, int index);
    nodeBPlus<T>* child_item_insert(nodeBPlus<T>* node, nodeBPlus<T>* child, const T& key);
    void insertR(nodeBPlus<T>* node, nodeBPlus<T>* child, const T& key);
    /*remove section*/
    nodeBPlus<T>* search_node(nodeBPlus<T>* node, const T& key);
    void clear(nodeBPlus<T>* node);
};

template <typename T>
BPlusTree<T>::~BPlusTree() { clear(this->root); }

template <typename T>
BPlusTree<T>::BPlusTree()
{
    this->maxchildren = 5;
    this->root = nullptr;
    this->less = [](const T& first, const T& second) { return first < second; };
    this->greater = [](const T& first, const T& second) { return second < first; };
}

template <typename T>
BPlusTree<T>::BPlusTree(size_t maxchildren, std::function<bool(const T&, const T&)> less, std::function<bool(const T&, const T&)> greater)
{
    this->maxchildren = maxchildren;
    this->root = nullptr;
    this->less = less;
    this->greater = greater;
}

template <typename T>
int BPlusTree<T>::find_index(T* arr, const T& key, size_t len) const
{
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        if (less(key, arr[i])/*key < arr[i]*/)
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
nodeBPlus<T>* BPlusTree<T>::find_node(nodeBPlus<T>* node, const T& key) const
{
    if (node == nullptr) { return nullptr; }
    else
    {
        nodeBPlus<T>* iterator = node;
        while (!iterator->is_leaf)
        {
            for (int i = 0; i < iterator->size; i++)
            {
                if (less(key, iterator->data[i])/*key < iterator->data[i]*/)
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
T* BPlusTree<T>::item_insert(T* arr, const T& key, size_t len)
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
nodeBPlus<T>** BPlusTree<T>::child_insert(nodeBPlus<T>** childArr, nodeBPlus<T>*child, size_t len, int index)
{
    for (int i = len; i > index; i--) { childArr[i] = childArr[i - 1]; }
    childArr[index] = child;
    return childArr;
}

template <typename T>
nodeBPlus<T>* BPlusTree<T>::child_item_insert(nodeBPlus<T>* node, nodeBPlus<T>* child, const T& key)
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
void BPlusTree<T>::insertR(nodeBPlus<T>* node, nodeBPlus<T>* child, const T& key)
{
    nodeBPlus<T>* iterator = node;
    if (iterator->size < this->maxchildren-1)
    {
        iterator = child_item_insert(iterator,child, key);
        iterator->size++;
    }
    else
    {
        nodeBPlus<T>* newNode = new nodeBPlus<T>(this->maxchildren);
        newNode->parent = iterator->parent;

        T* itemCopy = new T[iterator->size+1];
        for (int i = 0; i < iterator->size; i++) { itemCopy[i] = iterator->data[i]; }
        itemCopy = item_insert(itemCopy, key, iterator->size);

        nodeBPlus<T>** childCopy = new nodeBPlus<T>*[iterator->size+2];
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
            nodeBPlus<T>* newParent = new nodeBPlus<T>(this->maxchildren);
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
nodeBPlus<T>* BPlusTree<T>::search_node(nodeBPlus<T>* node, const T& key)
{
    nodeBPlus<T>* iterator = find_node(node, key);
    for (int i = 0; i < iterator->size; i++) { if (iterator->data[i] == key) { return iterator; } }
    return nullptr;
}

template <typename T>
void BPlusTree<T>::clear(nodeBPlus<T>* node)
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
nodeBPlus<T>* BPlusTree<T>::GetRoot() const { return this->root; }

template <typename T>
void BPlusTree<T>::insert(const T& key)
{
    if (this->root == nullptr)
    {
        this->root = new nodeBPlus<T>(this->maxchildren);
        this->root->is_leaf = true;
        this->root->data[0] = key;
        this->root->size = 1;
    }
    else
    {
        nodeBPlus<T>* iterator = this->root;
        
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
            nodeBPlus<T>* newNode = new nodeBPlus<T>(this->maxchildren);
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
                nodeBPlus<T>* newParent = new nodeBPlus<T>(this->maxchildren);
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
void BPlusTree<T>::min() const
{
    nodeBPlus<T>* cursor = this->root;
    while (!(*cursor).is_leaf) { cursor = (*cursor).children[0]; }
    std::cout << cursor->data[0] << std::endl;
}

template <typename T>
void BPlusTree<T>::max() const
{
    nodeBPlus<T>* cursor = this->root;
    while (!(*cursor).is_leaf) { cursor = (*cursor).children[cursor->size]; }
    std::cout << cursor->data[cursor->size-1] << std::endl;
}

template <typename T>
bool BPlusTree<T>::search(const T& key) { return search_node(this->root, key) != nullptr; }

template <typename T>
void coutOrder(nodeBPlus<T>* cursor)
{
    while (!(*cursor).is_leaf) { cursor = (*cursor).children[0]; }
    for (int i = 0; i < (*cursor).size; i++) { std::cout << (*cursor).data[i] << std::endl; }
    if ((*cursor).children[(*cursor).size] != nullptr) { coutOrder((*cursor).children[(*cursor).size]); }   
}

#endif