#include "Functions.cpp"

using namespace std;

int main() {
    srand(time(0));

    // 1. Sukuriame vartotojus
    create_users();
    if (Users.empty()) {
        cout << "No users created. Exiting." << endl;
        return 1;
    }

    // 2. Inicializuojame grandinę, duodami kiekvienam vartotojui pradinį balansą
    BlockChain myChain(3, Users, 1000.0);
    myChain.printBalances(Users);

    // 3. Sugeneruojame didelį kiekį transakcijų, bet JŲ NEPRIDEDAME į pendingTransactions.
    // Vietoj to, mes jas valdysime rankiniu būdu.
    vector<Transaction> allGeneratedTransactions;
    trans_generator(myChain, allGeneratedTransactions); // Pakeista funkcija, kad grąžintų transakcijas

    int blockCount = 1;
    // 4. Kartojame procesą, kol yra neįtrauktų transakcijų
    while (!allGeneratedTransactions.empty()) {
        cout << "\n=========================================" << endl;
        cout << "Preparing to mine Block #" << blockCount++ << endl;
        cout << allGeneratedTransactions.size() << " transactions remaining in total." << endl;

        // Paimame iki 100 transakcijų iš sąrašo galo
        int batchSize = min((int)allGeneratedTransactions.size(), 100);
        vector<Transaction> transactionsForThisBlock;
        for(int i = 0; i < batchSize; ++i) {
            transactionsForThisBlock.push_back(allGeneratedTransactions.back());
            allGeneratedTransactions.pop_back();
        }

        // Kasame bloką su konkrečia transakcijų partija
        if (myChain.minePending(transactionsForThisBlock)) {
            cout << "Block successfully mined." << endl;
            myChain.printBalances(Users);
        } else {
            cout << "Mining failed for this batch." << endl;
            // Grąžiname transakcijas atgal į sąrašą, jei kasimas nepavyko
            allGeneratedTransactions.insert(allGeneratedTransactions.end(), transactionsForThisBlock.begin(), transactionsForThisBlock.end());
            break;
        }
    }

    cout << "\n=========================================" << endl;
    cout << "All transactions have been processed." << endl;

    cout << "\n--- Final Blockchain content ---" << endl;
    myChain.printChain();
    return 0;
}