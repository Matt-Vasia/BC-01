
#ifndef LIB_H
#define LIB_H

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <chrono>
#include <cstdint>
#include <map>
#include <cassert>
#include <random>
#include <bitset>
#include <ctime>

using namespace std;

class User;

class Transaction;

class BlockChain;

long int Convert_to_ASCII(string str);

void ReadFromFile();

string SqrtToString(const string input);

void UIfunc();

void create_users();

void trans_generator();

void mineBlock();

#endif
