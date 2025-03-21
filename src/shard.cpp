#include "../include/shard.hpp"
#include <atomic>
#include <memory>
#include <chrono>
#include <thread>
using namespace std;

Shard::Shard() : dahtable(Dashtable()), running(true) {
    shardThread = thread(&Shard::run, this);
}

void Shard::shutdown() {
    running.store(false, memory_order_relaxed);
}

void Shard::run() {
    while (running.load(memory_order_relaxed)) {
        TransactionWrapper* wrapper;
        if (transactionQueue.try_dequeue(wrapper)) {
            switch (wrapper->transaction.type) {
                case INSERT:
                    dahtable.Insert(wrapper->transaction.key, wrapper->transaction.value);
                    wrapper->promiseObj.set_value("Insert successful");
                    break;
                case DELETE:
                    dahtable.Delete(wrapper->transaction.key);
                    wrapper->promiseObj.set_value("Delete successful");
                    break;
                case GET: {
                    string result = dahtable.Get(wrapper->transaction.key);
                    wrapper->promiseObj.set_value(result);
                    break;
                }
            }
        } else {
            this_thread::sleep_for(chrono::milliseconds(3));
        }
    }
    // Process any remaining transactions before exiting.
    TransactionWrapper* remainingWrapper;
    while (transactionQueue.try_dequeue(remainingWrapper)) {
        switch (remainingWrapper->transaction.type) {
            case INSERT:
                dahtable.Insert(remainingWrapper->transaction.key, remainingWrapper->transaction.value);
                remainingWrapper->promiseObj.set_value("Insert successful");
                break;
            case DELETE:
                dahtable.Delete(remainingWrapper->transaction.key);
                remainingWrapper->promiseObj.set_value("Delete successful");
                break;
            case GET: {
                string result = dahtable.Get(remainingWrapper->transaction.key);
                remainingWrapper->promiseObj.set_value(result);
                break;
            }
        }
    }
}

future<string> Shard::submitTransaction(Transaction transaction) {
    auto wrapper = new TransactionWrapper(transaction);
    transactionQueue.enqueue(wrapper);
    return wrapper->promiseObj.get_future();
}

Shard::~Shard() {
    shutdown();
    if (shardThread.joinable()) {
        shardThread.join();
    }
}
