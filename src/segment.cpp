#include "../include/segment.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;

Segment::Segment(){
    
    int count = 10;
    for (int i = 0; i < count; i++)
    {
        buckets.push_back(new Bucket());
    }
}

void Segment::Insert(string key, string value){
    buckets[0]->Insert(key,value);
}

string Segment::Get(string key){
    return buckets[0]->Get(key);
}

vector<pair<string,string>> Segment::DeleteAll(){
    return buckets[0]->DeleteAll();
}

void Segment::Delete(string key){
    return buckets[0]->Delete(key);
}

void Segment::Display(){
    for (int i = 0; i < buckets.size(); i++) {
        cout << "Bucket " << i << ": ";
        buckets[i]->Display();
    }
}