#include "../include/database.hpp"
#include <iostream>
using namespace std;

Database::Database(int noOfShards){

    this->noOfShards = noOfShards;
    
    for (int i = 0; i < noOfShards; i++) {
        shards.push_back(new Dashtable());
    }
}

string Database::Get(string key) {
    // Compute shard index using a simple hash
    hash<string> hash_fn;
    int shardIndex = hash_fn(key) % noOfShards;
    return shards[shardIndex]->Get(key);
}

void Database::Insert(string key, string value) {
    hash<string> hash_fn;
    int shardIndex = hash_fn(key) % noOfShards;
    shards[shardIndex]->Insert(key, value);
}

void Database::Delete(string key) {
    hash<string> hash_fn;
    int shardIndex = hash_fn(key) % noOfShards;
    shards[shardIndex]->Delete(key);
}

Database::~Database() {
    // Cleanup allocated dashtables.
    for (auto tbl : shards) {
        delete tbl;
    }
    shards.clear();
}