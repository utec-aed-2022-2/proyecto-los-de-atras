#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <chrono>
#include <fstream>
#include "block.h"

class BlockChain
{
private:
    DoubleList<block> chain;
    HashMap<std::string, nodeList<block>*> usersHash;
    BPlusTree<transactionOverload<transaction, std::string>> allOrderByDate; // admi
    BPlusTree<transactionOverload<transaction, float>> allOrderByNumber; // admi

public:
    BlockChain() = default;
    explicit BlockChain(const std::string &path, char delimiter=',') { // construye los usuarios en el path
        std::ifstream file(path);
        std::string line;
        std::getline(file, line);
        std::cout << line << std::endl;

        while (getline(file, line)) {
            std::stringstream stream(line);
            std::string username;
            std::string password;
            std::getline(stream, username, delimiter);
            std::getline(stream, password, delimiter);
            this->createUser(username, password);
        }
    }

    void createUser(std::string username, std::string password);
    void viewAll();
    void viewMyBlock(std::string username, std::string password);
    void viewMyBlockDate(std::string username, std::string password);
    void viewMyBlockAmount(std::string username, std::string password);
    void minTxDate(std::string username, std::string password);
    void maxTxDate(std::string username, std::string password);
    void minTxAmount(std::string username, std::string password);
    void maxTxAmount(std::string username, std::string password);
    bool searchTx(std::string username, std::string password, std::string to, float amount, std::string date);
    /*viewMyBlockDateRange*/
    /*viewMyBlockAmountRange*/
    void setTx(std::string username, std::string password, std::string to, float amount);
    void setTx(std::string username, std::string password, std::string to, float amount, std::string date);
};

void BlockChain::createUser(std::string username, std::string password)
{
    if (chain.is_empty())
    {
        chain.push_back(chain.size());
        std::stringstream ss; ss<<username; ss<<password;
        usersHash.set(ss.str(), chain.begin());
    }
    else
    {
        chain.push_back({chain.size(), chain.end()->data.hash});
        std::stringstream ss; ss<<username; ss<<password;
        usersHash.set(ss.str(), chain.end());
    }
}

void BlockChain::viewAll()
{
    auto iterator = chain.begin();
    while (iterator!=nullptr)
    {
        std::cout << iterator->data << std::endl;
        iterator = iterator->next;
    }    
}

void BlockChain::viewMyBlock(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    std::cout << usersHash.get(ss.str())->data;
}

void BlockChain::viewMyBlockDate(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    usersHash.get(ss.str())->data.coutOrderByDate();
}

void BlockChain::viewMyBlockAmount(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    usersHash.get(ss.str())->data.coutOrderByNumber();
}

void BlockChain::minTxDate(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data.orderByDate.min();
}

void BlockChain::maxTxDate(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data.orderByDate.max();
}

void BlockChain::minTxAmount(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data.orderByNumber.min();
}

void BlockChain::maxTxAmount(std::string username, std::string password)
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data.orderByNumber.max();
}

bool BlockChain::searchTx(std::string username, std::string password, std::string to, float amount, std::string date)
{
    std::stringstream ss; ss<<username; ss<<password;
    transaction tx(username, to, amount, date);
    return usersHash.get(ss.str())->data.search(tx);
}

/*viewMyBlockDateRange*/
/*viewMyBlockAmountRange*/

void BlockChain::setTx(std::string username, std::string password, std::string to, float amount)
{   
    std::stringstream ss; ss<<username; ss<<password;
    const auto p1 = std::chrono::system_clock::now();
    std::stringstream date; date<<std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
    transaction tx(username, to, amount, date.str());
    usersHash.get(ss.str())->data.insert(tx);
    allOrderByDate.insert(&tx);
    allOrderByNumber.insert(&tx);
    usersHash.get(ss.str())->data.hash = usersHash.get(ss.str())->data.calculateHash();

    auto iterator = usersHash.get(ss.str());
    iterator = iterator->next;
    while (iterator!=nullptr)
    {
        iterator->data.prevHash = iterator->prev->data.hash;
        iterator->data.hash = iterator->data.calculateHash();
        iterator = iterator->next;
    }
}

void BlockChain::setTx(std::string username, std::string password, std::string to, float amount, std::string date)
{   
    std::stringstream ss; ss<<username; ss<<password;
    transaction tx(username, to, amount, date);
    usersHash.get(ss.str())->data.insert(tx);
    allOrderByDate.insert(&tx);
    allOrderByNumber.insert(&tx);
    usersHash.get(ss.str())->data.hash = usersHash.get(ss.str())->data.calculateHash();

    auto iterator = usersHash.get(ss.str());
    iterator = iterator->next;
    while (iterator!=nullptr)
    {
        iterator->data.prevHash = iterator->prev->data.hash;
        iterator->data.hash = iterator->data.calculateHash();
        iterator = iterator->next;
    }
}

#endif