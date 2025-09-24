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

long int Convert_to_ASCII(string& str) {
    long int sum = 0;

    while(str.length()>=3) { // Jei stringas turi bent 3 simbolius
        const int OrBit = ((str[0] | str[1]) ^ (str[2] << 2) ^ 31) >> 4;
        const int OrBit2 = ((str[2] | str[1]) ^ (str[0] << 1) ^ 31) >> 3;
        const int AndBit = ((str[1] & str[2]) ^ (str[0] << 3) ^ 31) >> 7;
        const int AndBit2 = ((str[2] & str[0]) ^ (str[1] << 4) ^ 31) >> 5;
        sum*=31;
        sum += ((OrBit * AndBit2) ^ (OrBit2 * AndBit) ^ static_cast<int>(str[0]) ^ static_cast<int>(str[1]) ^ static_cast<int>(str[2]) ^ str.length());
        str.erase(0,3);
    }

    if(str.length()>=2) { // Jei stringas turi bent 2 simbolius
        const int OrBit = (str[0]|str[1]) >> 2;
        if (OrBit >= 0)
            sum += sqrt(OrBit) + static_cast<int>(str[1]);
        else
            sum += static_cast<int>(str[1]);
        str.erase(0,2);
    }

    if(!str.empty()) { // jei stringas turi 1 simboli
        for (char c : str) {
            sum += static_cast<int>(c);
        }
        str.erase(0,1);
    }

    return static_cast<double>(abs(sum));
}