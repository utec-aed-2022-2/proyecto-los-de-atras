#pragma once
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "block.h"

/****************************** declaration ******************************/
class blockchain
{
private:
    double_list<block*> chain;

public:
    void addBlock();
    void setData(uint64_t, transaction);
    void minechain(uint64_t);

    friend std::ostream& operator<<(std::ostream& os, blockchain& bch)
    {
        for (int i = 0; i < bch.chain.size(); i++)
        {
            os << *(bch.chain[i]) <<  std::endl <<  std::endl;
        }
        return os;
    }
};

/****************************** definition ******************************/
void blockchain::addBlock()
{
    if(chain.is_empty())
    {
        chain.push_back(new block(chain.size()+1));
        chain.back()->mine();
    }
    else
    {
        chain.push_back(new block(chain.size()+1, chain.back()->GetHash()));
        chain.back()->mine();
    }
}

void blockchain::setData(uint64_t id, transaction tx)
{
    chain[id-1]->data.push_back(tx);
    chain[id-1]->hash = chain[id-1]->calculateHash();
    
    for (int i = id; i < chain.size(); i++){
        chain[i]->prevHash = chain[i-1]->GetHash();
        chain[i]->hash = chain[i]->calculateHash();
    }
}

void blockchain::minechain(uint64_t id){
    chain[id-1]->mine();
    for (int i = id; i < chain.size(); i++){
        chain[i]->prevHash = chain[i-1]->GetHash();
        chain[i]->hash = chain[i]->calculateHash();
    }
}

#endif
