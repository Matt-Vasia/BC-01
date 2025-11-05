#include "Functions.cpp"

using namespace std;

int main() {
    srand(time(0)); // Inicializuojame atsitiktinių skaičių generatorių

    // 1. Sukuriame vartotojus
    create_users();
    if (Users.empty()) {
        cout << "No users created. Exiting." << endl;
        return 1;
    }

    // 2. Inicializuojame grandinę, duodami kiekvienam vartotojui pradinį balansą per Genesis bloką
    BlockChain myChain(3, Users, 1000.0);
    myChain.printBalances(Users);

    // 3. Sugeneruojame transakcijas, kurios iškart patenka į myChain.pendingTransactions
    trans_generator(myChain);

    int blockCount = 1;
    // 4. Kartojame procesą, kol yra neįtrauktų transakcijų
    while (!myChain.pendingTransactions.empty()) {
        cout << "\n=========================================" << endl;
        cout << "Preparing to mine Block #" << blockCount++ << endl;
        cout << myChain.pendingTransactions.size() << " transactions remaining in pending pool." << endl;

        // Kasame bloką su visomis laukiančiomis transakcijomis.
        // minePending() metodas pats pasirūpina visomis pendingTransactions.
        if (myChain.minePending()) {
            cout << "Block successfully mined." << endl;
            myChain.printBalances(Users);
        } else {
            cout << "Mining failed. There might be no valid transactions to mine." << endl;
            break; // Saugiklis, kad išvengtume amžino ciklo
        }
    }

    cout << "\n=========================================" << endl;
    cout << "All transactions have been processed." << endl;

    cout << "\n--- Final Blockchain content ---" << endl;
    myChain.printChain();
    return 0;
}