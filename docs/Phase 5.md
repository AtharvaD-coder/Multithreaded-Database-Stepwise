# Phase 5 Documentation

In **Phase 5**, we introduce **unit testing** to ensure the correctness and reliability of the database. We integrate **Google Test (gtest)** to provide a framework for writing and running tests. The primary focus of this phase is testing CRUD operations, which include **Insert** and **Get** operations in our database.

---

### Key Changes in Phase 5:

- **Google Test Integration**: We added **gtest** as a submodule for testing the system.
- **Testing CRUD Operations**: Created a test suite to validate the core CRUD operations (Insert and Get) on the database.
- **Test Setup**: A new `tests` folder was created, containing the `database.cpp` test file for testing the database operations.
- **Main Program (`main.cpp`)**: Added a simple program to manually test insert operations.
- **CMake Build System**: Introduced `CMakeLists.txt` to manage the project’s build process.
- **Fixed Compilation Error**: Resolved the **default argument error** in `database.cpp` and `database.hpp`.


---

## Overview of Phase 5 Files

### 1. **database.cpp** (Test File)

The `database.cpp` file in the `tests` folder contains the test suite for CRUD operations. The test uses Google Test to verify that the **Insert** and **Get** methods work correctly with the database.

#### Key Features of `database.cpp`:

- **CRUD Operations Testing**: The test case `InsertWithOurDatabase` inserts a set number of records into the database and retrieves one to verify the data.
- **Google Test Framework**: The test framework is integrated using `gtest`. The test is run within the `main` function by initializing Google Test and executing all tests.


#### Key Methods:
- **InsertWithOurDatabase**: A test that inserts `NO_OF_RECORDS` into the database and checks the correctness of retrieving one record.

---

### 2. **Google Test Submodule**

To enable unit testing, we added **Google Test** as a submodule in the project. This allows us to write and run tests with minimal configuration.

#### Steps to Add Google Test:
1. Navigate to your project’s root directory.
2. Add Google Test as a submodule using the following command:
   ```bash
   git submodule add https://github.com/google/googletest.git libs/googletest

#### Step to Build and Run Test:

```bash
cmake --build build && ./build/run_tests
