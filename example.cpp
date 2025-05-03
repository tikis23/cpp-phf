#include <print>

#include <phf/unordered_map.h>
#include <phf/unordered_set.h>

#include <algorithm>
#include <ranges>

int main() {
    // map
    constexpr phf::unordered_map<int, int, 5, 4.0> map({
        std::pair{1, 1},
        {2, 2},
        {3, 3},
        {4, 4},
        {5, 5},
    });
    static constinit phf::unordered_map<int, int, 5, 4.0> map2(map);

    std::print("Map empty: {}\n", map.empty());
    std::print("Map size: {}\n", map.size());
    std::print("Map max size: {}\n", map.max_size());
    
    map2.at(1) = 100;
    try {
        map2.at(-1);
    } catch (const std::out_of_range& e) {
        std::print("    Exception: {}\n", e.what());
    }
    std::print("Range-based for loop:\n");
    for (auto& p : map2) {
        // p.second = 0; // can modify value
        std::print("    {}: {}\n", p.first, p.second);
    }

    // set
    constexpr phf::unordered_set<int, 5, 4.0> set({1, 2, 3, 4, 5});

    std::print("Set empty: {}\n", set.empty());
    std::print("Set size: {}\n", set.size());
    std::print("Set max size: {}\n", set.max_size());
    std::print("Range-based for loop:\n");
    for (auto& p : set) {
        std::print("    {}\n", p);
    }
    std::print("Contains 3: {}\n", set.contains(3));
    std::print("Contains 6: {}\n", std::ranges::contains(set, 6));

    constexpr auto set2 = phf::make_unordered_set<int, 1.0>(std::array{5, 4, 3, 2, 1});
    std::print("Sets equal: {}\n", set == set2);
}