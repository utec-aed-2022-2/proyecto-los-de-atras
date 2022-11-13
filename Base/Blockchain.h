#pragma once
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
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
    void createUser(std::string username, std::string password);
    void viewAll();
    void viewMyBlock(std::string username, std::string password);
    void viewMyBlockDate(std::string username, std::string password);
    void viewMyBlockAmount(std::string username, std::string password);
    void viewMinTxDate(std::string username, std::string password);
    void viewMaxTxDate(std::string username, std::string password);
    void viewMinTxAmount (std::string username, std::string password);
    void viewMaxTxAmount (std::string username, std::string password);
    bool searchTx(std::string username, std::string password, std::string to, float amount, std::string date);
    /*viewMyBlockDateRange*/
    /*viewMyBlockAmountRange*/
    void setTx(std::string username, std::string password, std::string to, float amount);
    void setTx(std::string username, std::string password, std::string to, float amount, std::string date);

    void mineCascade(std::string username, std::string password);
};

void Blockchain::createUser(std::string username, std::string password)
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

void Blockchain::viewMyBlock(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    std::cout << usersHash.get(ss.str())->data;
}

void Blockchain::viewMyBlockDate(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    usersHash.get(ss.str())->data->coutOrderByDate(); 
}

void Blockchain::viewMyBlockAmount(std::string username, std::string password)
{ 
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    usersHash.get(ss.str())->data->coutOrderByNumber();
}

void Blockchain::viewMinTxDate(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data->coutMinTxDate();
}

void Blockchain::viewMaxTxDate(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data->coutMaxTxDate();
}

void Blockchain::viewMinTxAmount(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data->coutMinTxNumber();
}

void Blockchain::viewMaxTxAmount(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data->coutMaxTxNumber();
}

bool Blockchain::searchTx(std::string username, std::string password, std::string to, float amount, std::string date)
{
    std::stringstream ss; ss<<username; ss<<password;
    transaction tx(username, to, amount, date);
    return usersHash.get(ss.str())->data->search(tx);
}

/*viewMyBlockDateRange*/
/*viewMyBlockAmountRange*/

void Blockchain::setTx(std::string username, std::string password, std::string to, float amount)
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

void Blockchain::setTx(std::string username, std::string password, std::string to, float amount, std::string date)
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

void Blockchain::mineCascade(std::string username, std::string password)
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