#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include "transaction.h"
#include "../function/hashFunctions.h"
#include "../class/BPlusTree.h"
#include "../class/DoubleList.h"
#include "../class/Hash.h"
#include "../class/Heap.h"

const std::string hashGenesis = "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefault = -1;

struct block
{
    std::uint64_t id{};
    std::uint64_t nonce{};
    DoubleList<transaction*> data;
    Hash<std::string, transaction*> dataHash;
    BPlusTree<transaction*> orderByDate{
            BPlusTree<transaction*>(
                    23,
                    [](const transaction* first, const transaction* second){ return first->date < second->date;},
                    [](const transaction* first, const transaction* second){ return second->date < first->date;},
                    [](const transaction* first, const transaction* second){ return second->date == first->date;}
            )
    };
    BPlusTree<transaction*> orderByAmount{
            BPlusTree<transaction*>(
                    23,
                    [](const transaction* first, const transaction* second){ return first->amount < second->amount;},
                    [](const transaction* first, const transaction* second){ return second->amount < first->amount;},
                    [](const transaction* first, const transaction* second){ return second->amount == first->amount;}
            )
    };
    Heap<transaction*> maxTxDate{
            Heap<transaction*>(
                    23,
                    [](const transaction* first, const transaction* second){ return first->date < second->date;},
                    [](const transaction* first, const transaction* second){ return second->date < first->date;},
                    [](const transaction* first, const transaction* second){ return first->date == second->date;}
            )
    };
    Heap<transaction*, true> minTxDate{
            Heap<transaction*, true>(
                    23,
                    [](const transaction* first, const transaction* second){ return first->date < second->date;},
                    [](const transaction* first, const transaction* second){ return second->date < first->date;},
                    [](const transaction* first, const transaction* second){ return first->date == second->date;}
            )
    };
    Heap<transaction*> maxTxAmount{
            Heap<transaction*>(
                    23,
                    [](const transaction* first, const transaction* second){ return first->amount < second->amount;},
                    [](const transaction* first, const transaction* second){ return second->amount < first->amount;},
                    [](const transaction* first, const transaction* second){ return first->amount == second->amount;}
            )
    };
    Heap<transaction*, true> minTxAmount{
            Heap<transaction*, true>(
                    23,
                    [](const transaction* first, const transaction* second){ return first->amount < second->amount;},
                    [](const transaction* first, const transaction* second){ return second->amount < first->amount;},
                    [](const transaction* first, const transaction* second){ return first->amount == second->amount;}
            )
    };
    std::string prevHash;
    std::string hash;

    block() = default;
    ~block() = default;
    block(uint64_t id, std::string prevHash = hashGenesis);
    block(const block &other);
    block& operator=(const block &other);

    void insert(transaction* tx);
    bool search(transaction* tx);
    void mine();
    [[nodiscard]] std::string calculateHash() const;
    bool operator==(block const& other) const;
    bool operator!=(block const& other) const;
    friend std::ostream& operator<<(std::ostream& os, const block& b);

    DoubleList<transaction*> ObyDtoList();
    DoubleList<transaction*> ObyAtoList();
    DoubleList<transaction*> ObyDtoListRange(transaction* txStart, transaction* txEnd);
    DoubleList<transaction*> ObyAtoListRange(transaction* txStart, transaction* txEnd);
    DoubleList<transaction*> maxTxD();
    DoubleList<transaction*> minTxD();
    DoubleList<transaction*> maxTxA();
    DoubleList<transaction*> minTxA();
};

block::block(uint64_t id, std::string prevHash)
{
    this->id = id;
    this->nonce = nonceDefault;
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
    this->orderByAmount = other.orderByAmount;
    this->maxTxDate = other.maxTxDate;
    this->minTxDate = other.minTxDate;
    this->maxTxAmount = other.maxTxAmount;
    this->minTxAmount = other.minTxAmount;
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
    this->orderByAmount = other.orderByAmount;
    this->maxTxDate = other.maxTxDate;
    this->minTxDate = other.minTxDate;
    this->maxTxAmount = other.maxTxAmount;
    this->minTxAmount = other.minTxAmount;
    this->prevHash = other.prevHash;
    this->hash = other.hash;
    return *this;
}

void block::insert(transaction* tx)
{
    std::stringstream ss; ss << *(tx);
    data.push_back(tx);
    dataHash.set(ss.str(), data.end()->data);
    orderByDate.insert(data.end()->data);
    orderByAmount.insert(data.end()->data);
    maxTxDate.push(data.end()->data);
    minTxDate.push(data.end()->data);
    maxTxAmount.push(data.end()->data);
    minTxAmount.push(data.end()->data);
    this->hash = this->calculateHash();
    // std::cout << tx << std::endl;
    // std::cout << data.BACK() << std::endl;
    // std::cout << dataHash.get(ss.str()) << std::endl;
    // std::cout << maxTxDate.top() << std::endl;
    // std::cout << minTxAmount.top() << std::endl;
}

bool block::search(transaction* tx)
{
    std::stringstream ss; ss << *(tx);
    return dataHash.search(ss.str());
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

std::string block::calculateHash() const
{
    std::stringstream ss;
    for (int i = 0; i < data.SIZE() ; i++)
    {
        ss << *(data[i]);
    }
    ss << id << nonce << prevHash;
    return sha256(ss.str());
}

bool block::operator==(block const& other) const { return id == other.id && nonce == other.nonce && prevHash == other.prevHash && hash == other.hash; }

bool block::operator!=(block const& other) const { return !(*this == other); }

std::ostream& operator<<(std::ostream& os, const block& b)
{
    os << "[ " << b.id << " ] [ " << b.nonce << " ]" << std::endl;
    os << "my transactions:" << std::endl;
    for (int i = 0; i < b.data.SIZE(); i++) { os << *(b.data[i]) << std::endl; }
    os << "prev: " << b.prevHash << std::endl;
    os << "current: " << b.hash << std::endl;
    return os;
}

DoubleList<transaction*> block::ObyDtoList() { return orderByDate.makeList(); }

DoubleList<transaction*> block::ObyAtoList() { return orderByAmount.makeList(); }

DoubleList<transaction*> block::ObyDtoListRange(transaction* txStart, transaction* txEnd) { return orderByDate.makeListRange(txStart, txEnd); }

DoubleList<transaction*> block::ObyAtoListRange(transaction* txStart, transaction* txEnd) { return orderByAmount.makeListRange(txStart, txEnd); }

DoubleList<transaction*> block::maxTxD() { return maxTxDate.topRange(); }

DoubleList<transaction*> block::minTxD() { return minTxDate.topRange(); }

DoubleList<transaction*> block::maxTxA() { return maxTxAmount.topRange(); }

DoubleList<transaction*> block::minTxA() { return minTxAmount.topRange(); }

#endif