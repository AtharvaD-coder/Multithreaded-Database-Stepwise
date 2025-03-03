# Phase 2 Documentation

In **Phase 2**, we continue the development of our key-value store system, building on the foundations from **Phase 1**. In this phase, we focus on adding more advanced features such as **error handling**, **global configuration constants**, and **consistent hashing** to distribute key-value pairs across segments.

---

## Overview of Phase 2 Files

### 1. **errors.hpp**

The `errors.hpp` file defines two exceptions used for handling errors in the key-value store:

- **BucketFullException**: Thrown when a `Bucket` is full and cannot accommodate more key-value pairs.
- **SegmentFullException**: Thrown when a `Segment` reaches its capacity and cannot hold any more `Buckets`.

#### Why Use Exceptions?
In C++, exceptions are used for error handling. This allows us to separate the logic of handling errors from the core business logic of our program, making it easier to manage and debug.

---

### 2. **globals.hpp**

The `globals.hpp` file defines several global configuration constants used throughout the project. These constants control the behavior of the `Bucket`, `Segment`, and `Dashtable`:

- `BUCKET_SIZE`: Defines the maximum number of key-value pairs that can be stored in a `Bucket`.
- `SEGMENT_SIZE`: Defines the number of `Buckets` that a `Segment` can contain. In Phase 2, it’s set to `1`, meaning each `Segment` starts with just one `Bucket`.
- `SLOT_SIZE`: Defines the size of each `Bucket` (i.e., the number of slots available for key-value pairs).
- `MAX_RING_SIZE`: The maximum size of the hash ring. This is typically set to the maximum integer value (`__INT_MAX__`), which represents the theoretical upper limit for the number of segments.

#### Why Use Global Configuration Constants?
Global configuration constants provide a centralized place to manage and modify the behavior of the key-value store. They allow us to easily adjust key parameters (such as the number of slots per `Bucket`) without needing to modify multiple parts of the codebase.

---

### 3. **hasher.hpp**

The `hasher.hpp` file defines the `Hasher` class, which is responsible for performing **consistent hashing**. This class helps us distribute key-value pairs across multiple `Segments` efficiently.

#### Key Features of the `Hasher` Class:

- **Ring Representation**: The `Hasher` class manages a ring, which is a vector of pairs, where each pair consists of a hash value and a pointer to a `Segment`.
- **Hash Function**: The `HashFunction` method generates a hash value for a given key. This hash value determines where the key-value pair should be stored in the ring of segments.
- **GetElement**: This method retrieves the appropriate `Segment` for a given key by using the hash value of the key and finding the corresponding segment in the sorted ring.
- **AddElement**: Adds a new `Segment` to the ring by computing a new hash value based on the current size of the ring.
- **RehashHelper**: When the system becomes overloaded, the `RehashHelper` method helps to rebalance the segments by splitting an existing segment into two and recalculating their hash values.
- **sortRing**: This method ensures that the `ring` of segments is always sorted by hash values, enabling efficient lookups using binary search.

#### Why Use Consistent Hashing?
Consistent hashing is a technique used in distributed systems to efficiently distribute data across a fixed number of nodes (or in this case, segments). The key idea behind consistent hashing is that each key is hashed to a point on a circular "hash ring". This allows the system to easily add or remove nodes (segments) without rebalancing the entire dataset.

### Key Concepts Explained in the `Hasher` Class:

- **Consistent Hashing**: 
  Consistent hashing ensures that when a new segment is added or removed, only a small portion of the keys need to be redistributed. This is particularly important in systems where scalability and fault tolerance are key concerns.
  
- **Ring**:
  The ring is a circular structure used to represent the key space. Each segment is represented by a point on this ring. When we hash a key, we can easily find the corresponding segment by locating the hash value on the ring.

- **Rehashing**:
  Rehashing refers to the process of redistributing keys among segments. This may be necessary when the number of segments changes, or when the system needs to balance the load across all segments. Rehashing allows the system to scale efficiently.

---

### 4. **hasher.cpp**

The `hasher.cpp` file defines the implementation of the methods declared in `hasher.hpp`. Here’s a deeper look at each function:

- **Hasher Constructor**:  
  Initializes the `Hasher` by adding `SEGMENT_SIZE` segments to the ring. It then sorts the ring to ensure that the segments are ordered by their hash values.

- **GetElement**:  
  This method retrieves the appropriate segment for a given key. It first computes the hash value for the key, then uses `lower_bound` to find the correct segment in the sorted ring. If no matching segment is found (i.e., the key hash is greater than any existing segment’s hash), it wraps around and returns the first segment in the ring.

- **AddElement**:  
  Adds a new segment to the ring. The new segment’s hash value is determined by the current size of the ring. This method helps to scale the system by adding more segments as needed.

- **RehashHelper**:  
  This method handles rehashing. It calculates a new hash value (a "mid-point") between two existing segments and inserts a new segment at that point on the ring. This helps to balance the load between adjacent segments.

- **sortRing**:  
  Sorts the ring of segments by their hash values, ensuring that the key-value pairs are distributed correctly across the segments.

---

## Technical Concepts Introduced in Phase 2

### 1. **Consistent Hashing**
Consistent hashing is a fundamental technique used to distribute data evenly across multiple nodes (or segments in our case). The key benefit of consistent hashing is that it minimizes the number of keys that need to be redistributed when adding or removing segments.

#### How Consistent Hashing Works:
1. **Hashing the Key**: A key is hashed to a value in the range of the hash function.
2. **Hash Ring**: This hash value is mapped onto a circular "hash ring" where each segment (or node) is also assigned a hash value.
3. **Mapping a Key to a Segment**: To find the appropriate segment for a given key, we locate the key’s hash value on the ring and then find the nearest segment in the clockwise direction. This segment is responsible for storing the key-value pair.

### 2. **Rehashing**
Rehashing is the process of recalculating the hash values for keys and redistributing them across segments. This typically happens when segments are added or removed from the ring. Rehashing ensures that the data is evenly distributed across the available segments.

### 3. **Dynamic Memory Management with Pointers**
The `Hasher` class uses dynamic memory management by allocating memory for `Segment` objects using `new`. This allows for flexible, on-demand creation of new segments, which is essential for scaling the key-value store.

### 4. **size_t**
`size_t` is an unsigned integer type that is typically used to represent the size of an object or an index in an array or vector. It's designed to be large enough to accommodate the maximum size of any object in memory.

### 5. **tuple**
A tuple is a fixed-size collection of heterogeneous elements, meaning it can hold values of different types. In the Hasher class, a tuple<Segment*, size_t, size_t> is used to return multiple values from the GetElement function.

### 6. **static_cast**
static_cast is a C++ operator that performs an explicit conversion between compatible types. In the GetElement method, static_cast is used to cast a pointer type to another compatible pointer type.

### 7. **hash<string>**
hash<string> is a C++ standard library function that generates a hash value for a given string. It uses a hash function to convert a string into a size_t hash value, which can then be used to index into a hash table or in our case, the hash ring.