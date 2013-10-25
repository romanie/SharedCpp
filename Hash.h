#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

inline int unsigned hash(int key) {
    key += ~(key << 15);
    key ^= (key >> 10);
    key += (key << 3);
    key ^= (key >> 6);
    key += ~(key << 11);
    key ^= (key >> 16);
    return key;
}

inline unsigned int hash(long long key) {
  key += ~(key << 32);
  key ^= (key >> 22);
  key += ~(key << 13);
  key ^= (key >> 8);
  key += (key << 3);
  key ^= (key >> 15);
  key += ~(key << 27);
  key ^= (key >> 31);
  return (unsigned int)(key);
}

inline unsigned int hash(const std::pair<int, int> &p) {
  return hash(((long long)(p.first) << 32) | p.second);
}

inline unsigned int hash(const std::pair<int, long long> &p) {
  return hash(((long long)(p.first) << 32) | hash(p.second));
}

inline unsigned int hash(const std::pair<long long, int> &p) {
  return hash(((long long)(hash(p.first)) << 32) | p.second);
}

inline unsigned int hash(const std::pair<long long, long long> &p) {
  return hash(((long long)(hash(p.first)) << 32) | hash(p.second));
}

template <class Key, class Value, int MaxSize, int Buckets = 1000009>
class HashTable {
  private:
  	int last[Buckets], sz;
  	int pred[MaxSize];
    Key Keys[MaxSize];
    Value Values[MaxSize];
    Value& add(const Key &key, const Value &value) {
      int bucket = hash(key) % Buckets;
      pred[sz] = last[bucket];
      Keys[sz] = key;
      Values[sz] = value;
      last[bucket] = sz;
      sz++;
      return Values[sz - 1];
    }
  public:
    HashTable() : sz(0) {
      memset(last, -1, sizeof(last));
    }
    void reset() {
      memset(last, -1, sizeof(last));
      sz = 0;
    }
  	int find(const Key &key) {
      for (int idx = last[hash(key) % Buckets]; idx >= 0; idx = pred[idx]) {
        if (key == Keys[idx]) {
          return idx;
        }
      }
      return -1;
  	}
    Value& operator[](const Key &key) {
      int id = find(key);
      if (id == -1) return add(key, Value());
      return Values[id];
    }
    int end() const {
      return -1;
    }
    size_t size() const {
      return sz;
    }
    inline const Key& key(int idx) const {
      return Keys[idx];
    }
    inline const Value& value(int idx) const {
      return Values[idx];
    }
    std::vector< Key > keys() const {
      return std::vector< Key >(Keys, Keys + sz);
    }
    std::vector< Value > values() const {
      return std::vector< Value >(Values, Values + sz);
    }
    std::vector< std::pair<Key, Value> > array() const {
      std::vector< std::pair<Key, Value> > result(sz);
      for (int idx = 0; idx < sz; idx++) {
        result[idx].first = Keys[idx];
        result[idx].second = Values[idx];
      }
      return result;
    }
};