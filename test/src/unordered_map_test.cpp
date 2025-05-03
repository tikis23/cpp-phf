#include <gtest/gtest.h>

#include <algorithm>
#include <phf/unordered_map.h>
#include <ranges>

constexpr auto arr1 = std::array{
    std::pair{1, 10},
    std::pair{2, 20},
    std::pair{3, 30},
    std::pair{4, 40},
    std::pair{5, 50}
};
constexpr auto arr2 = std::array{
    std::pair{5, 50},
    std::pair{4, 40},
    std::pair{3, 30},
    std::pair{2, 20},
    std::pair{1, 10}
};
constexpr auto arr3 = std::array{
    std::pair{-1, -10},
    std::pair{-2, -20},
    std::pair{-3, -30}
};
constexpr auto arr4 = std::array{
    std::pair{  1,   10},
    std::pair{  2,   20},
    std::pair{  3,   30},
    std::pair{  4,   40},
    std::pair{666, 6660}
};
constexpr auto map1 = phf::make_unordered_map<int, int>(arr1);
constexpr auto map2 = phf::make_unordered_map<int, int, 15.0>(arr2);
constexpr auto map3 = phf::make_unordered_map<int, int, 4.5>(arr3);
constinit auto map4 = phf::make_unordered_map<int, int>(arr4);

TEST(UnorderedMapTest, SizeZero) {
    constexpr phf::unordered_map<int, int, 0> map({});
    ASSERT_EQ(map.size(), 0);
    ASSERT_EQ(map.max_size(), 0);
    ASSERT_TRUE(map.empty());
}

TEST(UnorderedMapTest, MemoryOverhead) {
    ASSERT_EQ(map1.size(), 5);
    ASSERT_EQ(map1.max_size(), 5);
    ASSERT_EQ(map2.size(), 5);
    ASSERT_EQ(map2.max_size(), 75);
}

TEST(UnorderedMapTest, AtReturnsValid) {
    for (const auto& [key, val] : arr1) {
        ASSERT_EQ(map1.at(key), val);
    }
}

TEST(UnorderedMapTest, AtThrows) {
    ASSERT_THROW(map1.at(-1111), std::out_of_range);
}

TEST(UnorderedMapTest, AtModifiesValue) {
    ASSERT_EQ(map4.at(1), 10);
    map4.at(1) = 100;
    ASSERT_EQ(map4.at(1), 100);
}

TEST(UnorderedMapTest, ContainsKey) {
    for (const auto& [key, val] : arr1) {
        ASSERT_EQ(map1.count(key), 1);
        ASSERT_NE(map1.find(key), map1.end());
        ASSERT_TRUE(map1.contains(key));
    }
    for (const auto& [key, val] : arr3) {
        ASSERT_EQ(map3.count(key), 1);
        ASSERT_NE(map3.find(key), map3.end());
        ASSERT_TRUE(map3.contains(key));
    }
}

TEST(UnorderedMapTest, NotContainsKey) {
    for (const auto& [key, val] : arr3) {
        ASSERT_EQ(map1.count(key), 0);
        ASSERT_EQ(map1.find(key), map1.end());
        ASSERT_FALSE(map1.contains(key));
    }
    for (const auto& [key, val] : arr1) {
        ASSERT_EQ(map3.count(key), 0);
        ASSERT_EQ(map3.find(key), map3.end());
        ASSERT_FALSE(map3.contains(key));
    }
}

TEST(UnorderedMapTest, Iteration) {
    for (const auto& v : map1) {
        ASSERT_TRUE(std::ranges::contains(arr1, v));
    }
    for (const auto& v : arr1) {
        ASSERT_TRUE(std::ranges::contains(map1, v));
    }
}

TEST(UnorderedMapTest, EqualRange) {
    auto range = map1.equal_range(1);
    ASSERT_EQ(range.first, map1.find(1));

    std::size_t elCount = 0;
    for (auto it = range.first; it != range.second; ++it) {
        ASSERT_EQ(it->first, 1);
        ASSERT_EQ(it->second, 10);
        ++elCount;
    }
    ASSERT_EQ(elCount, 1);

    range = map1.equal_range(15);
    ASSERT_EQ(range.first, map1.end());
    ASSERT_EQ(range.second, map1.end());
}

TEST(UnorderedMapTest, EqualRangeWithMemoryOverhead) {
    auto range = map2.equal_range(2);
    ASSERT_EQ(range.first, map2.find(2));

    std::size_t elCount = 0;
    for (auto it = range.first; it != range.second; ++it) {
        ASSERT_EQ(it->first, 2);
        ASSERT_EQ(it->second, 20);
        ++elCount;
    }
    ASSERT_EQ(elCount, 1);

    range = map2.equal_range(15);
    ASSERT_EQ(range.first, map2.end());
    ASSERT_EQ(range.second, map2.end());
}

TEST(UnorderedMapTest, OperatorEqual) {
    ASSERT_EQ(map1, map1);
    ASSERT_EQ(map1, map2);
    ASSERT_NE(map1, map4);
}