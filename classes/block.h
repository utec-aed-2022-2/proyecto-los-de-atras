#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include <sstream>
#include "double_list.h"
#include "transaction.h"
#include "../functions/hash_functions.h"

const std::string hashGenesis = "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefaul = -1;

struct block
{
    std::uint64_t id;
    std::uint64_t nonce;
    double_list<transaction> data;
    std::string prevHash{hashGenesis};
    std::string hash;

    block() = default;
    ~block() { this->data.clear(); }
    block(uint64_t id, std::string prevHash = hashGenesis): id(id), prevHash(prevHash)
    {
        nonce = nonceDefaul;
        hash = calculateHash();
    }
    block(const block &other): id(other.id), nonce(other.nonce), data(other.data), prevHash(other.prevHash), hash(other.hash) {}
    block& operator=(const block &other);

    friend std::ostream& operator<<(std::ostream& os, block& blck)
    {
        os << blck.id << std::endl;
        os << blck.nonce << std::endl;
        for (int i = 0; i < blck.data.size(); i++)
        {
            os << blck.data[i] << std::endl;
        }
        os << blck.prevHash << std::endl;
        os << blck.hash << std::endl;
        return os;
    }
    bool operator==(block const& other) { return id == other.id && nonce == other.nonce && prevHash == other.prevHash && hash == other.hash; }
    bool operator!=(block const& other) { return !(*this == other); }

    uint64_t GetIndex() const { return id; }
    uint64_t GetNonce() const { return nonce; }
    double_list<transaction> GetData() const { return data; }
    std::string GetHash() const { return hash; }
    void mine();
    std::string calculateHash ();
};

block& block::operator=(const block &other)
{
    if(&other== this) { return *this; }
    this->id = other.id;
    this->nonce = other.nonce;
    this->data = other.data;
    this->prevHash = other.prevHash;
    this->hash = other.hash;
    return *this;
}

std::string block::calculateHash()
{
    std::stringstream ss;
    for (int i = 0; i < data.size() ; i++)
    {
        ss << data[i];
    }
    ss << id << nonce << prevHash;
    return sha256(ss.str());
}

void block::mine()
{
    if (hash.substr(0, 4) != "0000")
    {
        std::string str = "0000";
        do
        {
            nonce++;
            hash = calculateHash();
        } while (str.compare(hash.substr(0, 4)));
    }
}

#endif