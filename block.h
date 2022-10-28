#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include <sstream>
#include "double_list.h"
#include "transaction.h"
#include "hash_functions.h"

const std::string hashGenesis = "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefaul = -1;

/****************************** declaration ******************************/
struct block
{
    uint64_t id;
    uint64_t nonce;
    //std::string data;
    double_list<transaction> data;
    std::string prevHash{hashGenesis};
    std::string hash;

    block() = default;

    block(uint64_t id, std::string prevHash = hashGenesis): id(id), prevHash(prevHash)
    {
        nonce = nonceDefaul;
        hash = calculateHash();
    }

    friend std::ostream& operator<<(std::ostream& os, block& blck)
    {
        os << blck.id << std::endl;
        os << blck.nonce << std::endl;
        for (size_t i = 0; i < blck.data.size(); i++)
        {
            os << blck.data[i] << std::endl;
        }
        os << blck.prevHash << std::endl;
        os << blck.hash << std::endl;
        return os;
    }
    // bool operator==(block const& other) { return id == other.id && nonce == other.nonce && data == other.data && prevHash == other.prevHash && hash == other.hash; }
    // bool operator!=(block const& other) { return !(*this == other); }

    uint64_t GetIndex() const { return id; }
    uint64_t GetNonce() const { return nonce; }
    double_list<transaction> GetData() const { return data; }
    std::string GetHash() const { return hash; }

    void mine();
    std::string calculateHash ();
};

/****************************** definition ******************************/
std::string block::calculateHash()
{
    std::stringstream ss;
    for (size_t i = 0; i < data.size() ; i++)
    {
        ss << data[i];
    }
    ss << id << nonce << prevHash;
    return sha256(ss.str());
}

void block::mine()
{
    if (hash.substr(0, 4) != "0000") {
        std::string str = "0000";
        do
        {
            nonce++;
            hash = calculateHash();
        } while (str.compare(hash.substr(0, 4)));
    }
}

#endif
