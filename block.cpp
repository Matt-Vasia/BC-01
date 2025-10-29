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

    string getName() const { return name; }
    string getPublic_key() const { return public_key; }
    double getBal() const { return balance; }

    void setBal(double bal) { balance = bal; } // gal reiktu idet logika, kad nebutu galima manipuliuot.
    void setName(string newName) { name = newName; }
    void setPublic_key(double key) { public_key = key; }
};

class Transaction
{
    string transactionID;
    string senderKey;
    string receiverKey;
    double amount;

public:
    Transaction(const string &sendKey, const string &recKey, double total)
        : senderKey(sendKey), receiverKey(recKey), amount(total)
    {
        string transHash = sendKey + recKey + to_string(total);
        transactionID = SqrtToString(transHash);
    }

    // getters
    string getTransactionID() const { return transactionID; }
    string getSenderKey() const { return senderKey; }
    string getReceiverKey() const { return receiverKey; }
    double getAmount() const { return amount; }
};

class Block
{
private:
    string prevHash;
    time_t timestamp;
    int version;
    string merkleRoot;
    int nonce;
    int difficulty=1;
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

    public:

         void mineBlock(){

            string dif(difficulty, '0');

            nonce = 0;
            hash = calculateHash();

            while(hash.substr(0,difficulty) != dif){
                nonce++;
                hash = calculateHash();

                if (nonce > 30000000) {
            cout << "Mining taking too long - hash function may not produce leading zeros!" << endl;
            break;
        }
            }

            cout << "--- BLOKAS ISKASTAS! ---" << endl;
            cout << "Hash: " << hash << endl;
            cout << "Nonce: " << nonce << endl;
        }

        void printBlock() const {
            cout << endl << "Previous Hash: " << getPreviousHash() << endl;
            cout << "Timestamp: " << ctime(&timestamp);
            cout << "Merkle Root: " << getMerkleRoot() << endl;
            cout << "Difficulty: " << getDifficulty() << endl << endl;
        }

    // constructor
    Block(const string &previousHash, const vector<Transaction> trans, int diff)
        : prevHash(previousHash), transactions(trans), difficulty(diff), version(1), nonce(0)
    {
        time(&timestamp);
        merkleRoot = calculateMerkleRoot();
        hash = calculateHash();
    }

public:
    // Getters
    string getHash() const { return hash; }
    string getPreviousHash() const { return prevHash; }
    time_t getTimestamp() const { return timestamp; }
    int getVersion() const { return version; }
    string getMerkleRoot() const { return merkleRoot; }
    int getNonce() const { return nonce; }
    int getDifficulty() const { return difficulty; }
    vector<Transaction> getTransactions() const { return transactions; }
    
    void setDifficulty(int num){difficulty=num;}
};

class BlockChain{
    public:
    vector<Block> chain;
    vector<Transaction> pendingTransactions;
    int difficulty;

    public:
    BlockChain(int diff=3) : difficulty(diff){
       
        Block genesisblock("0", vector<Transaction>(), difficulty);
        genesisblock.mineBlock();
        chain.push_back(genesisblock);
        cout << "Genesis block created!" << endl << endl;
    }

    Block getLastBlock(){
        return chain.back();
    }

    void addTransaction(const Transaction& trans){
          bool senderFound = false;
        for (auto& user : Users) {
            if (user.getPublic_key() == trans.getSenderKey()) {
                senderFound = true;
                if (user.getBal() < trans.getAmount()) {
                    cout << "Transaction failed: " << user.getName() << " has insufficient funds." << endl << endl;
                    return; // Neleidžiame pridėti transakcijos
                }
                break;
            }
        }
        if (!senderFound) {
            cout << "Transaction failed: Sender with key " << trans.getSenderKey() << " not found." << endl << endl;
            return;
        }

        pendingTransactions.push_back(trans);
    }

    void minePending(){
        if(pendingTransactions.empty()){
            cout << "There are none pending transactions.\n";
            return;
        }

        Block newBlock(getLastBlock().getHash(), pendingTransactions, difficulty);
        newBlock.mineBlock();

        chain.push_back(newBlock);

         // 5. Atnaujiname vartotojų balansus
        cout << "Updating user balances..." << endl;
        for (const auto& tx : pendingTransactions) {
            bool sender_found = false;
            bool receiver_found = false;
            // Atimame pinigus iš siuntėjo
            for (auto& user : Users) {
                if (user.getPublic_key() == tx.getSenderKey()) {
                    user.setBal(user.getBal() - tx.getAmount());
                    sender_found = true;
                    break;
                }
            }
            // Pridedame pinigus gavėjui
            for (auto& user : Users) {
                if (user.getPublic_key() == tx.getReceiverKey()) {
                    user.setBal(user.getBal() + tx.getAmount());
                    receiver_found = true;
                    break;
                }
            }
            if (!sender_found || !receiver_found) cout << "Balance update error for a transaction!" << endl;
        }
        cout << "Balances updated." << endl;

        pendingTransactions.clear();
    }

    void printChain() const {
        for(const auto& block : chain) {
            block.printBlock();
        }
    }

    void printBalances() const {
        cout << "\n--- User Balances ---" << endl;
        for (const auto& user : Users) {
            cout << user.getName() << ": " << fixed << setprecision(2) << user.getBal() << " coins" << endl;
        }
        cout << "---------------------\n" << endl;
    }

};