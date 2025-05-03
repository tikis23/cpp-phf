#include <gtest/gtest.h>

#include <phf/hash.h>

TEST(HashTest, EqualKeyEqualValueEqualHash) {
    ASSERT_EQ(phf::hash<int>{}(0, 1), phf::hash<int>{}(0, 1));
    ASSERT_EQ(phf::hash<std::string_view>{}(1592, "TEST_STRING"), phf::hash<std::string_view>{}(1592, "TEST_STRING"));
}
