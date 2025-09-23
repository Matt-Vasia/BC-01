#include "LIB.h"

using namespace std;

int Convert_to_ASCII(string str) {
    long int sum = 0;
    for(char symbol : str)
    {
        sum+=static_cast<int>(symbol);
    }
    return sum;
}

int main() {
    string input="test";
    cout << Convert_to_ASCII(input);

    return 0;
}