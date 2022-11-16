#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <type_traits>
#include <chrono>
#include "../utility/unix.h"
#include "../utility/stoli.h"

struct transaction
{
    std::string string1;
    std::string string2;
    float number;
    std::string date;

    transaction() = default;
    ~transaction() = default;
    transaction(std::string string1, std::string string2, float number, std::string date);
    transaction(const transaction &other);
    void writeTransaccion(std::ostream& os);

    transaction& operator=(const transaction &other);
    friend std::ostream& operator<<(std::ostream& os, const transaction& tx);
    bool operator==(transaction const& other);
    bool operator!=(transaction const& other);
};

transaction::transaction(std::string string1, std::string string2, float number, std::string date)
{
    this->string1 = string1;
    this->string2 = string2; 
    this->number = number;
    this->date = date;
}

transaction::transaction(const transaction &other)
{
    this->string1 = other.string1;
    this->string2 = other.string2; 
    this->number = other.number;
    this->date = other.date;
}

transaction& transaction::operator=(const transaction &other)
{
    if(&other== this) { return *this; }
    this->string1 = other.string1;
    this->string2 = other.string2; 
    this->number = other.number;
    this->date = other.date;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const transaction& tx)
{
    std::time_t unixTimestamp(std::stol(tx.date));
    std::string date = std::asctime(std::localtime(&unixTimestamp));

    os << "(" << tx.string1 << " , " << tx.string2 << ", " << tx.number << ", " << date.substr(0, 24) << ")";
    return os;
}

void transaction::writeTransaccion(std::ostream& os) {
    os << string1 << " " << string2 << " " << number << " " << date;
}

bool transaction::operator==(transaction const& other) { return string1 == other.string1 && string2 == other.string2 && number == other.number && date == other.date; }

bool transaction::operator!=(transaction const& other) { return !(*this == other); }

#endif