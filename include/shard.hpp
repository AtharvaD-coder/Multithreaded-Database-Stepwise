#pragma once
#include "./transaction.hpp"
#include "./dashtable.hpp"
#include <string>
#include <thread>
#include <queue>
#include <future>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "../libs/concurrentqueue/concurrentqueue.h"  
using namespace std;

class TransactionWrapper {
public:
    Transaction transaction;
    promise<string> promiseObj; 
    TransactionWrapper(const Transaction& txn) : transaction(txn) {}
};

class Shard {
    Dashtable dahtable;
    thread shardThread;
    // We use a high-performance concurrent queue.
    moodycamel::ConcurrentQueue<TransactionWrapper*> transactionQueue;
    mutex queueMutex;
    condition_variable queueCondition;
    atomic<bool> running;
public:
    Shard();
    ~Shard();
    void run();
    future<string> submitTransaction(Transaction transaction);
    void shutdown();
};
