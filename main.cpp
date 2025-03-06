#include <algorithm>
#include <array>
#include <print>
#include <ranges>
#include <vector>

std::size_t rehash(std::size_t seed, std::size_t hash) {
    seed ^= hash + 0x9e3779b97f4a7c16 + (seed << 6) + (seed >> 2);
    return seed;
}
template <typename T>
std::size_t fullhash(std::size_t seed, const T& key) {
    return rehash(seed, std::hash<T>{}(key));
}

template <typename T, std::size_t size>
std::array<std::size_t, size> createMinimalPerfectHash(const std::array<T, size>& keys) {
    std::array<std::size_t, size> hash_values{};

    // put keys into buckets
    std::array<std::vector<std::string>, size> buckets{};
    for (const auto& key : keys) {
        buckets[fullhash(0, key) % size].push_back(key);
    }

    // sort buckets by size to proccess largest first
    std::ranges::sort(buckets, [](const auto& a, const auto& b) { return a.size() > b.size(); });

    // split buckets into empty slots
    std::array<bool, size> global_slots{};
    std::vector<std::size_t> local_slots{};
    local_slots.reserve(buckets[0].size());
    for (const auto& bucket : buckets) {
        if (bucket.empty()) {
            break;
        }

        local_slots.clear();
        std::size_t d = 0;
        while (local_slots.size() < bucket.size()) {
            auto slot = fullhash(d, bucket[local_slots.size()]) % size;

            if (global_slots[slot] || std::ranges::find(local_slots, slot) != local_slots.end()) {
                d++;
                local_slots.clear();
            } else {
                local_slots.push_back(slot);
            }
        }

        hash_values[fullhash(0, bucket[0]) % size] = d;
        for (const auto slot : local_slots) {
            global_slots[slot] = true;
        }
    }

    return hash_values;
}

template <typename T, std::size_t size>
std::size_t getValueIndex(const std::array<std::size_t, size>& seeds, const T& key) {
    auto hash = std::hash<T>{}(key);
    auto seed = seeds[rehash(0, hash) % seeds.size()];
    return rehash(seed, hash) % seeds.size();
}

int main() {
    std::array<std::string, 11> test_strs = {"hello", "world", "test", "this", "is", "a", "test2", "b", "c", "testing", "words"};
    auto seeds = createMinimalPerfectHash(test_strs);

    for (std::size_t i = 0; i < test_strs.size(); i++) {
        const auto& key = test_strs[i];
        auto index = getValueIndex(seeds, key);
        std::print("key: {}, valueIndex: {}\n", key, index);
    }
    return 0;
}