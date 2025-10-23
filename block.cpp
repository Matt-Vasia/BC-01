#include "LIB.h"

class User
{
private:
    string name;
    string public_key;
    double balance;

public:
    User(const string &n, const string &key, double bal)
        : name(n), public_key(key), balance(bal)
    {
    }

    string getName() { return name; }
    string getPublic_key() { return public_key; }
    double getBal() { return balance; }

    void setBal(double bal) { balance = bal; } // gal reiktu idet logika, kad nebutu galima manipuliuot.
    void setBal(string newName) { name = newName; }
    void setBal(double key) { public_key = key; }
};

class Transaction
{
    string transactionID;
    string senderKey;
    string recieverKey;
    double amount;

public:
    Transaction(const string &sendKey, const string &recKey, double total)
        : senderKey(sendKey), recieverKey(recKey), amount(total)
    {
        string transHash = sendKey + recKey + to_string(total);
        transactionID = SqrtToString(transHash);
    }

    // getters
    string getTransactionID() const { return transactionID; }
    string getSenderKey() const { return senderKey; }
    string getReceiverKey() const { return recieverKey; }
    double getAmount() const { return amount; }
};

class Block
{
private:
    string prevHash;
    long timestamp;
    double version;
    string merkleRoot;
    int nonce;
    int difficulty;
    string hash;

    vector<Transaction> transactions;

    string calculateHash()
    {
        string blockData = prevHash +
                           to_string(timestamp) +
                           to_string(version) +
                           merkleRoot +
                           to_string(nonce) +
                           to_string(difficulty);
        return SqrtToString(blockData);
    }

    string calculateMerkleRoot()
    {
        if (transactions.empty())
            return "empty block";

        string hash = "";

        for (auto &&i : transactions)
            hash += i.getTransactionID();
        return SqrtToString(hash);
    }

    // constructor
    Block(const string &previousHash, const vector<Transaction> trans, int diff)
        : prevHash(previousHash), transactions(trans), difficulty(diff), version(1), nonce(0)
    {
        timestamp = time(0);
        merkleRoot = calculateMerkleRoot();
        hash = calculateHash();
    }

public:
    // Getters
    string getHash() const { return hash; }
    string getPreviousHash() const { return prevHash; }
    long getTimestamp() const { return timestamp; }
    int getVersion() const { return version; }
    string getMerkleRoot() const { return merkleRoot; }
    int getNonce() const { return nonce; }
    int getDifficulty() const { return difficulty; }
    vector<Transaction> getTransactions() const { return transactions; }
};