#include "../src/database.cpp"
#include "../src/shard.cpp"
#include "../src/bucket.cpp"
#include "../src/dashtable.cpp"
#include "../src/hasher.cpp"
#include "../src/segment.cpp"
#include "dashtable.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	Database* db = new Database();
	db->Insert("Atharva", "Desai");

	delete db;
}