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

    nfbpt::node<T>* GetRoot() const { return this->root; }

    bool search(T key) { return BPlusTreeSearch(this->root, key) != nullptr; }

    void insert(T key)
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
            nfbpt::node<T>* iterator = node;
            
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
                for (int i = 0; i < iterator->size; i++) { itemCopy[i] = iterator->item[i]; }
                itemCopy = item_insert(itemCopy, key, iterator->size);

                iterator->size = (this->maxchildren)/2;
                if ((this->maxchildren) % 2 == 0) { newNode->size = (this->maxchildren) / 2; }
                else { newNode->size = (this->maxchildren) / 2 + 1; }
                for (int i = 0; i < iterator->size; i++){ iterator->item[i] = itemCopy[i]; }
                for (int i = 0; i < newNode->size; i++){ newNode->item[i] = itemCopy[iterator->size + i]; }

                iterator->children[iterator->size] = newNode;
                newNode->children[newNode->size] = iterator->children[this->maxchildren-1];
                iterator->children[this->maxchildren-1] = nullptr;

                delete[] item_copy;

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
                    parent_insert_R(iterator->parent, newNode, parentItem);
                }
            }
        }        
    }

    void remove(T key);

private:
    void clear(nfbpt::node<T>* node)
    {
        if (node != nullptr)
        {
            if (!node->is_leaf) { for (int i = 0; i <= node->size; i++) { clear(node->children[i]); } }
            delete[] node->data;
            delete[] node->children;
            delete node;
        }
    }

    nfbpt::node<T>* find_node(nfbpt::node<T>* node, T key) const
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
            for (int i = 0; i < iterator->size; i++) { if (iterator->data[i] == key) { return iterator; } }

            return nullptr;
        }
    }

    int find_index(T* arr, T key, int len) const
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

    T* item_insert(T* arr, T key, std::size_t len)
    {
        int index = 0;
        for (int i = 0; i < len; i++)
        {
            if (key < arr[i])
            {
                index = i;
                break;
            }
            if (i==len-1)
            {
                index = len;
                break;
            }
        }
        for(int i = len; i > index; i--)
        {
            arr[i] = arr[i-1];
        }
        arr[index] = key;

        return arr;
    }

    nfbpt::node<T>** child_insert(nfbpt::node<T>** childArr, nfbpt::node<T>*child, std::size_t len, int index)
    {
        for (int i = len; i > index; i--) { childArr[i] = childArr[i - 1]; }
        childArr[index] = child;
        return childArr;
    }

    nfbpt::node<T>* child_item_insert(nfbpt::node<T>* node, nfbpt::node<T>* child, T key)
    {
        int itemIndex, childIndex;
        itemIndex = childIndex = 0;

        for (int i = 0; i < node->size; i++)
        {
            if (key < node->item[i])
            {
                itemIndex = i;
                childIndex = i+1;
                break;
            }
            if (i == node->size-1)
            {
                itemIndex = node->size;
                childIndex = node->size+1;
                break;
            }
        }
        for(int i = node->size; i > itemIndex; i--){ node->item[i] = node->item[i-1]; }
        for(int i = node->size+1; i > childIndex; i--){ node->children[i] = node->children[i-1]; }

        node->item[itemIndex] = key;
        node->children[childIndex] = child;

        return node;
    }

    void parent_insert_R(nfbpt::node<T>* node, nfbpt::node<T>* child, T key)
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

            T* item_copy = new T[iterator->size+1];
            for (int i = 0; i < iterator->size; i++) { item_copy[i] = iterator->data[i]; }
            item_copy = item_insert(item_copy, key, iterator->size);

            nfbpt::node<T>** child_copy = new nfbpt::node<T>*[iterator->size+2];
            for (int i = 0; i < iterator->size+1; i++) { child_copy[i] = iterator->children[i]; }
            child_copy[iterator->size+1] = nullptr;
            child_copy = child_insert(child_copy, child, iterator->size+1, find_index(item_copy, key, iterator->size+1));

            iterator->size = (this->maxchildren)/2;
            if ((this->maxchildren) % 2 == 0) { newNode->size = (this->maxchildren) / 2 -1; }
            else { newNode->size = (this->maxchildren) / 2; }
            for (int i = 0; i < iterator->size; i++)
            {
                iterator->data[i] = item_copy[i];
                iterator->children[i] = child_copy[i];
            }
            iterator->children[iterator->size] = child_copy[iterator->size];

            for (int i = 0; i < newNode->size; i++)
            {
                newNode->data[i] = item_copy[iterator->size+i+1];
                newNode->children[i] = child_copy[iterator->size+i+1];
                newNode->children[i]->parent = newNode;
            }
            newNode->children[newNode->size] = child_copy[iterator->size+newNode->size+1];
            newNode->children[newNode->size]->parent = newNode;

            T parentItem = item_copy[this->maxchildren/2];
            delete[] item_copy;
            delete[] child_copy;
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
                parent_insert_R(iterator->parent, newNode, parentItem);
            }
        }
    }
};

#endif