#pragma once

#include <array>

#include "hash.h"
#include "internal/phf.h"

namespace phf {

// TODO: add hasher parameter
template <Hashable Key, typename Val, std::size_t keyCount>
class unordered_map {
public:
    using KeyValPair = std::pair<Key, Val>;
    using KeyValArray = std::array<KeyValPair, keyCount>;
    using SeedArray = std::array<std::size_t, keyCount>;

public:
    // TODO: add more constructors
    explicit constexpr unordered_map(const KeyValArray& init)
        : m_hashSeeds(getHashSeeds(init)), m_keyValuePairs(getValues(init, m_hashSeeds)) {}
    constexpr ~unordered_map() = default;

    // TODO: expand interface
    constexpr Val& at(const Key& key) {
        auto index = internal::getIndexFromSeedArray(m_hashSeeds, key);
        if (m_keyValuePairs[index].first != key) {
            throw std::out_of_range("Key does not exist");
        }
        return m_keyValuePairs[index].second;
    }
    constexpr const Val& at(const Key& key) const {
        auto index = internal::getIndexFromSeedArray(m_hashSeeds, key);
        if (m_keyValuePairs[index].first != key) {
            throw std::out_of_range("Key does not exist");
        }
        return m_keyValuePairs[index].second;
    }

    constexpr KeyValArray::iterator begin() noexcept { return m_keyValuePairs.begin(); }
    constexpr KeyValArray::iterator end() noexcept { return m_keyValuePairs.end(); }
    constexpr KeyValArray::const_iterator begin() const noexcept { return m_keyValuePairs.begin(); }
    constexpr KeyValArray::const_iterator end() const noexcept { return m_keyValuePairs.end(); }
    constexpr KeyValArray::const_iterator cbegin() const noexcept { return m_keyValuePairs.cbegin(); }
    constexpr KeyValArray::const_iterator cend() const noexcept { return m_keyValuePairs.cend(); }

private:
    static constexpr SeedArray getHashSeeds(const KeyValArray& init) {
        std::array<Key, keyCount> keys{};
        std::ranges::transform(init, keys.begin(), [](const auto& pair) { return pair.first; });
        return internal::constructPhfSeedArray<Key, keyCount>(keys);
    }
    // TODO: key-value pairs could be created while constructing seeds
    static constexpr KeyValArray getValues(const KeyValArray& init, const SeedArray& seeds) {
        KeyValArray values{};
        for (const auto& pair : init) {
            auto index = internal::getIndexFromSeedArray(seeds, pair.first);
            values[index] = pair;
        }
        return values;
    }

    SeedArray m_hashSeeds;
    KeyValArray m_keyValuePairs;
};
} // namespace phf