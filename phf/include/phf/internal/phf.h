#pragma once

#include <algorithm>
#include <array>
#include <vector>

#include "../hash.h"

namespace phf::internal {
template <Hashable T, std::size_t size>
constexpr std::array<std::size_t, size> constructPhfSeedArray(const std::array<T, size>& keys) {
    // TODO: check if there are duplicate keys

    std::array<std::size_t, size> hash_values{};

    // put keys into buckets
    std::array<std::vector<T>, size> buckets{};
    for (const auto& key : keys) {
        buckets[hash<T>{}(0, key) % size].push_back(key);
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
            auto slot = hash<T>{}(d, bucket[local_slots.size()]) % size;

            if (global_slots[slot] || std::ranges::find(local_slots, slot) != local_slots.end()) {
                d++;
                local_slots.clear();
            } else {
                local_slots.push_back(slot);
            }
        }

        hash_values[hash<T>{}(0, bucket[0]) % size] = d;
        for (const auto slot : local_slots) {
            global_slots[slot] = true;
        }
    }

    return hash_values;
}

template <typename T, std::size_t size>
constexpr std::size_t getIndexFromSeedArray(const std::array<std::size_t, size>& seeds, const T& key) {
    auto startingHash = hash<T>{}(0, key) % seeds.size();
    auto seed = seeds[startingHash];
    return seed == 0 ? startingHash : hash<T>{}(seed, key) % seeds.size();
}
} // namespace phf::internal