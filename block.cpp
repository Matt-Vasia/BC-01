#include "LIB.h"

class User
{
private:
    string name;
    string public_key;

public:
    User(const string &n, const string &key)
        : name(n), public_key(key)
    {
    }

    double getBalanse(const map<string, TransactionOutput>& allUTXOs) const // grazina visu naudotojo UTXO suma.
    {
        double sum=0.0;
        
        for (auto && pair : allUTXOs)
        {
            if(pair.second.IsSpent(public_key))
            {
                sum+=pair.second.value;
            }
        }
        return sum;
    }

    string getName() const { return name; }
    string getPublic_key() const { return public_key; }

    void setName(string newName) { name = newName; }
    void setPublic_key(const string &key) { public_key = key; }
};

class Transaction
{
    public:

    string transactionID;
    vector <TransactionOutput> output;
    vector <TransactionInput> input;

    private:
    string calculateHash(){
        string temp="";
        for (auto &&in : input)
        {
            temp+=in.outputID;
        }

        for (auto &&out : output)
        {
            temp+=to_string(out.value)+out.receiverPublicKey;
        }
        
        return SqrtToString(temp);
    }

public:
    Transaction(const vector<TransactionInput>& in, const vector<TransactionOutput>& out)
    : output(out), input(in)
    {
        transactionID = calculateHash();

        for(size_t i = 0; i < this->output.size(); ++i) {
            this->output[i].id = SqrtToString(transactionID + to_string(i));
        }
    }

    Transaction() {}

    double getInputValue() const 
    {
        double sum=0.0;

        for (auto &&in : input)
        {
            sum+=in.unspentOutput.value;
        }
        return sum;
    }

    double getOutputValue() const 
    {
        double sum=0.0;

        for (auto &&out : output)
        {
            sum+=out.value;
        }
        return sum;
    }

    // getters
    string getTransactionID() const { return transactionID; }
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
    map<string, TransactionOutput> allUTXO; // string yra TransactionOutut id

    public:
    BlockChain(int diff=3, const vector<User>& initialUsers, double initialBalance) : difficulty(diff){
       
        cout << "Creating Genesis block..." << endl;

        // Coinbase sistema 
        vector<TransactionInput> genesisInputs; // Tuscias
        vector<TransactionOutput> genesisOutputs;

        for (const auto& user : initialUsers) {
            // Kiekvienam vartotojui sukuriame po viena pradini coina
            TransactionOutput initialCoin(user.getPublic_key(), initialBalance, "GENESIS_TX", 0); // monetos konstruktorius
            
            allUTXO[initialCoin.id] = initialCoin;
            genesisOutputs.push_back(initialCoin);
        }

    Transaction genesisTransaction(genesisInputs,genesisOutputs);

    vector<Transaction> genesisBlockTransactions;
    genesisBlockTransactions.push_back(genesisTransaction);

    Block genesisBlock("0", genesisBlockTransactions, difficulty);
    genesisBlock.mineBlock();
    chain.push_back(genesisBlock);
    
    cout << "Genesis block created with starting coins" << endl << endl;
    }

    Block getLastBlock(){
        return chain.back();
    }

    bool validateTransaction(const Transaction& trans)const {
        for (auto &&in : trans.input) // tikrina ar egzistuoja tokios monetos ir ar nera isleistos
        {
            if(allUTXO.count(in.outputID)==0){
                cout << "Error: Input " << in.outputID << " doesnt exist."<< endl;
                return false;
            }
        }
        
        if(trans.getInputValue() < trans.getOutputValue()){
            cout << "Validation Error: Inputs value (" << trans.getInputValue() 
                 << ") is less than outputs value (" << trans.getOutputValue() << ")" << endl;
                 return false;
        }
        return true;
    }

    bool addTransaction(const Transaction& trans){
        if(validateTransaction(trans) == false){
            cout << "Transaction validation failed." << endl << endl;
            return false;
        }
        pendingTransactions.push_back(trans);
        cout << "Transaction valid." << endl << endl;
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

        // Atnaujiname UTXO sąrašą
        cout << "Updating UTXO set..." << endl;
        for (const auto& tx : pendingTransactions) {
            // Pašaliname "išleistas" monetas (inputs)
            for (const auto& in : tx.input) {
                allUTXO.erase(in.outputID);
            }
            // Pridedame naujas "neišleistas" monetas (outputs)
            for (const auto& out : tx.output) {
                allUTXO[out.id] = out;
            }
        }
        cout << "UTXO set updated." << endl;

        pendingTransactions.clear();
        return true;
    }

    void printChain() const {
        for(const auto& block : chain) {
            block.printBlock();
        }
    }

    void printBalances() const {
        cout << "\n--- User Balances (from UTXOs) ---" << endl;
        // Pastaba: Tikroje UTXO sistemoje, mes iteruotume per visus vartotojus ir
        // apskaičiuotume jų balansą iš UTXO rinkinio.
        // Tam reikia, kad globalus 'Users' sąrašas būtų pasiekiamas čia.
        // Kol kas ši funkcija paliekama kaip pavyzdys, kur vyktų balanso skaičiavimas.
        /*
        for (const auto& user : Users) {
            cout << user.getName() << ": " << fixed << setprecision(2) << user.getBalanse(allUTXO) << " coins" << endl;
        }
        */
        cout << "--------------------------------------\n" << endl;
    }

};