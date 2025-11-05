#ifndef LIB_H
#define LIB_H

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <chrono>
#include <cstdint>
#include <map>
#include <cassert>
#include <random>
#include <bitset>
#include <ctime>
#include <algorithm>

using namespace std;

// Function declarations moved to the top
long int Convert_to_ASCII(string str);
string SqrtToString(const string input);

struct TransactionOutput{
    string id; // monetos ID
    string receiverPublicKey; // kam priklauso
    double value; // monetos verte
    bool Spent = false;

    TransactionOutput() : value(0.0) {}

    TransactionOutput(string receiver, double bal, string txID, int index) 
    : receiverPublicKey(receiver), value(bal) {
        id = SqrtToString(txID+to_string(index));
    }

    bool IsSpent(const string& publicKey) const{
        return receiverPublicKey == publicKey;
    }
};

struct TransactionInput{
    string outputID;
    TransactionOutput unspentOutput;

    TransactionInput(string outId) : outputID(outId) {}
};

class User;

class Transaction;

class BlockChain;

extern vector<User> Users;
// extern vector<Transaction> Txs;

void ReadFromFile();

void UIfunc();

void create_users();

void trans_generator(BlockChain& blockchain, vector<Transaction>& out_transactions);

// void mineBlock();

#endif
