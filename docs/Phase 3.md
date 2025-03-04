# Phase 3 Documentation

In **Phase 3**, we enhance the key-value store by introducing **sharding** to distribute the data across multiple independent storage systems (shards). This enables horizontal scalability and improves the overall system's performance. The entire database is broken into several shards, and each shard has its own single Dashtabl

---

## Overview of Phase 3 Files

### 1. **database.hpp**

The `database.hpp` file defines the `Database` class, which manages multiple **shards**. Each shard is essentially a separate `Dashtable` instance, which can be independently managed and scaled. The class allows interaction with these shards using the basic operations: `Get`, `Insert`, and `Delete`.

#### Key Features of the `Database` Class:

- **Sharding**: The `Database` class creates multiple shards (each represented by a `Dashtable`) to distribute the data. The number of shards is specified during the initialization.
- **Shard Management**: Each shard is a separate instance of a `Dashtable`, which means that data is partitioned across multiple `Dashtable` objects, allowing the database to scale horizontally.
- **Hash Function**: A simple hash function (`std::hash<string>`) is used to compute the shard index for a given key. This ensures that each key is distributed to one of the shards based on its hash value.

#### Key Methods:

- **Database Constructor**: 
  - Initializes a vector of `Dashtable` pointers, creating `noOfShards` number of shards.
  - Each `Dashtable` is responsible for a partition of the key-value pairs.

- **Get**:
  - Given a `key`, computes the shard index using the hash function, and then delegates the call to the corresponding `Dashtable`'s `Get` method.

- **Put**:
  - Similar to `Get`, computes the shard index for the given key and delegates the `Insert` operation to the appropriate shard's `Insert` method.

- **Delete**:
  - Deletes a key-value pair from the appropriate shard based on the computed shard index.

- **Destructor**: 
  - Cleans up dynamically allocated memory for all `Dashtable` instances in the `shards` vector.

---

### 2. **database.cpp**

The `database.cpp` file defines the implementation of the methods declared in `database.hpp`. Here's a deeper look at each function:

- **Database Constructor**:  
  - The constructor accepts `noOfShards`, which specifies how many shards (or `Dashtable` instances) will be used in the database.
  - It initializes a vector of pointers to `Dashtable` objects. Each `Dashtable` instance is dynamically allocated to handle a partition of the key-value data.
  
- **Get Method**:  
  - This method calculates the hash of the key using `std::hash<string>` and uses the modulus operation (`% noOfShards`) to determine which shard (or `Dashtable`) should handle the request.
  - The method then delegates the `Get` call to the appropriate `Dashtable`.

- **Put Method**:  
  - Similar to the `Get` method, `Insert` calculates the shard index for the key and calls the `Insert` method of the corresponding `Dashtable` to insert the key-value pair.

- **Delete Method**:  
  - The `Delete` method uses the same hashing technique to determine which shard contains the key. It then delegates the deletion to the appropriate `Dashtable`.

- **Destructor**:  
  - The destructor cleans up the dynamically allocated `Dashtable` instances in the `shards` vector, ensuring that the memory is properly freed when the `Database` object is destroyed.

---

## Technical Concepts Introduced in Phase 3

### 1. **Sharding**
Sharding is a technique used to horizontally scale a system by distributing the data across multiple independent storage units (in this case, `Dashtable` instances). Each shard holds a partition of the data, which helps distribute the load and improve performance.

#### How Sharding Works:
- **Sharding by Key**: When a key-value pair is inserted or accessed, a hash function computes which shard (or partition) will store the data based on the key. The key-value pair is then routed to the corresponding shard.
- **Shard Index**: The shard to which a key belongs is determined using the hash of the key and the modulus operator (`%`). This ensures that the data is distributed evenly across the shards.

### 2. **Hash Function for Sharding**
In Phase 3, a simple hash function (`std::hash<string>`) is used to compute the hash value of a string key. The hash value is then mapped to a shard by calculating the shard index as `hash_value % noOfShards`. This ensures a pseudo-random but deterministic distribution of keys across the available shards.

### 3. **Dynamic Memory Management**
The `Database` class uses dynamic memory allocation to manage the `Dashtable` objects that form each shard. This allows the system to scale by adding or removing shards as needed, without changing the underlying architecture. The destructor ensures that all dynamically allocated memory is properly cleaned up when the database object is destroyed.

### 4. **Vector of Pointers**
The `Database` class uses a vector of pointers to `Dashtable` instances to represent the shards. This allows the class to easily manage the collection of shards and allocate or deallocate memory for each shard independently.

### 5. **Destruction of Dynamic Memory**
The destructor of the `Database` class is responsible for cleaning up the memory allocated for each shard. It iterates over the `shards` vector, deleting each `Dashtable` instance and then clearing the vector to prevent memory leaks.

---
