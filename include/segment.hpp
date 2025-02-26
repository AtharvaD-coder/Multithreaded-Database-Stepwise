#pragma once
#include <string>
#include <vector>
#include "bucket.hpp"
using namespace std;

class Segment {

    vector<Bucket*> buckets;
    
    public:

    Segment();

    void Insert(string key, string value);
    string Get(string key);
    vector<pair<string,string>> DeleteAll();
    void Delete(string key);
    void Display();


};