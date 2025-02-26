#pragma once
#include "../include/segment.hpp"
#include <string>
#include <vector>
using namespace std;

class Dashtable {
    vector<Segment*> segments;

    public:

    Dashtable();

    void Insert(string key, string value);
    string Get(string key);
    vector<pair<string,string>> DeleteAll();
    void Delete(string key);
    void Display();
};