#pragma once
#include <string>
#include <vector>
using namespace std;

class Bucket {

    vector<pair<string,string>> slots;

    public:

    Bucket();

    void Insert(string key, string value);
    string Get(string key);
    vector<pair<string,string>> DeleteAll();
    void Delete(string key);
    void Display();
};