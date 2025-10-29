// #include "LIB.h"
#include "Functions.cpp"

using namespace std;


int main() {
    BlockChain myChain(2);

    create_users();
    trans_generator();

    myChain.printBalances();

    
    int blockCount = 1;
    // 6. Kartojame procesą, kol yra neįtrauktų transakcijų
    while (!Txs.empty()) {
        cout << "\n=========================================" << endl;
        cout << "Preparing to mine Block #" << blockCount++ << endl;
        cout << Txs.size() << " transactions remaining." << endl;

        // Atsitiktinai parenkame iki 100 transakcijų
        std::sort(Txs.begin(), Txs.end(), [](const Transaction& a, const Transaction& b) {
            return a.getAmount() < b.getAmount();
        });
        int transactionsToMine = min((int)Txs.size(), 100);
        
        vector<Transaction> transactionsForBlock;
        for (int i = 0; i < transactionsToMine; ++i) {
            transactionsForBlock.push_back(Txs.back());
            Txs.pop_back(); // Pašaliname transakciją iš pagrindinio sąrašo
        }

        cout << "Adding " << transactionsForBlock.size() << " transactions to the new block." << endl;
        for(const auto& tx : transactionsForBlock) {
            myChain.addTransaction(tx);
        }
    

    // for(const auto& tx : Txs) {
    //     myChain.addTransaction(tx);
    // }
    // Txs.clear();

    myChain.minePending();
    myChain.printBalances();
}

    cout << "\n=========================================" << endl;
    cout << "All transactions have been processed." << endl;


    cout << "\n--- Blockchain content ---" << endl;
    myChain.printChain();
    return 0;
}

