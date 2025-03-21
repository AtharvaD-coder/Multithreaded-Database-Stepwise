# Phase 4 Documentation

In **Phase 4**, we enhance the key-value store by introducing **transactional processing** and **multi-threading** for increased performance and concurrency. This phase integrates **asynchronous operations** to handle multiple transactions concurrently, improving throughput. Additionally, the system is further optimized by using a **high-performance concurrent queue** for thread-safe communication and task handling between threads.

---

### Key Changes in Phase 4:

- **Shard-Level Multi-threading**: Each shard operates in its own dedicated thread to handle transactions concurrently.
- **Transaction Wrapping**: Transactions are wrapped in a `TransactionWrapper` class to handle asynchronous results with `std::future`.
- **Concurrent Queue**: The system now uses a high-performance concurrent queue (from `moodycamel::ConcurrentQueue`) to manage incoming transactions efficiently.
- **Thread-Safe Operations**: Operations like `Insert`, `Delete`, and `Get` are processed in parallel, improving the overall throughput of the system.

---

## Overview of Phase 4 Files

### 1. **shard.hpp**

The `shard.hpp` file defines the `Shard` class, which encapsulates the processing of transactions within a dedicated thread for each shard. It uses a `ConcurrentQueue` to queue transactions and a `std::thread` to process them asynchronously.

#### Key Features of the `Shard` Class:

- **Transaction Queue**: Transactions are added to a thread-safe queue and processed sequentially within the shard's dedicated thread.
- **Transaction Processing**: The shard processes transactions (e.g., INSERT, GET, DELETE) using a `run` method, ensuring each transaction is handled correctly and asynchronously.
- **Asynchronous Transaction Handling**: The `submitTransaction` method returns a `std::future` to allow asynchronous handling of transaction results.
- **Shutdown Mechanism**: The `shutdown` method stops the shard thread gracefully when the database is destroyed or when no longer needed.

#### Key Methods:
- **submitTransaction**: Adds a transaction to the queue and returns a `std::future` for the transaction's result.
- **run**: Continuously processes transactions from the queue as long as the shard is running.
- **shutdown**: Stops the shard's processing thread.

---

### 2. **shard.cpp**

The `shard.cpp` file implements the methods of the `Shard` class, including transaction processing, transaction queue management, and asynchronous handling.

#### Key Concepts in `Shard.cpp`:
- **Threading**: A dedicated thread processes transactions in the shard. This allows for parallel transaction handling across different shards.
- **Concurrent Queue**: The system uses a `moodycamel::ConcurrentQueue` for efficient and thread-safe queuing of transactions.
- **Promise and Future**: Each transaction is wrapped in a `TransactionWrapper` that contains a `std::promise`, enabling asynchronous results to be returned to the caller.

---

### 3. **database.hpp**

The `database.hpp` file defines the `Database` class, which now manages multiple shards of type `Shard`. The database creates multiple shards, distributes transactions, and handles communication with the shards through `submitTransaction`.

#### Key Changes:
- **Shard Management**: The database now manages `Shard` objects, which handle transactions concurrently within their own threads.
- **Transaction Submission**: The `Get`, `Insert`, and `Delete` methods now submit transactions to the appropriate shard and use `std::future` to retrieve results asynchronously.

---

### 4. **database.cpp**

The `database.cpp` file implements the methods of the `Database` class, including the logic for distributing transactions to the appropriate shard and retrieving results.

#### Key Concepts:
- **Shard Distribution**: The `getShard` method computes the appropriate shard based on the hash of the key.
- **Asynchronous Calls**: The `Insert`, `Get`, and `Delete` methods now submit transactions to the corresponding shard and wait for results asynchronously using `std::future`.

---

### 5. **transaction.hpp**

The `transaction.hpp` file defines the structure of a **transaction**. It introduces the `TransactionType` enum and the `Transaction` structure that is used by the system to represent operations like **INSERT**, **GET**, and **DELETE**.

---

## Technical Concepts Introduced in Phase 4

### 1. **Transactional Processing**
In Phase 4, each operation is now treated as a transaction. Transactions are added to a queue and processed asynchronously, allowing the system to handle multiple operations concurrently. This significantly improves throughput by leveraging multi-threading.

### 2. **Concurrent Queue**
The `moodycamel::ConcurrentQueue` is used to queue transactions. It allows for high-performance, thread-safe communication between threads, ensuring that transactions are processed in the correct order without race conditions.

### 3. **Thread Management**
Each shard operates in its own thread. The shard processes transactions independently from the other shards, enabling the system to handle transactions in parallel and scale more effectively.

### 4. **Promises and Futures**
Each transaction returns a `std::future` to the caller, allowing the caller to wait for the result asynchronously. This design pattern helps to decouple transaction submission from result retrieval, enabling non-blocking calls.

### 5. **Shutdown Mechanism**
The `shutdown` method gracefully stops the shard's thread, ensuring that any pending transactions are processed before the thread is terminated.

---

## Concurrent Queue Installation via Git Submodule

To integrate the `ConcurrentQueue` library from **moodycamel** into your project, follow these steps to add it as a Git submodule:

1. Navigate to your project’s root directory.
2. Run the following command to add the `ConcurrentQueue` repository as a submodule:
   ```bash
   git submodule add https://github.com/cameron314/concurrentqueue.git libs/concurrentqueue
   ```
3. Initialize and update the submodule:
   ```bash
   git submodule update --init --recursive
   ```
4. The `concurrentqueue` library is now located in the `libs/concurrentqueue` directory. You can include it in your project by adding `#include "../libs/concurrentqueue/concurrentqueue.h"` wherever needed.

---
