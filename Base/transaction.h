#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <type_traits>
#include <chrono>
#include "../Functions/utd.h"
#include "../Functions/stoli.h"

struct transaction
{
    std::string string1;
    std::string string2;
    float number;
    std::string date;

    transaction() = default;
    ~transaction() = default;
    transaction(const std::string& string1, const std::string& string2, const float& number, const std::string& date);
    transaction(const transaction &other);

    transaction& operator=(const transaction &other);
    friend std::ostream& operator<<(std::ostream& os, transaction& tx);
    bool operator==(transaction const& other);
    bool operator!=(transaction const& other);
    std::string GetString1() const;
    std::string GetString2() const;
    float GetNumber() const;
    std::string GetDate() const;
};

transaction::transaction(const std::string& string1, const std::string& string2, const float& number, const std::string& date)
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

std::ostream& operator<<(std::ostream& os, transaction& tx)
{
    os << "(" << tx.string1 << " , " << tx.string2 << ", " << tx.number << ", " << unixTimeToHumanReadable(stoli(tx.date)) << ")";
    return os;
}

bool transaction::operator==(transaction const& other) { return string1 == other.string1 && string2 == other.string2 && number == other.number && date == other.date; }

bool transaction::operator!=(transaction const& other) { return !(*this == other); }

std::string transaction::GetString1() const { return string1; }

std::string transaction::GetString2() const { return string2; }

float transaction::GetNumber() const { return number; }

std::string transaction::GetDate() const { return date; }

#endif