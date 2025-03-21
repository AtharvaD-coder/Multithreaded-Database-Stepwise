#pragma once
#include <vector>
#include <memory>
#include <string>
#include "./shard.hpp"   // Now using Shard instead of Dashtable directly
using namespace std;

class Database {
    int noOfShards;
    vector<Shard*> shards;
    int getShard(string key);
public:
    Database(int noOfShards);
    ~Database();
    string Get(string key);
    void Insert(string key, string value);
    void Delete(string key);
};
