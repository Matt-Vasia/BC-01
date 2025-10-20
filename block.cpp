#include "LIB.h"

class User{
private:
    string name;
    string public_key;
    double balance;

public:
    User(const string& n, const string& key, double bal)
        : name(n), public_key(key), balance(bal)
    {}
    
};

class Transaction{
    string transactionID;
    string senderKey;
    string recieverKey;
    double amount;

    public:
    Transaction(const string& transID, const string& sendKey, const string& recKey, double total)
    : transactionID(transID), senderKey(sendKey), recieverKey(recKey), amount(total)
    {}
};