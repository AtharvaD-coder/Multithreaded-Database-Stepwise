#include "../include/hasher.hpp"
#include "../include/globals.hpp"
#include "../include/segment.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <utility>
using namespace std;

Hasher::Hasher(vector<pair<size_t, Segment*>>& vec) : ring(vec) {
    // Start with one segment in the ring.
    for (size_t i = 0; i < SEGMENT_SIZE; i++) {
        AddElement();
    }
    sortRing();
}

tuple<Segment*, size_t, size_t> Hasher::GetElement(string key) {
    if (ring.empty()) {
        throw std::runtime_error("No Segments available");
    }
    size_t hashValue = HashFunction(key);
    auto it = lower_bound(ring.begin(), ring.end(),
                          make_pair(hashValue, static_cast<Segment*>(nullptr)),
                          [](const pair<size_t, Segment*>& a,
                             const pair<size_t, Segment*>& b) {
                              return a.first < b.first;
                          });
    if (it == ring.end()) {
        return {ring.front().second, 0, ring.front().first};
    }
    size_t index = distance(ring.begin(), it);
    return {it->second, index, it->first};
}

void Hasher::AddElement() {
    size_t hashValue = HashFunction(to_string(ring.size()));
    ring.push_back(make_pair(hashValue, new Segment()));
}

size_t Hasher::HashFunction(string key) const {
    hash<string> hash_fn;
    size_t hashValue = hash_fn(key);
    return (hashValue % MAX_RING_SIZE);
}

void Hasher::RehashHelper(size_t segmentIndex) {
    // Simplified rehashing: compute a mid-point hash value.
    long long currentElementHashValue = ring[segmentIndex].first;
    long long prevElementHashValue = (segmentIndex == 0 ? 0 : ring[segmentIndex - 1].first);
    long long midhashValue = prevElementHashValue + ((currentElementHashValue - prevElementHashValue) / 2);
    ring.insert(ring.begin() + segmentIndex, make_pair(midhashValue, new Segment()));
}

void Hasher::sortRing() {
    sort(ring.begin(), ring.end(),
              [](const pair<size_t, Segment*>& a,
                 const pair<size_t, Segment*>& b) {
                  return a.first < b.first;
              });
}
