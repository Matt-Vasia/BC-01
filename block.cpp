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

    void setBal(double bal) { balance = bal; }
    void setName(string newName) { name = newName; }
    void setPublic_key(const string &key) { public_key = key; }
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
            return SqrtToString("");

        vector<string> layer;
        layer.reserve(transactions.size());
        for (const auto &tx : transactions)
            layer.push_back(tx.getTransactionID());

        while (layer.size() > 1)
        {
            vector<string> next;
            next.reserve((layer.size() + 1) / 2);
            for (size_t i = 0; i < layer.size(); i += 2)
            {
                const string &left = layer[i];
                const string &right = (i + 1 < layer.size()) ? layer[i + 1] : layer[i];

                next.push_back(SqrtToString(left + right));
            }
            layer.swap(next);
        }
        return layer[0];
    }

    public:

         bool mineBlock(){

            string dif(difficulty, '0');

            auto start = chrono::high_resolution_clock::now();

            nonce = 0;
            hash = calculateHash();

            while(hash.substr(0,difficulty) != dif){
                nonce++;
                hash = calculateHash();

                if (nonce > 30000000) {
                    cout << "Mining taking too long - hash function may not produce leading zeros!" << endl;
                    return false;
                }
                if(chrono::high_resolution_clock::now() - start > chrono::seconds(5))
                    return false;
            }
            return true;
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

    const Block& getLastBlock() const {
        return chain.back();
    }

    bool addTransaction(const Transaction& trans){
        // Validate sender exists and has sufficient available balance
        User* sender = nullptr;
        for (auto& user : Users) {
            if (user.getPublic_key() == trans.getSenderKey()) {
                sender = &user;
                break;
            }
        }
        if (!sender) {
            cout << "Transaction failed: Sender with key " << trans.getSenderKey() << " not found." << endl << endl;
            return false;
        }

        // Validate receiver exists
        bool receiverFound = false;
        for (auto& user : Users) {
            if (user.getPublic_key() == trans.getReceiverKey()) {
                receiverFound = true;
                break;
            }
        }
        if (!receiverFound) {
            cout << "Transaction failed: Receiver with key " << trans.getReceiverKey() << " not found." << endl << endl;
            return false;
        }

        // Calculate sender's already-reserved amount in current pending transactions
        double reserved = 0.0;
        for (const auto& tx : pendingTransactions) {
            if (tx.getSenderKey() == trans.getSenderKey()) reserved += tx.getAmount();
        }
        const double available = sender->getBal() - reserved;
        if (trans.getAmount() > available) {
            cout << "Transaction failed: " << sender->getName() << " has insufficient funds (available "
                 << fixed << setprecision(2) << available << ", needed " << trans.getAmount() << ")." << endl << endl;
            return false;
        }

        pendingTransactions.push_back(trans);
        return true;
    }

    bool minePending(){
        if(pendingTransactions.empty()){
            cout << "There are none pending transactions.\n";
            return false;
        }

        Block newBlock(getLastBlock().getHash(), pendingTransactions, difficulty);

        if(!newBlock.mineBlock())
            return false;

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
        return true;
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