#pragma once
#ifndef TEST_H
#define TEST_H
#include "../classes/blockchain.h"
#include "../functions/unixtodate.h"

template <typename T>
void print(nfbpt::node<T>* cursor)
{
    // You must NOT edit this function.
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; ++i) {
            std::cout << cursor->data[i] << " ";
        }
        std::cout << "\n";

        if (!cursor->is_leaf) {
            for (int i = 0; i < cursor->size + 1; ++i) {
                print(cursor->children[i]);
            }
        }
    }
}

void test1()
{
    blockchain xd;

    xd.addBlock();
    xd.addBlock();
    xd.addBlock();
    xd.addBlock();

    xd.setData(1, {"a", "b", 100, "x"});
    xd.setData(3, {"a", "c", 200, "x"});
    xd.setData(3, {"w", "a", 300, "x"});
    xd.setData(4, {"z", "g", 5500, "x"});
    xd.setData(1, {"a", "h", 200, "x"});
    xd.setData(1, {"q", "j", 1200, "x"});

    xd.minechain(3);

    xd.setData(3, {"w", "a", 3022220, "x"});

    xd.addBlock();

    std::cout << xd;
}

void test2()
{
    
    long int T = 1653318796;

    std::string ans = unixTimeToHumanReadable(T);

    // DD:MM:YYYY:HH:MM:SS
    std::cout << ans << std::endl;
}

void test3()
{
    double_list<int> a;
    a.push_back(1);
    a.push_back(2);

    double_list<int> b = a;

    for (int i = 0; i < b.size(); i++) { std::cout << b[i] << std::endl; }
}

/*int main3(int argc, char const *argv[])
{
    blockchain xd;

    xd.addBlock();
    xd.addBlock();
    xd.addBlock();

    xd.setData(1, {"a", "b", 100, "x"});
    xd.setData(3, {"a", "c", 200, "x"});
    xd.setData(3, {"w", "a", 300, "x"});

    block** p = &xd.chain[1];
    
    std::cout << std::endl;
    std::cout << **p;
    std::cout << *xd.chain[1];

    return 0;
}


int main2(int argc, char const *argv[])
{
    double_list<int> dl;
    dl.push_back(1);
    dl.push_back(2);
    dl.push_back(3);

    int * p = &dl[1];

    *p = 9;

    std::cout << *p << std::endl;

    for (int i = 0; i < dl.size(); i++)
    {
        std::cout << dl[i] << std::endl;
    }

    return 0;
}


int main1(int argc, char const *argv[])
{
    bplustree<int> bpt1(3);
    bpt1.insert(9);
    bpt1.insert(5);
    bpt1.insert(1);
    bpt1.insert(7);
    bpt1.insert(4);
    bpt1.insert(6);
    print(bpt1.GetRoot());

    std::cout << std::endl;
    
    bplustree<std::string> bpt2(3);
    bpt2.insert("i");
    bpt2.insert("e");
    bpt2.insert("a");
    bpt2.insert("g");
    bpt2.insert("d");
    bpt2.insert("f");
    print(bpt2.GetRoot());

    return 0;
}*/

#endif