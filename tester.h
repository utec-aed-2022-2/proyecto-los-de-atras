#pragma once
#ifndef TESTER_H
#define TESTER_H
#include "blockchain.h"

void test1()
{
    blockchain xd;

    xd.addBlock();
    xd.addBlock();
    xd.addBlock();
    xd.addBlock();

    std::cout << xd;

    xd.setData(3, "Choqque Mejia, Fernando Adriano");

    std::cout << xd;

    xd.setData(4, "Castro Padilla, Juan Diego");

    std::cout << xd;
}

void test2()
{
    blockchain xd;

    xd.addBlock("Choqque Mejia, Fernando Adriano");
    xd.addBlock("Castro Padilla, Juan Diego");
    xd.addBlock("Flores Panduro, Carlos Alonso");
    xd.addBlock("Izaguirre Zavaleta, Luis Fernando");

    std::cout << xd;
}

void test3()
{
    blockchain xd;

    xd.addBlock("Choqque Mejia, Fernando Adriano");
    xd.addBlock("Castro Padilla, Juan Diego");
    xd.addBlock("Flores Panduro, Carlos Alonso");
    xd.addBlock("Izaguirre Zavaleta, Luis Fernando");

    xd.setData(2, "Raza Estrada, Gilver Alexis");

    std::cout << xd;

    xd.minechain(2);

    std::cout << xd;
}

#endif