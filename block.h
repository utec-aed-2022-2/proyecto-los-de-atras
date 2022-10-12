#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include <sstream>
#include "hash_functions.h"

const std::string hashGenesis = "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefaul = -1;

/****************************** declaration ******************************/
struct block
{
    uint64_t id;
    uint64_t nonce;
    std::string data;
    std::string prevHash{hashGenesis};
    std::string hash;

    block() = default;

    block(uint64_t id, std::string data = "", std::string prevHash = hashGenesis): id(id), data(data), prevHash(prevHash)
    {
        nonce = nonceDefaul;
        hash = calculateHash();
    }

    friend std::ostream& operator<<(std::ostream& os, block& blck)
    {
        os << "id: " << blck.id << "\ndata: " << blck.data << "\nnonce: " << blck.nonce << "\nprevHash: " << blck.prevHash << "\nhash: " << blck.hash;
        return os;
    }
    bool operator==(block const& other) { return id == other.id && nonce == other.nonce && data == other.data && prevHash == other.prevHash && hash == other.hash; }
    bool operator!=(block const& other) { return !(*this == other); }

    uint32_t GetIndex() const { return id; }
    int64_t GetNonce() const { return nonce; }
    std::string GetData() const { return data; }
    std::string GetHash() const { return hash; }

    void mine();
    const std::string calculateHash() const;
};

/****************************** definition ******************************/
const std::string block::calculateHash() const
{
    std::stringstream ss;
    ss << id << nonce << data << prevHash;
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
