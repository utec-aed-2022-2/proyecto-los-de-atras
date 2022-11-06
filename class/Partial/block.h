#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include "transaction.h"
#include "../doubleList.h"
#include "../../function/hashFunctions.h"

const std::string hashGenesis = "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefaul = -1;

struct block
{
    std::uint64_t id;
    std::uint64_t nonce;
    doubleList<transaction> data;
    std::string prevHash{hashGenesis};
    std::string hash;

    block() = default;
    ~block();
    block(uint64_t id, std::string prevHash = hashGenesis);
    block(const block &other);

    block& operator=(const block &other);
    friend std::ostream& operator<<(std::ostream& os, block& b);
    bool operator==(block const& other);
    bool operator!=(block const& other);
    uint64_t GetIndex() const;
    uint64_t GetNonce() const;
    doubleList<transaction> GetData() const;
    std::string GetHash() const;
    void mine();
    std::string calculateHash ();
};

block::~block() { this->data.clear(); }

block::block(uint64_t id, std::string prevHash)
{
    this->id = id;
    this->nonce = nonceDefaul;
    this->prevHash = prevHash;
    this->hash = calculateHash();
}

block::block(const block &other)
{
    this->id = other.id;
    this->nonce = other.nonce;
    this->data = other.data;
    this->prevHash = other.prevHash;
    this->hash = other.hash;
}

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

std::ostream& operator<<(std::ostream& os, block& b)
{
    os << b.id << std::endl;
    os << b.nonce << std::endl;
    for (int i = 0; i < b.data.size(); i++)
    {
        os << b.data[i] << std::endl;
    }
    os << b.prevHash << std::endl;
    os << b.hash << std::endl;
    return os;
}

bool block::operator==(block const& other) { return id == other.id && nonce == other.nonce && prevHash == other.prevHash && hash == other.hash; }

bool block::operator!=(block const& other) { return !(*this == other); }

uint64_t block::GetIndex() const { return id; }

uint64_t block::GetNonce() const { return nonce; }

doubleList<transaction> block::GetData() const { return data; }

std::string block::GetHash() const { return hash; }

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

#endif