#include "LIB.h"

class User{
private:
    string name;
    string public_key;
    double balance;

public:
    User(const string& n, const string& key, double bal)
        : name(n), public_key(key), balance(bal)
    {}
    
};

class Transaction{
    string transactionID;
    string senderKey;
    string recieverKey;
    double amount;

    public:
    Transaction(const string& sendKey, const string& recKey, double total)
    : senderKey(sendKey), recieverKey(recKey), amount(total)
    {
        string transHash = sendKey + recKey + std::to_string(total);
        transactionID = SqrtToString(transHash);
    }

    //getters
    string getTransactionID() const { return transactionID; }
    string getSenderKey() const { return senderKey; }
    string getReceiverKey() const { return recieverKey; }
    double getAmount() const { return amount; }
};

class Block{
    private:
    string prevHash;
    long timestamp;
    double version;
    string merkleRoot;
    int nonce;
    int difficulty;
    string hash;

    vector<Transaction> transactions;

    // Getters
    string getHash() const { return hash; }
    string getPreviousHash() const { return prevHash; }
    long long getTimestamp() const { return timestamp; }
    int getVersion() const { return version; }
    string getMerkleRoot() const { return merkleRoot; }
    int getNonce() const { return nonce; }
    int getDifficulty() const { return difficulty; }
    vector<Transaction> getTransactions() const { return transactions; }
};