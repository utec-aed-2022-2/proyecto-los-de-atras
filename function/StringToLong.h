#pragma once
#ifndef STRINGTOLONG_H
#define STRINGTOLONG_H
#include <iostream>
#include <cstring>
#include <string>
#include <math.h>

long int stoli(const std::string &__str)
{
    long int returnn = 0;
    for (int i = 0; i < __str.size(); i++) { returnn += stoi(__str.substr(i, 1)) * pow(10,9-i); }
    return returnn;
}

#endif