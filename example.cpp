#include <print>

#include <phf/unordered_map.h>

int main() {
    constexpr phf::unordered_map<std::string_view, int, 3> map({
        std::pair{  "one", 1}, // Doesn't deduce without explicit std::pair. TODO: find a fix
        {  "two", 2},
        {"three", 3},
    });

    static constinit phf::unordered_map<std::string_view, int, 3> mapModifiable(map);

    std::print("Range-based for loop:\n");
    for (const auto& p : map) {
        std::print("    {}: {}\n", p.first, p.second);
    }

    std::print("at():\n");
    std::print("    one: {}\n", map.at("one"));

    std::print("at() modification:\n");
    std::print("    two: {}\n", mapModifiable.at("two"));
    mapModifiable.at("two") = 25;
    std::print("    two: {}\n", mapModifiable.at("two"));

    return 0;
}