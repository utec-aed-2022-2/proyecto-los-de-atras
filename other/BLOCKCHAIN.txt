#pragma once
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <fstream>
#include "block.h"

class Blockchain
{
private:
    DoubleList<block*> chain;
    HashMap<std::string, nodeList<block*>*> usersHash;
    BPlusTree<transaction> allOrderByDate{
        BPlusTree<transaction>(
        23,
        [](const transaction& first, const transaction& second){ return first.date < second.date;},
        [](const transaction& first, const transaction& second){ return second.date < first.date;}
        )
    };
    BPlusTree<transaction> allOrderByNumber{
        BPlusTree<transaction>(
        23,
        [](const transaction& first, const transaction& second){ return first.number < second.number;},
        [](const transaction& first, const transaction& second){ return second.number < first.number;}
        )
    };

public:
    Blockchain() = default;
    explicit Blockchain(const std::string& usersPath, const std::string& transactionsPath) {
        std::string line;
        auto* file = new std::ifstream(usersPath);
        std::getline(*file, line, '\n');
        std::string username {}, password {};

        while ((*file) >> username >> password) {
            createUser(username, password);
        }
        file->close();

        file = new std::ifstream(transactionsPath);
        std::getline(*file, line, '\n');
        std::string from, to, date, ammount;

        while ((*file) >> from >> password >> to >> ammount >> date) {
            setTx(from, password, to, std::stof(ammount), date);
        }
        file->close();
    }

    void createUser(const std::string& username, const std::string& password);
    void viewAll();
    void viewMyBlock(const std::string& username, const std::string& password);
    void writeMyBlock(std::ostream& os, const std::string& username, const std::string& password);
    void viewMyBlockDate(const std::string& username, const std::string& password);
    void viewMyBlockAmount(const std::string& username, const std::string& password);
    void viewMinTxDate(const std::string& username, const std::string& password);
    void viewMaxTxDate(const std::string& username, const std::string& password);
    void viewMinTxAmount (const std::string& username, const std::string& password);
    void viewMaxTxAmount (const std::string& username, const std::string& password);
    bool searchTx(const std::string& username, const std::string& password, std::string to, float amount, std::string date);
    /*viewMyBlockDateRange*/
    /*viewMyBlockAmountRange*/
    void setTx(const std::string& username, const std::string& password, std::string to, float amount);
    void setTx(const std::string& username, const std::string& password, std::string to, float amount, std::string date);

    void mineCascade(const std::string& username, const std::string& password);
};

void Blockchain::createUser(const std::string& username, const std::string& password)
{
    if (chain.is_empty())
    {
        chain.push_back(new block{chain.size()});
        std::stringstream ss; ss<<username; ss<<password;
        usersHash.set(ss.str(), chain.begin());
    }
    else
    {
        chain.push_back(new block{chain.size(), chain.end()->data->hash});
        std::stringstream ss; ss<<username; ss<<password;
        usersHash.set(ss.str(), chain.end());
    }
}

void Blockchain::viewAll()
{
    auto iterator = chain.begin();
    while (iterator!=nullptr)
    {
        std::cout << *(iterator->data) << std::endl;
        iterator = iterator->next;
    }    
}

void Blockchain::writeMyBlock(std::ostream& os, const std::string& username, const std::string& password) {
    std::stringstream ss; ss<<username; ss <<password;
    usersHash.get(ss.str())->data->writeBlock(os);
}

void Blockchain::viewMyBlock(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    std::cout << *usersHash.get(ss.str())->data;
}

void Blockchain::viewMyBlockDate(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    usersHash.get(ss.str())->data->coutOrderByDate(); 
}

void Blockchain::viewMyBlockAmount(const std::string& username, const std::string& password)
{ 
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    usersHash.get(ss.str())->data->coutOrderByNumber();
}

void Blockchain::viewMinTxDate(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data->coutMinTxDate();
}

void Blockchain::viewMaxTxDate(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data->coutMaxTxDate();
}

void Blockchain::viewMinTxAmount(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data->coutMinTxNumber();
}

void Blockchain::viewMaxTxAmount(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data->coutMaxTxNumber();
}

bool Blockchain::searchTx(const std::string& username, const std::string& password, std::string to, float amount, std::string date)
{
    std::stringstream ss; ss<<username; ss<<password;
    transaction tx(username, to, amount, date);
    return usersHash.get(ss.str())->data->search(tx);
}

/*viewMyBlockDateRange*/
/*viewMyBlockAmountRange*/

void Blockchain::setTx(const std::string& username, const std::string& password, std::string to, float amount)
{   
    std::stringstream ss; ss<<username; ss<<password;
    const auto p1 = std::chrono::system_clock::now();
    std::stringstream date; date<<std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
    transaction tx(username, to, amount, date.str());

    usersHash.get(ss.str())->data->insert(tx);
    allOrderByDate.insert(tx);
    allOrderByNumber.insert(tx);
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

void Blockchain::setTx(const std::string& username, const std::string& password, std::string to, float amount, std::string date)
{   
    std::stringstream ss; ss<<username; ss<<password;
    transaction tx(username, to, amount, date);
    usersHash.get(ss.str())->data->insert(tx);
    allOrderByDate.insert(tx);
    allOrderByNumber.insert(tx);
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

void Blockchain::mineCascade(const std::string& username, const std::string& password)
{
    std::stringstream ss; ss<<username; ss<<password;
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

#endif