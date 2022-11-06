#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "../doubleList.h"
#include "../hashMap.h"
#include "block.h"

class BlockChain
{
private:
    BPlusTree<std::string> orderByName;
    hashMap<std::string, nodeList<block>*> UsersHash;
    doubleList<block> UsersList;
};

#endif