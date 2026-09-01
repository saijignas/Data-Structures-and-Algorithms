#include <string>

#include "../include/data_structures/hash_map.h"
#include "../include/test_framework.h"

TEST_CASE("hash map: set then get returns the value") {
    HashMap<std::string, int> map;
    map.set("a", 1);
    map.set("b", 2);
    int out = 0;
    CHECK(map.get("a", out) && out == 1);
    CHECK(map.get("b", out) && out == 2);
}

TEST_CASE("hash map: get on missing key returns false") {
    HashMap<std::string, int> map;
    int out = 0;
    CHECK(!map.get("missing", out));
}

TEST_CASE("hash map: set on existing key overwrites, doesn't grow size") {
    HashMap<std::string, int> map;
    map.set("a", 1);
    map.set("a", 2);
    int out = 0;
    CHECK(map.size() == 1);
    CHECK(map.get("a", out) && out == 2);
}

TEST_CASE("hash map: remove deletes the key") {
    HashMap<std::string, int> map;
    map.set("a", 1);
    CHECK(map.remove("a"));
    CHECK(!map.contains("a"));
    CHECK(map.size() == 0);
}

TEST_CASE("hash map: remove on missing key returns false") {
    HashMap<std::string, int> map;
    CHECK(!map.remove("missing"));
}

TEST_CASE("hash map: resizes as elements are added") {
    HashMap<int, int> map;
    std::size_t initial_buckets = map.bucket_count();
    for (int i = 0; i < 100; ++i) map.set(i, i * i);
    CHECK(map.bucket_count() > initial_buckets);
    for (int i = 0; i < 100; ++i) {
        int out = 0;
        CHECK(map.get(i, out) && out == i * i);
    }
}

TEST_CASE("hash map: empty map has size 0") {
    HashMap<std::string, int> map;
    CHECK(map.empty());
    CHECK(map.size() == 0);
}
