#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <type_traits>
#include <chrono>
#include "../utility/unix.h"
#include "../utility/stoli.h"

struct transaction {
    std::string string1;
    std::string string2;
    float amount;
    std::string date;

    transaction() = default;

    ~transaction() = default;

    transaction(std::string string1, std::string string2, float amount, std::string date);

    transaction(const transaction &other);

    transaction &operator=(const transaction &other);

    bool operator==(transaction const &other);

    bool operator!=(transaction const &other);

    void writeTransaccion(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, const transaction &tx);
};

transaction::transaction(std::string string1, std::string string2, float amount, std::string date) {
    this->string1 = string1;
    this->string2 = string2;
    this->amount = amount;
    this->date = date;
}

transaction::transaction(const transaction &other) {
    std::cout << "copy constructor transaction " << std::endl;
    this->string1 = other.string1;
    this->string2 = other.string2;
    this->amount = other.amount;
    this->date = other.date;
}

transaction &transaction::operator=(const transaction &other) {
    std::cout << "constructing transaction from other" << std::endl;
    if (&other == this) { return *this; }
    this->string1 = other.string1;
    this->string2 = other.string2;
    this->amount = other.amount;
    this->date = other.date;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const transaction &tx) {
    std::time_t unixTimestamp(std::stol(tx.date));
    std::string date = std::asctime(std::localtime(&unixTimestamp));

    os << "(" << tx.string1 << " , " << tx.string2 << ", " << tx.amount << ", " << date.substr(0, 24) << ")";
    return os;
}

void transaction::writeTransaccion(std::ostream &os) {
    os << string1 << " " << string2 << " " << amount << " " << date;
}

bool transaction::operator==(transaction const &other) {
    return string1 == other.string1 && string2 == other.string2 && amount == other.amount && date == other.date;
}

bool transaction::operator!=(transaction const &other) { return !(*this == other); }

#endif