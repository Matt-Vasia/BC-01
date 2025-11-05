// #include "LIB.h"
#include "Functions.cpp"

using namespace std;


int main() {
    BlockChain myChain(3);

    create_users();
    trans_generator();

    myChain.printBalances(Users);

    
    int blockCount = 1;
    // 6. Kartojame procesą, kol yra neįtrauktų transakcijų
    while (!Txs.empty()) {
        cout << "\n=========================================" << endl;
        cout << "Preparing to mine Block #" << blockCount++ << endl;
        cout << Txs.size() << " transactions remaining." << endl;

        int transactionsToMine = min((int)Txs.size(), 100);
        
        vector<Transaction> transactionsForBlock;
        for (int i = 0; i < transactionsToMine; ++i) {
            transactionsForBlock.push_back(Txs.back());
            Txs.pop_back(); // Pašaliname transakciją iš pagrindinio sąrašo
        }

        cout << "Adding " << transactionsForBlock.size() << " transactions to the new block." << endl;
        // Try to add; if rejected, immediately requeue so nothing disappears
        vector<Transaction> acceptedForBlock;
        int successfulTransactions = 0;
        for (const auto& tx : transactionsForBlock) {
            if (myChain.addTransaction(tx)) {
                acceptedForBlock.push_back(tx);
                successfulTransactions++;
            }
        }

        if (acceptedForBlock.empty()) {
            cout << "No valid transactions for this block. Stopping to avoid infinite loop." << endl;
            break;
        }
        else
            cout << "Number of transactions added to block: " << successfulTransactions << endl << endl;

        if(!myChain.minePending())
        {
            blockCount--;
            size_t cnt = 0;
            // Return only the accepted ones (rejected were already requeued)
            while (!acceptedForBlock.empty()) {
                if (cnt % 2 == 0)
                    Txs.push_back(acceptedForBlock.back());
                else
                    Txs.insert(Txs.begin(), acceptedForBlock.back());
                acceptedForBlock.pop_back();
                ++cnt;
            }
        }
        else
            myChain.printBalances(Users);
    }

    cout << "\n=========================================" << endl;
    cout << "All transactions have been processed." << endl;


    cout << "\n--- Blockchain content ---" << endl;
    myChain.printChain();
    return 0;
}

