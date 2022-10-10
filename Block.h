#include "SHA256.h"
#include <ctime>
#include <sstream>
#pragma once

class Block final{
    public:
        string PrevHash;

        Block(){
            this->m_nonce = -1;
            this->m_time = time(nullptr);
        }

        Block(uint32_t indexInput, const string &dataInput) : m_index(indexInput), m_data(dataInput) {
            this->m_nonce = -1;
            this->m_time = time(nullptr);
        }

        uint32_t GetIndex() const {return this->m_index;}
        int64_t GetNonce() const {return this->m_nonce;}
        string GetData() const {return this->m_data;}
        time_t GetTime() const {return this->m_time;}
        string GetHash() const {return this->m_hash;}
        void SetAsGenesis(){
            this->PrevHash = "0000000000000000000000000000000000000000000000000000000000000000";
            this->m_time = time(nullptr);
            this->m_index = 0;
            this->m_data = "";
        }

        // minar
        void DOMine(uint32_t difficulty){
            if (m_hash.substr(0,difficulty)!="0000"){
                char * cstr = new char[difficulty + 1];
                for (uint32_t i = 0; i < difficulty; ++i){cstr[i] = '0';}
                cstr[difficulty] = '\0';

                string str(cstr);

                do{
                    this->m_nonce++;
                    this->m_hash = CalculateHash();
                }while (str.compare(this->m_hash.substr(0, difficulty)));
            }
        }

    private:
        uint32_t m_index;
        int64_t m_nonce;
        string m_data;
        string m_hash;
        time_t m_time;

        // hash con index, time, data, nonce, prevhash
        const string CalculateHash() const{
            stringstream ss;
            ss << this->m_index << this->m_time << this->m_data << this->m_nonce << this->PrevHash;
            return SHA256::encrypt(ss.str());
        }

    friend class BlockChain;
};







