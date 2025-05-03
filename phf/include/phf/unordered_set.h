#pragma once

#include <array>
#include <functional>

#include "hash.h"
#include "internal/phf.h"

namespace phf {

template <typename Key, std::size_t KeyCount, double MemoryOverheadScale = 1.0, typename Hash = phf::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>
    requires(MemoryOverheadScale >= 1.0)
class unordered_set {
private:
    static constexpr inline auto ArrSize = internal::sizeWithMemoryOverhead<KeyCount, MemoryOverheadScale>;

public:
    using key_type = Key;
    using value_type = Key;
    using size_type = std::size_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using const_iterator = internal::SparseIterator<value_type, ArrSize, true>;

private:
    using init_arr = std::array<value_type, KeyCount>;
    using value_arr = std::array<value_type, ArrSize>;
    using jump_arr = std::array<internal::IteratorJumpType, ArrSize>;

public:
    constexpr unordered_set(hash_seed_type startingSeed, const init_arr& init)
        : m_seed(internal::getSeed<value_type, KeyCount, MemoryOverheadScale, hasher, key_equal>(startingSeed, init)),
          m_valueArray(internal::initValueArray<init_arr, value_arr, hasher>(m_seed, init)),
          m_jumpArray(internal::initJumpArray<init_arr, jump_arr, hasher>(m_seed, init)) {}
    explicit constexpr unordered_set(const init_arr& init) : unordered_set(0, init) {}

    constexpr ~unordered_set() = default;
    constexpr unordered_set(const unordered_set&) = default;
    constexpr unordered_set(unordered_set&&) = default;
    constexpr unordered_set& operator=(const unordered_set&) = default;
    constexpr unordered_set& operator=(unordered_set&&) = default;

    constexpr const_iterator begin() const noexcept { return const_iterator(m_valueArray, m_jumpArray, 0, true); }
    constexpr const_iterator end() const noexcept { return const_iterator(m_valueArray, m_jumpArray, ArrSize); }
    constexpr const_iterator cbegin() const noexcept { return const_iterator(m_valueArray, m_jumpArray, 0, true); }
    constexpr const_iterator cend() const noexcept { return const_iterator(m_valueArray, m_jumpArray, ArrSize); }

    constexpr bool empty() const noexcept { return KeyCount == 0; }
    constexpr size_type size() const noexcept { return KeyCount; }
    constexpr size_type max_size() const noexcept { return ArrSize; }

    template <class K>
    constexpr size_type count(const K& x) const {
        return find(x) != end() ? 1 : 0;
    }
    template <class K>
    constexpr const_iterator find(const K& x) const {
        auto index = hasher{}(m_seed, x) % ArrSize;
        if (m_jumpArray[index] != 0) {
            return end();
        }
        if (!key_equal{}(m_valueArray[index], x)) {
            return end();
        }
        return const_iterator(m_valueArray, m_jumpArray, index);
    }
    template <class K>
    constexpr bool contains(const K& x) const {
        return count(x);
    }
    template <class K>
    constexpr std::pair<const_iterator, const_iterator> equal_range(const K& x) const {
        const auto it = find(x);
        if (it == end()) {
            return {end(), end()};
        }
        return {it, it.increment_unsafe(1)};
    }

    template <double MemoryOverheadScaleOther>
    constexpr bool operator==(const unordered_set<Key, KeyCount, MemoryOverheadScaleOther, Hash, KeyEqual>& other) const {
        for (const auto& key : *this) {
            if (!other.contains(key)) {
                return false;
            }
        }
        return true;
    }

private:
    hash_seed_type m_seed;
    value_arr m_valueArray;
    jump_arr m_jumpArray;
};

template <typename Key, double MemoryOverheadScale = 1.0, typename Hash = phf::hash<Key>, typename KeyEqual = std::equal_to<Key>,
          std::size_t KeyCount>
    requires(MemoryOverheadScale >= 1.0)
constexpr auto make_unordered_set(const std::array<Key, KeyCount>& init) {
    return unordered_set<Key, KeyCount, MemoryOverheadScale, Hash, KeyEqual>(init);
}
template <typename Key, double MemoryOverheadScale = 1.0, typename Hash = phf::hash<Key>, typename KeyEqual = std::equal_to<Key>,
          std::size_t KeyCount>
    requires(MemoryOverheadScale >= 1.0)
constexpr auto make_unordered_set(hash_seed_type startingSeed, const std::array<Key, KeyCount>& init) {
    return unordered_set<Key, KeyCount, MemoryOverheadScale, Hash, KeyEqual>(startingSeed, init);
}

} // namespace phf