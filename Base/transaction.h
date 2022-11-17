#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <type_traits>
#include <sstream>
#include <chrono>
#include "../utility/stoli.h"

struct transaction
{
    std::string string1;
    std::string string2;
    float amount;
    std::string date;

    transaction() = default;
    ~transaction() = default;
    transaction(std::string string1, std::string string2, float amount, std::string date);
    transaction(const transaction &other);
    transaction& operator=(const transaction &other);

    bool operator==(transaction const& other);
    bool operator!=(transaction const& other);
    friend std::ostream& operator<<(std::ostream& os, const transaction& tx);
};

transaction::transaction(std::string string1, std::string string2, float amount, std::string date)
{
    this->string1 = string1;
    this->string2 = string2; 
    this->amount = amount;
    this->date = date;
}

transaction::transaction(const transaction &other)
{
    this->string1 = other.string1;
    this->string2 = other.string2; 
    this->amount = other.amount;
    this->date = other.date;
}

transaction& transaction::operator=(const transaction &other)
{
    if(&other== this) { return *this; }
    this->string1 = other.string1;
    this->string2 = other.string2; 
    this->amount = other.amount;
    this->date = other.date;
    return *this;
}

bool transaction::operator==(transaction const& other) { return string1 == other.string1 && string2 == other.string2 && amount == other.amount && date == other.date; }

bool transaction::operator!=(transaction const& other) { return !(*this == other); }

std::ostream& operator<<(std::ostream& os, const transaction& tx)
{
    std::time_t unixTimestamp(std::stol(tx.date));
    std::string date = std::asctime(std::localtime(&unixTimestamp));

    os << "(" << tx.string1 << " , " << tx.string2 << ", " << tx.amount << ", " << date.substr(0, 24) << ")";
    return os;
}

#endif