#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

class BucketFullException : public exception {
    private:
    string message;

    public:
    BucketFullException(const string& msg) : message(msg){}
    BucketFullException() : message("Bucket is full!") {}
    const char* what() const noexcept override { return message.c_str(); }
};

class SegmentFullException : public exception {
    private:
        std::string message;
    public:
        SegmentFullException(const string& msg) : message(msg) {}
        SegmentFullException() : message("Segment is full!") {}
        const char* what() const noexcept override { return message.c_str(); }
    };