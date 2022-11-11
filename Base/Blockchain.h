#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "block.h"

class Blockchain
{
private:
    DoubleList<block> chain;
    HashMap<std::string, nodeList<block>*> usersHash;
    BPlusTree<transaction> allOrderByDate{ // admi
        BPlusTree<transaction>(
        7, 
        [](const transaction& first, const transaction& second){ return first.date < second.date;},
        [](const transaction& first, const transaction& second){ return second.date < first.date;}
        )
    };
    BPlusTree<transaction> allOrderByNumber{ // admi
        BPlusTree<transaction>(
        7, 
        [](const transaction& first, const transaction& second){ return first.number < second.number;},
        [](const transaction& first, const transaction& second){ return second.number < first.number;}
        )
    };

public:
    Blockchain() = default;
    void createUser(std::string username, std::string password); // O(1)
    void viewAll(); // O(n)
    void viewMyBlock(std::string username, std::string password); // O(1)
    void viewMyBlockDate(std::string username, std::string password); // O(n)
    void viewMyBlockAmount(std::string username, std::string password); // O(n)
    void minTxDate(std::string username, std::string password); // O(log(n))
    void maxTxDate(std::string username, std::string password); // O(log(n))
    void minTxAmount(std::string username, std::string password); // O(log(n))
    void maxTxAmount(std::string username, std::string password); // O(log(n))
    bool searchTx(std::string username, std::string password, std::string to, float amount, std::string date); // O(1)
    /*viewMyBlockDateRange*/
    /*viewMyBlockAmountRange*/
    void setTx(std::string username, std::string password, std::string to, float amount);
    void setTx(std::string username, std::string password, std::string to, float amount, std::string date);
};

void Blockchain::createUser(std::string username, std::string password) // O(1)
{
    if (chain.is_empty())
    {
        chain.push_back(chain.size()); // O(1)
        std::stringstream ss; ss<<username; ss<<password;
        usersHash.set(ss.str(), chain.begin()); // O(1)
    }
    else
    {
        chain.push_back({chain.size(), chain.end()->data.hash}); // O(1)
        std::stringstream ss; ss<<username; ss<<password;
        usersHash.set(ss.str(), chain.end()); // O(1)
    }
}

void Blockchain::viewAll() // O(n)
{
    auto iterator = chain.begin();
    while (iterator!=nullptr)
    {
        std::cout << iterator->data << std::endl;
        iterator = iterator->next;
    }    
}

void Blockchain::viewMyBlock(std::string username, std::string password) // O(1)
{
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    std::cout << usersHash.get(ss.str())->data; // O(1)
}

void Blockchain::viewMyBlockDate(std::string username, std::string password) // O(n)
{
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    usersHash.get(ss.str())->data.coutOrderByDate();  // O(n)
}

void Blockchain::viewMyBlockAmount(std::string username, std::string password) // O(n)
{
    std::stringstream ss; ss<<username; ss<<password;
    std::cout << "username[ " << username << " ]" << std::endl;
    usersHash.get(ss.str())->data.coutOrderByNumber(); // O(n)
}

void Blockchain::minTxDate(std::string username, std::string password) // O(log(n))
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data.orderByDate.min(); // O(log(n))
}

void Blockchain::maxTxDate(std::string username, std::string password) // O(log(n))
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data.orderByDate.max(); // O(log(n))
}

void Blockchain::minTxAmount(std::string username, std::string password) // O(log(n))
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data.orderByNumber.min(); // O(log(n))
}

void Blockchain::maxTxAmount(std::string username, std::string password) // O(log(n))
{
    std::stringstream ss; ss<<username; ss<<password;
    usersHash.get(ss.str())->data.orderByNumber.max(); // O(log(n))
}

bool Blockchain::searchTx(std::string username, std::string password, std::string to, float amount, std::string date) // O(1)
{
    std::stringstream ss; ss<<username; ss<<password;
    transaction tx(username, to, amount, date);
    return usersHash.get(ss.str())->data.search(tx); // O(1)
}

/*viewMyBlockDateRange*/
/*viewMyBlockAmountRange*/

void Blockchain::setTx(std::string username, std::string password, std::string to, float amount)
{   
    std::stringstream ss; ss<<username; ss<<password;
    const auto p1 = std::chrono::system_clock::now();
    std::stringstream date; date<<std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
    transaction tx(username, to, amount, date.str());
    usersHash.get(ss.str())->data.insert(tx);
    allOrderByDate.insert(tx);
    allOrderByNumber.insert(tx);
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

void Blockchain::setTx(std::string username, std::string password, std::string to, float amount, std::string date)
{   
    std::stringstream ss; ss<<username; ss<<password;
    transaction tx(username, to, amount, date);
    usersHash.get(ss.str())->data.insert(tx);
    allOrderByDate.insert(tx);
    allOrderByNumber.insert(tx);
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