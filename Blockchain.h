#include "Block.h"
#include "ForwardList.h"

#pragma once

#include <cstdint>

using namespace std;

class BlockChain {
    public:
        BlockChain(){this->m_difficulty = 4;}

        void AddGenesis(){
            Block genesis(0, "");
            genesis.SetAsGenesis();
            genesis.DOMine(this->m_difficulty);
            this->m_chain.push_back(genesis);
        }

        void AddBlock(Block newBlock){
            newBlock.PrevHash = GetLastBlock().GetHash();
            newBlock.DOMine(this->m_difficulty);
            this->m_chain.push_back(newBlock);
        }

        void PrintBlocks(){
            cout << endl << "All blocks:" << endl << endl;
            for (int i = 0; i < this->m_chain.size(); i++) {
                cout << "Index: " << m_chain[i].GetIndex() << endl;
                cout << "Nonce: " << m_chain[i].GetNonce() << endl;
                cout << "Data: " << m_chain[i].GetData() << endl;
                cout << "PreHash: " << m_chain[i].PrevHash << endl;
                cout  << "Hash: " << m_chain[i].GetHash() << endl;
                cout << endl;
            }
            cout << endl;
        }

        void Datablock(){
            uint32_t index;
            cout<<"Enter your block for insert data: "; cin >> index;
            cin.ignore();
            cout<<"Enter your data for block "<< index <<": ";
            string dataIn;
            getline(cin,dataIn); 
            m_chain[index].m_data = dataIn;
            m_chain[index].m_hash = m_chain[index].CalculateHash();

            for (int i = index+1; i < m_chain.size(); i++){
                m_chain[i].PrevHash = m_chain[i-1].GetHash();
                m_chain[i].m_hash = m_chain[i].CalculateHash();
            }
            
            PrintBlocks();
        }

        void Mineblock(){
            uint32_t index;
            cout<<"Enter your block to mine: "; cin>>index;
            m_chain[index].DOMine(4);
            for (int i = index+1; i < m_chain.size(); i++){
                m_chain[i].PrevHash = m_chain[i-1].GetHash();
                m_chain[i].m_hash = m_chain[i].CalculateHash();
            }

            PrintBlocks();
        }

    private:
        uint32_t m_difficulty;
        ForwardList<Block> m_chain;

        const Block GetLastBlock() {return this->m_chain.back();}
        const uint32_t GetChainSize() {return this->m_chain.size();}
};


