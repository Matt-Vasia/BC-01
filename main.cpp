#include "LIB.h"

using namespace std;


int main() {
    string input;
    cin>>input;

    long int inputInAscii = Convert_to_ASCII(input);

    long double sqrtOfInputInAscii = sqrt(inputInAscii);
    if(sqrtOfInputInAscii == static_cast<int>(sqrtOfInputInAscii))
        inputInAscii+=1;
    sqrtOfInputInAscii = sqrt(inputInAscii);

    ostringstream oss;
    oss << setprecision(25) << fixed << sqrtOfInputInAscii;
    string sqrtAsString = oss.str();

    size_t decimalPos = sqrtAsString.find('.');
    string answer = "";
    if (decimalPos != string::npos) {
        answer = sqrtAsString.substr(decimalPos + 1, 20);
    }

    cout<<answer;
    return 0;
}

