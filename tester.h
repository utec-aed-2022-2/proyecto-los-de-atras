#pragma once
#ifndef TESTER_H
#define TESTER_H
#include "blockchain.h"

using std::string;
using std::cout;
using std::endl;

void test()
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

    cout << xd;
}

#endif