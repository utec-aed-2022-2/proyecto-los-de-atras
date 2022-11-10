#ifndef BLOCK_H
#define BLOCK_H
#include "transaction.h"
#include "class/BPlusTree.h"
#include "class/DoubleList.h"
#include "class/HashMap.h"
#include "function/hashFunctions.h"

const std::string hashGenesis = "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefaul = -1;

struct block
{
    std::uint64_t id;
    std::uint64_t nonce;
    DoubleList<transaction> data;
    HashMap<std::string, transaction*> dataHash;
    BPlusTree<transactionOverload<transaction, std::string>> orderByDate;
    BPlusTree<transactionOverload<transaction, float>> orderByNumber;
    std::string prevHash{hashGenesis};
    std::string hash;

    block() = default;
    ~block() = default;
    block(uint64_t id, std::string prevHash = hashGenesis);
    block(const block &other);
    void insert(transaction tx);
    block& operator=(const block &other);
    bool operator==(block const& other);
    bool operator!=(block const& other);
    friend std::ostream& operator<<(std::ostream& os, block& b);
    
    void coutOrderByDate();
    void coutOrderByNumber();
    void mine();
    std::string calculateHash ();
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
    this->prevHash = other.prevHash;
    this->hash = other.hash;
    return *this;
}

void block::insert(transaction tx)
{
    std::stringstream ss; ss << tx;
    data.push_back(tx);
    dataHash.set(sha256(ss.str()), &tx);
    orderByDate.insert(&tx);
    orderByNumber.insert(&tx);
    this->hash = this->calculateHash();
}

bool block::operator==(block const& other) { return id == other.id && nonce == other.nonce && prevHash == other.prevHash && hash == other.hash; }

bool block::operator!=(block const& other) { return !(*this == other); }

std::ostream& operator<<(std::ostream& os, block& b)
{
    os << "[ " << b.id << " ] [ " << b.nonce << " ]" << std::endl;
    os << "my transactions:" << std::endl;
    for (int i = 0; i < b.data.size(); i++) { os << b.data[i] << std::endl; }
    os << "prev: " << b.prevHash << std::endl;
    os << "current: " << b.hash << std::endl;
    return os;
}

void block::coutOrderByDate()
{
    std::cout << "my transactions(order by date): " << std::endl;
    coutOrder(this->orderByDate.GetRoot());
}

void block::coutOrderByNumber()
{
    std::cout << "my transactions(order by amount): " << std::endl;
    coutOrder(this->orderByNumber.GetRoot());
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

#endif