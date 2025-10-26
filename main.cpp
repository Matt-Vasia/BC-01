#include "LIB.h"
// #include "block.cpp"

using namespace std;


int main() {
    // UIfunc();
    create_users();
    trans_generator();
    cout << "Testing hash function:" << endl;
for(int i = 0; i < 10; i++) {
    string test = "test" + to_string(i);
    string hash = SqrtToString(test);
    cout << "Input: " << test << " -> Hash: " << hash << " (length: " << hash.length() << ")" << endl;
}
    mineBlock();
    return 0;
}

