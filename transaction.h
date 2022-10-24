#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <sstream>

struct transaction
{
    std::string string1;
    std::string string2;
    uint64_t number;
    std::string date;

    transaction() = default;

    transaction(std::string string1, std::string string2, uint64_t number, std::string date): string1(string1), string2(string2), number(number), date(date) {}

    friend std::ostream& operator<<(std::ostream& os, transaction& tx)
    {
        os << "From: " << tx.string1 << " to: " << tx.string2 << " - " << tx.number << " - " << tx.date;
        return os;
    }

    bool operator==(transaction const& other) { return string1 == other.string1 && string2 == other.string2 && number == other.number && date == other.date; }
    bool operator!=(transaction const& other) { return !(*this == other); }

    std::string GetString1() const { return string1; }
    std::string GetString2() const { return string2; }
    uint64_t GetNumber() const { return number; }
    std::string GetDate() const { return date; }
};

#endif