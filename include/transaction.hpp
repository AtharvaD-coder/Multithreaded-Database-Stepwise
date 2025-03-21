#pragma once
#include <string>
using namespace std;

enum TransactionType {
    INSERT,
    GET,
    DELETE
};

struct Transaction {
    TransactionType type;
    string key;
    string value;
};
