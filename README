# Key-Value Store with Sharding, Multi-Threading, and Transaction Support

This project implements a scalable and concurrent **key-value store** in C++. It leverages **sharding**, **consistent hashing**, and **asynchronous transaction processing** to enable efficient horizontal scaling. The system supports **multi-threading** and **lock-free data structures** for high throughput, ensuring efficient concurrent execution of database operations.

---

## Architectural Overview

The database development process has been divided into multiple phases, with each phase implemented in a dedicated branch. Additionally, each phase includes a corresponding documentation file in the `docs` folder, providing a detailed explanation of the phase's implementation and key technical concepts.

### Phase 1: Core Data Structures
Phase 1 establishes the fundamental data structures necessary for an efficient key-value store:
- **Bucket**: Manages a collection of key-value pairs with efficient lookup.
- **Segment**: Groups multiple buckets and manages distributed storage within a single `Dashtable`.
- **Dashtable**: Serves as the primary data structure for storing and retrieving key-value pairs.

Key programming principles:
- **Encapsulation**: Modular design to ensure reusability and separation of concerns.
- **Efficient Memory Management**: Optimized data structures to minimize memory overhead.

---

### Phase 2: Consistent Hashing and Configuration
Phase 2 introduces:
- **Error Handling**: Custom exception classes (`BucketFullException`, `SegmentFullException`) to ensure robust error recovery.
- **Global Configuration Management**: Defines constants (`BUCKET_SIZE`, `SEGMENT_SIZE`) for configurable system behavior.
- **Consistent Hashing Mechanism**:
  - Implements a **Hasher class** to efficiently map keys to segments.
  - Reduces data movement when scaling by maintaining key locality.

---

### Phase 3: Horizontal Scalability via Sharding
Phase 3 enables **sharding** for distributed storage:
- **Partitioning Strategy**: Data is distributed across multiple `Dashtable` instances (shards).
- **Shard Routing**: Uses `std::hash<std::string>` to compute a shard index (`hash_value % noOfShards`).
- **Dynamic Shard Management**: The `Database` class dynamically manages shards for efficient query processing.

Key enhancements:
- **Hash-Based Distribution**: Ensures even distribution of key-value pairs across shards.
- **Modular Shard Management**: Each shard operates independently, facilitating parallelism.

---

### Phase 4: Multi-Threading and Asynchronous Transaction Processing
Phase 4 optimizes concurrency and transaction handling:
- **Dedicated Shard-Level Threading**: Each shard operates in a dedicated thread for parallel transaction processing.
- **Transaction Queueing**: Utilizes `moodycamel::ConcurrentQueue` for lock-free transaction dispatch.
- **Asynchronous Execution**:
  - Uses `std::promise` and `std::future` for non-blocking transaction results.
  - Ensures that read/write operations do not block execution.
- **Transaction Execution Model**:
  - **SubmitTransaction**: Adds operations to a thread-safe queue.
  - **Run Loop**: Continuously dequeues and processes transactions in a dedicated thread.
  - **Graceful Shutdown**: Ensures safe termination of all transaction threads.

Performance improvements:
- **Parallel Query Execution**: Significantly improves throughput in high-concurrency environments.
- **Optimized Synchronization**: Avoids traditional locking mechanisms using a concurrent queue.

---

### Phase 5: Unit Testing with Google Test
Phase 5 introduces **automated testing** to ensure system reliability:
- **Google Test Integration**: Uses `gtest` for unit testing.
- **Test Suite for CRUD Operations**:
  - Validates `Insert` and `Get` operations under various conditions.
  - Ensures consistent correctness under concurrent execution.
- **Build System Integration**:
  - Uses **CMake** for streamlined compilation and dependency management.
  - Supports automated test execution via:
    ```bash
    cmake --build build && ./build/run_tests
    ```

---

## Key System Features
### 1. Sharding for Horizontal Scalability
- **Partitioned Data Storage**: The database is split across multiple independent shards.
- **Efficient Query Routing**: Uses consistent hashing to assign keys to specific shards.

### 2. Multi-Threading and Parallel Processing
- **Dedicated Shard Threads**: Each shard runs its own execution thread for concurrent query execution.
- **Asynchronous Transaction Handling**: Uses `std::future` for non-blocking operations.

### 3. High-Performance Transaction Queue
- **Lock-Free Concurrent Queue**: Uses `moodycamel::ConcurrentQueue` for high-throughput transaction management.
- **Efficient Work Distribution**: Transactions are processed asynchronously without global locks.

### 4. Memory Management and Optimized Synchronization
- **Dynamic Memory Allocation**: Each shard dynamically allocates memory for optimal performance.
- **Minimal Lock Contention**: Transaction queue eliminates the need for expensive locks.

### 5. Automated Testing with Google Test

---

## Installation and Setup

### 1. Clone the Repository
```bash
git clone https://github.com/AtharvaD-coder/Multithreaded-Database.git
cd multithreaded-db
```

### 2. Add Dependencies
- **ConcurrentQueue (MoodyCamel)**
  ```bash
  git submodule add https://github.com/cameron314/concurrentqueue.git libs/concurrentqueue
  git submodule update --init --recursive
  ```
- **Google Test**
  ```bash
  git submodule add https://github.com/google/googletest.git libs/gtest
  git submodule update --init --recursive
  ```

### 3. Build the Project
```bash
cmake -S . -B build
cmake --build build
```

### 4. Run Unit Tests
```bash
./build/run_tests
```

---

## Technical Concepts
### 1. Consistent Hashing
- Distributes keys across segments with minimal data movement during resharding.
- Uses a **hash ring** to determine key placement.

### 2. Lock-Free Concurrent Queue
- Provides high-throughput task processing with **low-latency queueing**.
- Reduces thread contention using a **lock-free multi-producer, multi-consumer model**.

### 3. Thread-Pooling and Parallelism
- Each shard has an independent execution thread.
- Transactions are **batched and processed asynchronously**.
