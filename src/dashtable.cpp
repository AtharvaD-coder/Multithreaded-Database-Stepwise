#include "../include/dashtable.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;

Dashtable::Dashtable(){

    segments.push_back(new Segment());
}

void Dashtable::Insert(string key, string value){
    segments[0]->Insert(key,value);
}

string Dashtable::Get(string key){
    return segments[0]->Get(key);
}

vector<pair<string,string>> Dashtable::DeleteAll(){
    return segments[0]->DeleteAll();
}

void Dashtable::Delete(string key){
    return segments[0]->Delete(key);
}

void Dashtable::Display(){
    for (int i = 0; i < segments.size(); i++) {
        cout << "Segment " << i << ": ";
        segments[i]->Display();
    }
}