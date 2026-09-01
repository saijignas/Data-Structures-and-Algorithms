// Hash map: separate chaining (array of buckets, each a small linked
// list of key-value pairs) + dynamic resizing.
// get/set/delete: O(1) average -- degrades to O(n) if every key hashes
//                 into the same bucket (not defended against here; the
//                 point is demonstrating chaining + resizing, not a
//                 cryptographically-robust hash).
// Resizing:       doubles bucket count and rehashes everything once the
//                 load factor (size / bucket_count) exceeds 0.75, the
//                 same amortized-O(1)-append argument as DynamicArray
//                 applied to the whole table instead of one buffer.
#pragma once

#include <functional>
#include <list>
#include <utility>
#include <vector>

template <typename K, typename V>
class HashMap {
public:
    HashMap() : buckets_(8), size_(0) {}

    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    void set(const K& key, const V& value) {
        std::size_t idx = bucket_index(key, buckets_.size());
        for (auto& kv : buckets_[idx]) {
            if (kv.first == key) {
                kv.second = value;
                return;
            }
        }
        buckets_[idx].emplace_back(key, value);
        ++size_;
        if (load_factor() > 0.75) resize();
    }

    bool get(const K& key, V& out) const {
        std::size_t idx = bucket_index(key, buckets_.size());
        for (const auto& kv : buckets_[idx]) {
            if (kv.first == key) {
                out = kv.second;
                return true;
            }
        }
        return false;
    }

    bool contains(const K& key) const {
        V unused;
        return get(key, unused);
    }

    bool remove(const K& key) {
        std::size_t idx = bucket_index(key, buckets_.size());
        auto& bucket = buckets_[idx];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --size_;
                return true;
            }
        }
        return false;
    }

    std::size_t bucket_count() const { return buckets_.size(); }

private:
    double load_factor() const {
        return static_cast<double>(size_) / static_cast<double>(buckets_.size());
    }

    static std::size_t bucket_index(const K& key, std::size_t bucket_count) {
        return std::hash<K>{}(key) % bucket_count;
    }

    void resize() {
        std::vector<std::list<std::pair<K, V>>> new_buckets(buckets_.size() * 2);
        for (auto& bucket : buckets_) {
            for (auto& kv : bucket) {
                std::size_t idx = bucket_index(kv.first, new_buckets.size());
                new_buckets[idx].emplace_back(kv.first, kv.second);
            }
        }
        buckets_ = std::move(new_buckets);
    }

    std::vector<std::list<std::pair<K, V>>> buckets_;
    std::size_t size_;
};
