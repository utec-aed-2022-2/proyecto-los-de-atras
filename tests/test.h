#pragma once
#ifndef TEST_H
#define TEST_H
#include "../classes/blockchain.h"
#include "../functions/unixtodate.h"

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

#endif