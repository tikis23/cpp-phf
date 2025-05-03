#include <gtest/gtest.h>

#include <algorithm>
#include <phf/unordered_set.h>
#include <ranges>

constexpr auto arr1 = std::array{1, 2, 3, 4, 5};
constexpr auto arr2 = std::array{5, 4, 3, 2, 1};
constexpr auto arr3 = std::array{-1, -2, -3};
constexpr auto arr4 = std::array{1, 2, 3, 4, 666};
constexpr auto set1 = phf::make_unordered_set<int>(arr1);
constexpr auto set2 = phf::make_unordered_set<int, 15.0>(arr2);
constexpr auto set3 = phf::make_unordered_set<int, 4.5>(arr3);
constexpr auto set4 = phf::make_unordered_set<int>(arr4);

TEST(UnorderedSetTest, SizeZero) {
    constexpr phf::unordered_set<int, 0> set({});
    ASSERT_EQ(set.size(), 0);
    ASSERT_EQ(set.max_size(), 0);
    ASSERT_TRUE(set.empty());
}

TEST(UnorderedSetTest, MemoryOverhead) {
    ASSERT_EQ(set1.size(), 5);
    ASSERT_EQ(set1.max_size(), 5);
    ASSERT_EQ(set2.size(), 5);
    ASSERT_EQ(set2.max_size(), 75);
}

TEST(UnorderedSetTest, ContainsValue) {
    for (const auto& val : arr1) {
        ASSERT_EQ(set1.count(val), 1);
        ASSERT_NE(set1.find(val), set1.end());
        ASSERT_TRUE(set1.contains(val));
    }
    for (const auto& val : arr3) {
        ASSERT_EQ(set3.count(val), 1);
        ASSERT_NE(set3.find(val), set3.end());
        ASSERT_TRUE(set3.contains(val));
    }
}

TEST(UnorderedSetTest, NotContainsValue) {
    for (const auto& val : arr3) {
        ASSERT_EQ(set1.count(val), 0);
        ASSERT_EQ(set1.find(val), set1.end());
        ASSERT_FALSE(set1.contains(val));
    }
    for (const auto& val : arr1) {
        ASSERT_EQ(set3.count(val), 0);
        ASSERT_EQ(set3.find(val), set3.end());
        ASSERT_FALSE(set3.contains(val));
    }
}

TEST(UnorderedSetTest, Iteration) {
    for (const auto& val : set1) {
        ASSERT_TRUE(std::ranges::contains(arr1, val));
    }
    for (const auto& val : arr1) {
        ASSERT_TRUE(std::ranges::contains(set1, val));
    }
}

TEST(UnorderedSetTest, EqualRange) {
    auto range = set1.equal_range(1);
    ASSERT_EQ(range.first, set1.find(1));

    std::size_t elCount = 0;
    for (auto it = range.first; it != range.second; ++it) {
        ASSERT_EQ(*it, 1);
        ++elCount;
    }
    ASSERT_EQ(elCount, 1);

    range = set1.equal_range(15);
    ASSERT_EQ(range.first, set1.end());
    ASSERT_EQ(range.second, set1.end());
}

TEST(UnorderedSetTest, EqualRangeWithMemoryOverhead) {
    auto range = set2.equal_range(2);
    ASSERT_EQ(range.first, set2.find(2));

    std::size_t elCount = 0;
    for (auto it = range.first; it != range.second; ++it) {
        ASSERT_EQ(*it, 2);
        ++elCount;
    }
    ASSERT_EQ(elCount, 1);

    range = set2.equal_range(15);
    ASSERT_EQ(range.first, set2.end());
    ASSERT_EQ(range.second, set2.end());
}

TEST(UnorderedSetTest, OperatorEqual) {
    ASSERT_EQ(set1, set1);
    ASSERT_EQ(set1, set2);
    ASSERT_NE(set1, set4);
}