
## PHASE 1

In Phase 1, we create the basic components from the bottom up: **slot → bucket → segment → dashtable**.

A **dashtable** contains several **segments** (a vector of segments), and each **segment** contains several **buckets** (a vector of buckets).

---

### Step 1: Create the Bucket Files

1. **Bucket.hpp**:  
   The `Bucket.hpp` file defines the `Bucket` class, which represents a container for storing key-value pairs using a fixed-size vector of `pair<string, string>` called `slots`. The `slots` vector is **private** (This is encapsulation).

2. **Bucket.cpp**:  
   The `Bucket.cpp` file defines the member functions of the `Bucket` class. The constructor initializes the `slots` vector with 10 empty pairs.

---

### Step 2: Create the Segment Files

1. **Segment.hpp**:  
   The `Segment.hpp` file defines a class `Segment`, which represents a collection of `Bucket` objects managed in a vector of `Bucket*` pointers (`vector<Bucket*> buckets`). The class provides methods to interact with these buckets, such as `Insert`, `Get`, and `Delete`, allowing insertion, retrieval, and deletion of key-value pairs in the buckets. It also includes a `DeleteAll` method that deletes all entries and returns the deleted key-value pairs, and a `print` method to display the contents of the segment.

   The class makes use of **dynamic memory management** (with pointers to `Bucket`), **object-oriented principles** (encapsulation through methods), and **standard library containers** like `vector` to manage a collection of objects efficiently.

2. **Segment.cpp**:  
   The `Segment.cpp` file defines the member functions for the `Segment` class, utilizing delegation to the `Bucket` class's methods to perform operations.

---

### Step 3: Create the Dashtable Files

1. **Dashtable.hpp** and **Dashtable.cpp**:  
   The final part of Phase 1 is creating the `Dashtable.hpp` and `Dashtable.cpp` files, which integrate the `Bucket` and `Segment` classes into a more complete structure for the key-value store. The `Dashtable` class contains several `Segment` objects and will manage them accordingly.

---

## Phase 1 Summary

In the first phase, we built the basic storage primitives (**Bucket**, **Segment**, **Dashtable**) as a single-threaded key-value store.

---

## Significant Concepts and Unique Terms Introduced in Phase 1

1. **Object-Oriented Programming**: Using classes and objects to organize and structure the code.
2. **Pointers**: Managing memory through direct references to locations in memory.
3. **Encapsulation**: Restricting access to certain components of the object (e.g., private fields in `Bucket`).
4. **Dynamic Memory Management**: Using pointers to allocate and manage memory for the `Bucket` and `Segment` objects.
5. **Standard C++ Libraries**: Utilizing libraries like `vector` to manage collections of objects.
6. **`vector<pair<string, string>>`, `auto`**: Using C++ standard containers and `auto` keyword for type inference.
7. **Scope Resolution Operator (`::`)**: Used to define the scope of methods in classes, especially for defining methods outside of the class definition.

