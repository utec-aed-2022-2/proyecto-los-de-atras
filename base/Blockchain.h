#pragma once
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <fstream>
#include <string>
#include <sstream>
#include "block.h"

class Blockchain {
private:
    DoubleList<block *> chain;
    Hash<std::string, nl::node<block *> *> usersHash;

    BPlusTree<transaction *> allOrderByDate{
            23,
            [](const transaction *first, const transaction *second) { return first->date < second->date; },
            [](const transaction *first, const transaction *second) { return second->date < first->date; },
            [](const transaction *first, const transaction *second) { return second->date == first->date; }
    };
    BPlusTree<transaction *> allOrderByAmount{
            23,
            [](const transaction *first, const transaction *second) { return first->amount < second->amount; },
            [](const transaction *first, const transaction *second) { return second->amount < first->amount; },
            [](const transaction *first, const transaction *second) { return second->amount == first->amount; }
    };

public:

    ~Blockchain() = default;

    Blockchain() = default;

    explicit Blockchain(const std::string &usersPath, const std::string &transactionsPath);

    void createUser(const std::string &username, const std::string &password);

    bool searchUser(const std::string &username, const std::string &password);

    void setTx(const std::string &username, const std::string &password, const std::string &to, float amount);

    void setTx(const std::string &username, const std::string &password, const std::string &to, float amount,
               const std::string &date);

    bool searchTx(const std::string &username, const std::string &password, const std::string &to, float amount,
                  const std::string &date);

    void myTxs(const std::string &username, const std::string &password,
               const std::string &path = "./assets/users/session.txt");

    void myTxsDate(const std::string &username, const std::string &password,
                   const std::string &path = "./assets/users/session.txt");

    void myTxsAmount(const std::string &username, const std::string &password,
                     const std::string &path = "./assets/users/session.txt");

    void myTxsDateRange(const std::string &username, const std::string &password, const std::string &start,
                        const std::string &end, const std::string &path = "./assets/users/session.txt");

    void myTxsAmountRange(const std::string &username, const std::string &password, float start, float end,
                          const std::string &path = "./assets/users/session.txt");

    void myMaxTxD(const std::string &username, const std::string &password,
                  const std::string &path = "./assets/users/session.txt");

    void myMinTxD(const std::string &username, const std::string &password,
                  const std::string &path = "./assets/users/session.txt");

    void myMaxTxA(const std::string &username, const std::string &password,
                  const std::string &path = "./assets/users/session.txt");

    void myMinTxA(const std::string &username, const std::string &password,
                  const std::string &path = "./assets/users/session.txt");

    void mineCascade(const std::string &username, const std::string &password);

    friend std::ostream &operator<<(std::ostream &os, const Blockchain &tx);

};

Blockchain::Blockchain(const std::string &usersPath, const std::string &transactionsPath) {
    std::string line;
    auto *file = new std::ifstream(usersPath);
    std::getline(*file, line, '\n');
    std::string username{}, password{};

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

void Blockchain::createUser(const std::string &username, const std::string &password) {
    if (chain.is_empty()) {
        chain.push_back(new block{chain.SIZE()});
        std::stringstream ss;
        ss << username;
        ss << password;
        usersHash.set(ss.str(), chain.begin());
    } else {
        chain.push_back(new block{chain.SIZE(), chain.end()->data->hash});
        std::stringstream ss;
        ss << username;
        ss << password;
        usersHash.set(ss.str(), chain.end());
    }
}

void Blockchain::myTxs(const std::string &username, const std::string &password, const std::string &path) {
    std::stringstream ss;
    ss << username;
    ss << password;
    DoubleList<transaction *> transactions = this->usersHash.get(ss.str())->data->data;

    std::ofstream out(path);
    for (int i = 0; i < transactions.SIZE(); ++i) {
        transaction *transaction = transactions[i];
        out << transaction->string1 << " " << transaction->string2 << " " << transaction->amount << " "
            << transaction->date << std::endl;
    }
    out.close();
}

void Blockchain::myTxsDate(const std::string &username, const std::string &password, const std::string &path) {
    std::stringstream ss;
    ss << username;
    ss << password;
    DoubleList<transaction *> transactions = usersHash.get(ss.str())->data->ObyDtoList();

    std::ofstream out(path);
    for (int i = 0; i < transactions.SIZE(); ++i) {
        transaction *transaction = transactions[i];
        out << transaction->string1 << " " << transaction->string2 << " " << transaction->amount << " "
            << transaction->date << std::endl;
    }
    out.close();
}

void Blockchain::myTxsAmount(const std::string &username, const std::string &password, const std::string &path) {
    std::stringstream ss;
    ss << username;
    ss << password;
    DoubleList<transaction *> transactions = usersHash.get(ss.str())->data->ObyAtoList();

    std::ofstream out(path);
    for (int i = 0; i < transactions.SIZE(); ++i) {
        transaction *transaction = transactions[i];
        out << transaction->string1 << " " << transaction->string2 << " " << transaction->amount << " "
            << transaction->date << std::endl;
    }
    out.close();
}

void Blockchain::myMaxTxD(const std::string &username, const std::string &password, const std::string &path) {
    std::stringstream ss;
    ss << username;
    ss << password;
    DoubleList<transaction *> transactions = usersHash.get(ss.str())->data->maxTxD();

    std::ofstream out(path);
    for (int i = 0; i < transactions.SIZE(); ++i) {
        transaction *transaction = transactions[i];
        out << transaction->string1 << " " << transaction->string2 << " " << transaction->amount << " "
            << transaction->date << std::endl;
    }
    out.close();
}

void Blockchain::myMinTxD(const std::string &username, const std::string &password, const std::string &path) {
    std::stringstream ss;
    ss << username;
    ss << password;
    DoubleList<transaction *> transactions = usersHash.get(ss.str())->data->minTxD();

    std::ofstream out(path);
    for (int i = 0; i < transactions.SIZE(); ++i) {
        transaction *transaction = transactions[i];
        out << transaction->string1 << " " << transaction->string2 << " " << transaction->amount << " "
            << transaction->date << std::endl;
    }
    out.close();
}

void Blockchain::myMaxTxA(const std::string &username, const std::string &password, const std::string &path) {
    std::stringstream ss;
    ss << username;
    ss << password;
    DoubleList<transaction *> transactions = usersHash.get(ss.str())->data->maxTxA();

    std::ofstream out(path);
    for (int i = 0; i < transactions.SIZE(); ++i) {
        transaction *transaction = transactions[i];
        out << transaction->string1 << " " << transaction->string2 << " " << transaction->amount << " "
            << transaction->date << std::endl;
    }
    out.close();
}

void Blockchain::myMinTxA(const std::string &username, const std::string &password, const std::string &path) {
    std::stringstream ss;
    ss << username;
    ss << password;
    DoubleList<transaction *> transactions = usersHash.get(ss.str())->data->minTxA();

    std::ofstream out(path);
    for (int i = 0; i < transactions.SIZE(); ++i) {
        transaction *transaction = transactions[i];
        out << transaction->string1 << " " << transaction->string2 << " " << transaction->amount << " "
            << transaction->date << std::endl;
    }
    out.close();
}

void Blockchain::setTx(const std::string &username, const std::string &password, const std::string &to, float amount) {
    std::stringstream ss;
    ss << username;
    ss << password;
    const auto p1 = std::chrono::system_clock::now();
    std::stringstream date;
    date << std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
    auto *tx = new transaction(username, to, amount, date.str());

    usersHash.get(ss.str())->data->insert(tx);
    allOrderByDate.insert(tx);
    allOrderByAmount.insert(tx);
    usersHash.get(ss.str())->data->hash = usersHash.get(ss.str())->data->calculateHash();

    auto iterator = usersHash.get(ss.str());
    iterator = iterator->next;
    while (iterator != nullptr) {
        iterator->data->prevHash = iterator->prev->data->hash;
        iterator->data->hash = iterator->data->calculateHash();
        iterator = iterator->next;
    }
}

void Blockchain::setTx(const std::string &username, const std::string &password, const std::string &to, float amount,
                       const std::string &date) {
    std::stringstream ss;
    ss << username;
    ss << password;
    auto *tx = new transaction(username, to, amount, date);
    usersHash.get(ss.str())->data->insert(tx);
    allOrderByDate.insert(tx);
    allOrderByAmount.insert(tx);
    usersHash.get(ss.str())->data->hash = usersHash.get(ss.str())->data->calculateHash();

    auto iterator = usersHash.get(ss.str());
    iterator = iterator->next;
    while (iterator != nullptr) {
        iterator->data->prevHash = iterator->prev->data->hash;
        iterator->data->hash = iterator->data->calculateHash();
        iterator = iterator->next;
    }
}

bool Blockchain::searchTx(const std::string &username, const std::string &password, const std::string &to, float amount,
                          const std::string &date) {
    std::stringstream ss;
    ss << username;
    ss << password;
    auto *tx = new transaction(username, to, amount, date);
    std::stringstream key;
    key << *(tx);
    return usersHash.get(ss.str())->data->dataHash.search(key.str());
}

bool Blockchain::searchUser(const std::string &username, const std::string &password) {
    std::stringstream ss;
    ss << username;
    ss << password;
    return usersHash.search(ss.str());
}

void Blockchain::mineCascade(const std::string &username, const std::string &password) {
    std::stringstream ss;
    ss << username;
    ss << password;
    usersHash.get(ss.str())->data->mine();
    auto iterator = usersHash.get(ss.str());
    iterator = iterator->next;
    while (iterator != nullptr) {
        iterator->data->prevHash = iterator->prev->data->hash;
        iterator->data->hash = iterator->data->calculateHash();
        iterator = iterator->next;
    }
}

std::ostream &operator<<(std::ostream &os, const Blockchain &tx) {
    auto iterator = tx.chain.begin();
    while (iterator != nullptr) {
        os << *(iterator->data) << std::endl;
        iterator = iterator->next;
    }
    return os;
}

void Blockchain::myTxsDateRange(const std::string &username, const std::string &password, const std::string &start,
                                const std::string &end, const std::string &path) {
    std::stringstream ss;
    ss << username;
    ss << password;
    DoubleList<transaction *> transactions = usersHash.get(ss.str())->data->orderByDate.makeListRange(
            new transaction{"", "", 0, start}, new transaction{"", "", 0, end});
    std::ofstream out(path);
    for (int i = 0; i < transactions.SIZE(); ++i) {
        transaction *transaction = transactions[i];
        out << transaction->string1 << " " << transaction->string2 << " " << transaction->amount << " "
            << transaction->date << std::endl;
    }
    out.close();
}

void Blockchain::myTxsAmountRange(const std::string &username, const std::string &password, float start, float end,
                                  const std::string &path) {
    std::stringstream ss;
    ss << username;
    ss << password;
    DoubleList<transaction *> transactions = usersHash.get(ss.str())->data->orderByAmount.makeListRange(
            new transaction{"", "", start, ""}, new transaction{"", "", end, ""});
    std::ofstream out(path);
    std::cout << "size: " << transactions.SIZE() << std::endl;
    for (int i = 0; i < transactions.SIZE(); ++i) {
        transaction *transaction = transactions[i];
        out << transaction->string1 << " " << transaction->string2 << " " << transaction->amount << " "
            << transaction->date << std::endl;
    }
    out.close();
}

#endif