#include "../src/database.cpp"
#include "../src/shard.cpp"
#include "../src/dashtable.cpp"
#include "../src/bucket.cpp"
#include "../src/hasher.cpp"
#include "../src/segment.cpp"
#include <gtest/gtest.h>
#include <string>
#include <iostream>

int NO_OF_RECORDS = 10;

TEST(CrudOperations, InsertWithOurDatabase) {
    Database db(10);
    std::cout << "Inserting " << NO_OF_RECORDS << " records in Database" << std::endl;
    for (int i = 0; i < NO_OF_RECORDS; ++i) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        db.Insert(key, value);
    }
    std::cout << "Retrieving record 'key5'" << std::endl;
    std::cout << "Value: " << db.Get("key5") << std::endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
