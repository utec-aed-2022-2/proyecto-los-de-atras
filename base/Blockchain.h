#pragma once
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "block.h"

class Blockchain
{
private:
    DoubleList<block*> chain;
    Hash<std::string, nl::node<block*>*> usersHash;
    BPlusTree<transaction*> allOrderByDate{
            BPlusTree<transaction*>(
                    23,
                    [](const transaction* first, const transaction* second){ return first->date < second->date;},
                    [](const transaction* first, const transaction* second){ return second->date < first->date;},
                    [](const transaction* first, const transaction* second){ return second->date == first->date;}
            )
    };
    BPlusTree<transaction*> allOrderByAmount{
            BPlusTree<transaction*>(
                    23,
                    [](const transaction* first, const transaction* second){ return first->amount < second->amount;},
                    [](const transaction* first, const transaction* second){ return second->amount < first->amount;},
                    [](const transaction* first, const transaction* second){ return second->amount == first->amount;}
            )
    };

public:
    Blockchain() = default;
    ~Blockchain() = default;

    void createUser(const std::string& username, const std::string& password);
    block* myBlock(const std::string& username, const std::string& password);
    DoubleList<transaction*> myTxsDate(const std::string& username, const std::string& password);
    DoubleList<transaction*> myTxsAmount(const std::string& username, const std::string& password);
    DoubleList<transaction*> myTxsDateRange(const std::string& username, const std::string& password, const std::string& start, const std::string& end);
    DoubleList<transaction*> myTxsAmountRange(const std::string& username, const std::string& password, float start, float end);
    DoubleList<transaction*> myMaxTxD(const std::string& username, const std::string& password);
    DoubleList<transaction*> myMinTxD(const std::string& username, const std::string& password);
    DoubleList<transaction*> myMaxTxA(const std::string& username, const std::string& password);
    DoubleList<transaction*> myMinTxA(const std::string& username, const std::string& password);
    void setTx(const std::string& username, const std::string& password, const std::string& to, float amount);
    void setTx(const std::string& username, const std::string& password, const std::string& to, float amount, const std::string& date);
    bool searchUser(const std::string& username, const std::string& password);
    bool searchTx(const std::string& username, const std::string& password, const std::string& to, float amount, const std::string& date);

    void mineCascade(const std::string& username, const std::string& password);
    friend std::ostream& operator<<(std::ostream& os, const Blockchain& tx);
};

void Blockchain::createUser(const std::string& username, const std::string& password)
{
    if (chain.is_empty())
    {
        chain.push_back(new block{chain.SIZE()});
        std::stringstream ss; ss << username; ss << password;
        usersHash.set(ss.str(), chain.begin());
    }
    else
    {
        chain.push_back(new block{chain.SIZE(), chain.end()->data->hash});
        std::stringstream ss; ss << username; ss << password;
        usersHash.set(ss.str(), chain.end());
    }
}

block* Blockchain::myBlock(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss << username; ss << password;
    return usersHash.get(ss.str())->data;
}

DoubleList<transaction*> Blockchain::myTxsDate(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss<<username; ss<<password;
    return usersHash.get(ss.str())->data->ObyDtoList();
}

DoubleList<transaction*> Blockchain::myTxsAmount(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss<<username; ss<<password;
    return usersHash.get(ss.str())->data->ObyAtoList();
}

DoubleList<transaction*> Blockchain::myTxsDateRange(const std::string& username, const std::string& password, const std::string& start, const std::string& end)
{
    std::stringstream ss; ss<<username; ss<<password;
    return usersHash.get(ss.str())->data->orderByDate.makeListRange(new transaction{"", "", 0, start}, new transaction{"", "", 0, end});
}

DoubleList<transaction*> Blockchain::myTxsAmountRange(const std::string& username, const std::string& password, float start, float end)
{
    std::stringstream ss; ss<<username; ss<<password;
    return usersHash.get(ss.str())->data->orderByAmount.makeListRange(new transaction{"", "", start, ""}, new transaction{"", "", end, ""});
}

DoubleList<transaction*> Blockchain::myMaxTxD(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss << username; ss << password;
    return usersHash.get(ss.str())->data->maxTxD();
}

DoubleList<transaction*> Blockchain::myMinTxD(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss << username; ss << password;
    return usersHash.get(ss.str())->data->minTxD();
}

DoubleList<transaction*> Blockchain::myMaxTxA(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss << username; ss << password;
    return usersHash.get(ss.str())->data->maxTxA();
}

DoubleList<transaction*> Blockchain::myMinTxA(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss << username; ss << password;
    return usersHash.get(ss.str())->data->minTxA();
}

void Blockchain::setTx(const std::string& username, const std::string& password, const std::string& to, float amount)
{
    std::stringstream ss; ss << username; ss << password;
    const auto p1 = std::chrono::system_clock::now();
    std::stringstream date; date<<std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
    transaction* tx = new transaction(username, to, amount, date.str());

    usersHash.get(ss.str())->data->insert(tx);
    allOrderByDate.insert(tx);
    allOrderByAmount.insert(tx);
    usersHash.get(ss.str())->data->hash = usersHash.get(ss.str())->data->calculateHash();

    auto iterator = usersHash.get(ss.str());
    iterator = iterator->next;
    while (iterator!=nullptr)
    {
        iterator->data->prevHash = iterator->prev->data->hash;
        iterator->data->hash = iterator->data->calculateHash();
        iterator = iterator->next;
    }
}

void Blockchain::setTx(const std::string& username, const std::string& password, const std::string& to, float amount, const std::string& date)
{
    std::stringstream ss; ss << username; ss << password;
    transaction* tx = new transaction(username, to, amount, date);
    usersHash.get(ss.str())->data->insert(tx);
    allOrderByDate.insert(tx);
    allOrderByAmount.insert(tx);
    usersHash.get(ss.str())->data->hash = usersHash.get(ss.str())->data->calculateHash();

    auto iterator = usersHash.get(ss.str());
    iterator = iterator->next;
    while (iterator!=nullptr)
    {
        iterator->data->prevHash = iterator->prev->data->hash;
        iterator->data->hash = iterator->data->calculateHash();
        iterator = iterator->next;
    }
}

bool Blockchain::searchTx(const std::string& username, const std::string& password, const std::string& to, float amount, const std::string& date)
{
    std::stringstream ss; ss << username; ss << password;
    transaction* tx = new transaction(username, to, amount, date);
    std::stringstream key; key << *(tx);
    return usersHash.get(ss.str())->data->dataHash.search(key.str());
}

bool Blockchain::searchUser(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss << username; ss << password;
    return usersHash.search(ss.str());
}

void Blockchain::mineCascade(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss << username; ss << password;
    usersHash.get(ss.str())->data->mine();
    auto iterator = usersHash.get(ss.str());
    iterator = iterator->next;
    while (iterator!=nullptr)
    {
        iterator->data->prevHash = iterator->prev->data->hash;
        iterator->data->hash = iterator->data->calculateHash();
        iterator = iterator->next;
    }
}

std::ostream& operator<<(std::ostream& os, const Blockchain& tx)
{
    auto iterator = tx.chain.begin();
    while (iterator!=nullptr)
    {
        os << *(iterator->data) << std::endl;
        iterator = iterator->next;
    }
    return os;
}

#endif