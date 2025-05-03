#pragma once

#include <array>
#include <functional>

#include "hash.h"
#include "internal/phf.h"

namespace phf {

template <typename Key, typename Value, std::size_t KeyCount, double MemoryOverheadScale = 1.0, typename Hash = phf::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>
    requires(MemoryOverheadScale >= 1.0)
class unordered_map {
private:
    static constexpr inline auto ArrSize = internal::sizeWithMemoryOverhead<KeyCount, MemoryOverheadScale>;

public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const key_type, mapped_type>;
    using value_type_mut = std::pair<key_type, mapped_type>;
    using size_type = std::size_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using iterator = internal::SparseIterator<value_type, ArrSize, false>;
    using const_iterator = internal::SparseIterator<value_type, ArrSize, true>;

private:
    using init_arr = std::array<value_type_mut, KeyCount>;
    using value_arr = std::array<value_type, ArrSize>;
    using value_arr_mut = std::array<value_type_mut, ArrSize>;
    using jump_arr = std::array<internal::IteratorJumpType, ArrSize>;

    struct pair_hasher {
        constexpr hash_type operator()(hash_seed_type seed, const value_type_mut& key) const { return hasher{}(seed, key.first); }
    };
    struct pair_key_equal {
        constexpr bool operator()(const value_type_mut& lhs, const value_type_mut& rhs) const { return key_equal{}(lhs.first, rhs.first); }
    };

public:
    constexpr unordered_map(hash_seed_type startingSeed, init_arr init)
        : m_seed(internal::getSeed<value_type_mut, KeyCount, MemoryOverheadScale, pair_hasher, pair_key_equal>(startingSeed, init)),
          m_valueArray(makeConstArray(internal::initValueArray<init_arr, value_arr_mut, pair_hasher>(m_seed, init))),
          m_jumpArray(internal::initJumpArray<init_arr, jump_arr, pair_hasher>(m_seed, init)) {}
    explicit constexpr unordered_map(init_arr init) : unordered_map(0, init) {}

    constexpr ~unordered_map() = default;
    constexpr unordered_map(const unordered_map&) = default;
    constexpr unordered_map(unordered_map&&) = default;
    constexpr unordered_map& operator=(const unordered_map&) = default;
    constexpr unordered_map& operator=(unordered_map&&) = default;

    constexpr iterator begin() noexcept { return iterator(&m_valueArray, &m_jumpArray, 0, true); }
    constexpr iterator end() noexcept { return iterator(&m_valueArray, &m_jumpArray, ArrSize); }
    constexpr const_iterator begin() const noexcept { return const_iterator(&m_valueArray, &m_jumpArray, 0, true); }
    constexpr const_iterator end() const noexcept { return const_iterator(&m_valueArray, &m_jumpArray, ArrSize); }
    constexpr const_iterator cbegin() const noexcept { return const_iterator(&m_valueArray, &m_jumpArray, 0, true); }
    constexpr const_iterator cend() const noexcept { return const_iterator(&m_valueArray, &m_jumpArray, ArrSize); }

    constexpr bool empty() const noexcept { return KeyCount == 0; }
    constexpr size_type size() const noexcept { return KeyCount; }
    constexpr size_type max_size() const noexcept { return ArrSize; }

    template <class K>
    constexpr mapped_type& at(const K& x) {
        auto it = find(x);
        if (it == end()) {
            throw std::out_of_range("Key not found");
        }
        return it->second;
    }
    template <class K>
    constexpr const mapped_type& at(const K& x) const {
        const auto it = find(x);
        if (it == end()) {
            throw std::out_of_range("Key not found");
        }
        return it->second;
    }

    template <class K>
    constexpr size_type count(const K& x) const {
        return find(x) != end() ? 1 : 0;
    }

    template <class K>
    constexpr iterator find(const K& x) {
        auto index = hasher{}(m_seed, x) % ArrSize;
        if (m_jumpArray[index] != 0) {
            return end();
        }
        if (!key_equal{}(m_valueArray[index].first, x)) {
            return end();
        }
        return iterator(&m_valueArray, &m_jumpArray, index);
    }
    template <class K>
    constexpr const_iterator find(const K& x) const {
        auto index = hasher{}(m_seed, x) % ArrSize;
        if (m_jumpArray[index] != 0) {
            return end();
        }
        if (!key_equal{}(m_valueArray[index].first, x)) {
            return end();
        }
        return const_iterator(&m_valueArray, &m_jumpArray, index);
    }
    template <class K>
    constexpr bool contains(const K& x) const {
        return count(x);
    }
    template <class K>
    constexpr std::pair<iterator, iterator> equal_range(const K& x) {
        auto it = find(x);
        if (it == end()) {
            return {end(), end()};
        }
        return {it, it.increment_unsafe(1)};
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
        requires(std::equality_comparable<Value>)
    constexpr bool operator==(const unordered_map<Key, Value, KeyCount, MemoryOverheadScaleOther, Hash, KeyEqual>& other) const {
        for (const auto& [key, val] : *this) {
            const auto it = other.find(key);
            if (it == other.end() || !(it->second == val)) {
                return false;
            }
        }
        return true;
    }

private:
    template <std::size_t... I>
    constexpr std::array<value_type, ArrSize> makeConstArrayImpl(std::array<value_type_mut, ArrSize> arr, std::index_sequence<I...>) {
        return {value_type{arr[I]}...};
    }
    constexpr std::array<value_type, ArrSize> makeConstArray(std::array<value_type_mut, ArrSize> arr) {
        return makeConstArrayImpl(arr, std::make_index_sequence<ArrSize>{});
    }

    hash_seed_type m_seed;
    value_arr m_valueArray;
    jump_arr m_jumpArray;
};

template <typename Key, typename Value, double MemoryOverheadScale = 1.0, typename Hash = phf::hash<Key>,
          typename KeyEqual = std::equal_to<Key>, std::size_t KeyCount>
    requires(MemoryOverheadScale >= 1.0)
constexpr auto make_unordered_map(const std::array<std::pair<Key, Value>, KeyCount>& init) {
    return unordered_map<Key, Value, KeyCount, MemoryOverheadScale, Hash, KeyEqual>(init);
}
template <typename Key, typename Value, double MemoryOverheadScale = 1.0, typename Hash = phf::hash<Key>,
          typename KeyEqual = std::equal_to<Key>, std::size_t KeyCount>
    requires(MemoryOverheadScale >= 1.0)
constexpr auto make_unordered_map(hash_seed_type startingSeed, const std::array<std::pair<Key, Value>, KeyCount>& init) {
    return unordered_map<Key, Value, KeyCount, MemoryOverheadScale, Hash, KeyEqual>(startingSeed, init);
}

} // namespace phf