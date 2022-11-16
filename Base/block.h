#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include "transaction.h"
#include "../function/hashFunctions.h"
#include "../class/BPlusTree.h"
#include "../class/DoubleList.h"
#include "../class/HashMap.h"
#include "../class/Heap.h"

const std::string hashGenesis = "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefaul = -1;

struct block
{
    std::uint64_t id {};
    std::uint64_t nonce {};
    DoubleList<transaction> data;
    HashMap<std::string, transaction*> dataHash;
    BPlusTree<transaction> orderByDate{
        BPlusTree<transaction>(
        23, 
        [](const transaction& first, const transaction& second){ return first.date < second.date;},
        [](const transaction& first, const transaction& second){ return second.date < first.date;}
        )
    };
    BPlusTree<transaction> orderByNumber{
        BPlusTree<transaction>(
        23, 
        [](const transaction& first, const transaction& second){ return first.number < second.number;},
        [](const transaction& first, const transaction& second){ return second.number < first.number;}
        )
    };
    Heap<transaction> maxTxDate{
        Heap<transaction>(
        23, 
        [](const transaction& first, const transaction& second){ return first.date < second.date;},
        [](const transaction& first, const transaction& second){ return second.date < first.date;}
        )
    };
    Heap<transaction, true> minTxDate{
        Heap<transaction, true>(
        23, 
        [](const transaction& first, const transaction& second){ return first.date < second.date;},
        [](const transaction& first, const transaction& second){ return second.date < first.date;}
        )
    };
    Heap<transaction> maxTxNumber{
        Heap<transaction>(
        23, 
        [](const transaction& first, const transaction& second){ return first.number < second.number;},
        [](const transaction& first, const transaction& second){ return second.number < first.number;}
        )
    };
    Heap<transaction, true> minTxNumber{
        Heap<transaction, true>(
        23, 
        [](const transaction& first, const transaction& second){ return first.number < second.number;},
        [](const transaction& first, const transaction& second){ return second.number < first.number;}
        )
    };
    std::string prevHash;
    std::string hash;

    block() = default;
    ~block() = default;
    block(uint64_t id, std::string prevHash = hashGenesis);
    block(const block &other);
    block& operator=(const block &other);
    void insert(transaction tx);
    void writeBlock(std::ostream& os);
    /*remove section*/
    bool search(transaction tx);
    void coutOrderByDate() const;
    void coutOrderByNumber() const;
    void coutMaxTxDate() const;
    void coutMinTxDate() const;
    void coutMaxTxNumber() const;
    void coutMinTxNumber() const;
    void mine();
    std::string calculateHash ();
    bool operator==(block const& other);
    bool operator!=(block const& other);
    friend std::ostream& operator<<(std::ostream& os, const block& b);
};

block::block(uint64_t id, std::string prevHash)
{
    this->id = id;
    this->nonce = nonceDefaul;
    this->prevHash = prevHash;
    this->hash = calculateHash();
    this->mine();
}

block::block(const block &other)
{
    this->id = other.id;
    this->nonce = other.nonce;
    this->data = other.data;
    this->dataHash = other.dataHash;
    this->orderByDate = other.orderByDate;
    this->orderByNumber = other.orderByNumber;
    this->maxTxDate = other.maxTxDate;
    this->minTxDate = other.minTxDate;
    this->maxTxNumber = other.maxTxNumber;
    this->minTxNumber = other.minTxNumber;
    this->prevHash = other.prevHash;
    this->hash = other.hash;
}

block& block::operator=(const block &other)
{
    if(&other== this) { return *this; }
    this->id = other.id;
    this->nonce = other.nonce;
    this->data = other.data;
    this->dataHash = other.dataHash;
    this->orderByDate = other.orderByDate;
    this->orderByNumber = other.orderByNumber;
    this->maxTxDate = other.maxTxDate;
    this->minTxDate = other.minTxDate;
    this->maxTxNumber = other.maxTxNumber;
    this->minTxNumber = other.minTxNumber;
    this->prevHash = other.prevHash;
    this->hash = other.hash;
    return *this;
}

void block::insert(transaction tx)
{
    std::stringstream ss; ss << tx;
    data.push_back(tx);
    dataHash.set(ss.str(), &data.end()->data);
    orderByDate.insert(data.end()->data);
    orderByNumber.insert(data.end()->data);
    maxTxDate.push(data.end()->data);
    minTxDate.push(data.end()->data);
    maxTxNumber.push(data.end()->data);
    minTxNumber.push(data.end()->data);
    this->hash = this->calculateHash();
}

/*remove section*/

bool block::search(const transaction tx)
{
    std::stringstream ss; ss << tx;
    dataHash.get(ss.str());
    return true;
}

void block::coutOrderByDate() const
{
    std::cout << "my transactions(ordered by date): " << std::endl;
    coutOrder(this->orderByDate.GetRoot());
}

void block::coutOrderByNumber() const
{
    std::cout << "my transactions(ordered by amount): " << std::endl;
    coutOrder(this->orderByNumber.GetRoot());
}

void block::coutMaxTxDate() const
{
    std::cout << "my max transactions(by date): ";
    std::cout << this->maxTxDate.top() << std::endl;
}

void block::coutMinTxDate() const
{
    std::cout << "my min transactions(by date): ";
    std::cout << this->minTxDate.top() << std::endl;
}

void block::coutMaxTxNumber() const
{
    std::cout << "my max transactions(by amount): ";
    std::cout << this->maxTxNumber.top() << std::endl;
}

void block::coutMinTxNumber() const
{
    std::cout << "my min transactions(by amount): ";
    std::cout << this->minTxNumber.top() << std::endl;
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

bool block::operator==(block const& other) { return id == other.id && nonce == other.nonce && prevHash == other.prevHash && hash == other.hash; }

bool block::operator!=(block const& other) { return !(*this == other); }

std::ostream& operator<<(std::ostream& os, const block& b)
{
    os << "[ " << b.id << " ] [ " << b.nonce << " ]" << std::endl;
    os << "my transactions:" << std::endl;
    for (int i = 0; i < b.data.size(); i++) { os << b.data[i] << std::endl; }
    os << "prev: " << b.prevHash << std::endl;
    os << "current: " << b.hash << std::endl;
    return os;
}

void block::writeBlock(std::ostream& os) {
    for (int i = 0; i < data.size(); i++) {
        data[i].writeTransaccion(os);
        os << std::endl;
    }
}

#endif