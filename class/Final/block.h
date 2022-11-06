#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include "transaction.h"
#include "../BPlusTree.h"
#include "../../function/hashFunctions.h"

const std::string hashGenesis = "0000000000000000000000000000000000000000000000000000000000000000";
const uint64_t nonceDefaul = -1;

struct block
{
    std::uint64_t id;
    std::uint64_t nonce;
    
    BPlusTree<transaction> orderbyAmount;
    BPlusTree<transaction> orderbyDate;

    std::string prevHash{hashGenesis};
    std::string hash;
};

#endif