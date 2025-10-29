// #include "LIB.h"
#include "Functions.cpp"

using namespace std;


int main() {
    BlockChain myChain(3);

    create_users();
    trans_generator();

    for(const auto& tx : Txs) {
        myChain.addTransaction(tx);
    }
    Txs.clear();

    myChain.minePending();

    cout << "\n--- Blockchain content ---" << endl;
    myChain.printChain();
    return 0;
}

