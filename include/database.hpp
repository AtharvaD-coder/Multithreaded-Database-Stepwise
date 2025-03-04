#pragma once
#include "../include/dashtable.hpp"
#include <string>
#include <vector>
using namespace std;

class Database {
    
    int noOfShards;

    vector<Dashtable*> shards;

    public:

    Database(int noOfShards);
    ~Database();
    string Get(string key);
    void Insert(string key, string value);
    void Delete(string key);
};