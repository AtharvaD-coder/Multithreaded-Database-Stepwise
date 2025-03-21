#include "../include/database.hpp"
#include "../include/shard.hpp"
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
using namespace std;

Database::Database(int noOfShards = thread::hardware_concurrency()) {
    this->noOfShards = noOfShards;
    cout << "NO OF SHARDS: " << noOfShards << endl;
    for (int i = 0; i < noOfShards; i++) {
        shards.emplace_back(new Shard());
    }
}

int Database::getShard(string key) {
    hash<string> hash_fn;
    size_t hashValue = hash_fn(key);
    int hashval = hashValue % noOfShards;
    return hashval;
}

string Database::Get(string key) {
    int shardIndex = getShard(key);
    Shard* shard = shards[shardIndex];
    future<string> resultFuture =
        shard->submitTransaction(Transaction{GET, key, ""});
    string result = resultFuture.get();
    return result;
}

void Database::Insert(string key, string value) {
    int shardIndex = getShard(key);
    Shard* shard = shards[shardIndex];
    future<string> resultFuture =
        shard->submitTransaction(Transaction{INSERT, key, value});
    // Optionally wait for result here or handle asynchronously.
}

void Database::Delete(string key) {
    int shardIndex = getShard(key);
    Shard* shard = shards[shardIndex];
    future<string> resultFuture =
        shard->submitTransaction(Transaction{DELETE, key, ""});
    string result = resultFuture.get();
}

Database::~Database() {
    for (auto s : shards) {
        delete s;
    }
    shards.clear();
}
