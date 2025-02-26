#include "../include/bucket.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;

Bucket::Bucket(){

    slots.resize(10);
}

void Bucket::Insert(string key, string value){
    for(auto &slot : slots){
        if(slot.first.empty()){
            slot.first = key;
            slot.second = value;
            return;
        }
    }
    throw runtime_error("The bucket is full!");
}

string Bucket::Get(string key){
    for(auto &slot : slots){
        if(slot.first == key){
            return slot.second;
        }
    }
    throw runtime_error("Key not found!");
}

vector<pair<string,string>> Bucket::DeleteAll() {
    vector<pair<string,string>> deletedPairs;
    for(auto &slot : slots){
        if(!slot.first.empty()){
            deletedPairs.push_back(slot);
            slot.first = "";
            slot.second = "";
        }
    }
    return deletedPairs;
}

void Bucket::Delete(string key) {
    for(auto &slot : slots){
        if(slot.first == key){
            slot.first = "";
            slot.second = "";
        }
        return;
    }
    throw runtime_error("They key was not found!");
}

void Bucket::Display() {
    for(auto &slot : slots){
        if(!slot.first.empty()){
            cout<<"Key: " << slot.first << "Value: " << slot.second << "\n";
        }
    }

}