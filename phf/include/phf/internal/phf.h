#pragma once

#include <array>

#include "../hash.h"

namespace phf::internal {
using IteratorJumpType = uint8_t;

template <std::size_t Size, double MemoryOverheadScale>
constexpr std::size_t sizeWithMemoryOverhead = static_cast<std::size_t>(Size * MemoryOverheadScale);

template <typename Key, std::size_t KeyCount, double MemoryOverheadScale, typename Hash, typename KeyEqual>
    requires(MemoryOverheadScale >= 1.0)
constexpr hash_seed_type getSeed(hash_seed_type startingSeed, const std::array<Key, KeyCount>& keys) {
    // check if the keys are unique, std::unordered_set can be used here when c++26 is available
    for (std::size_t i = 1; i < KeyCount; i++) {
        for (std::size_t j = 0; j < i; j++) {
            if (KeyEqual{}(keys[i], keys[j])) {
                throw std::invalid_argument("Keys must be unique");
            }
        }
    }

    // generate a seed
    constexpr std::size_t modulo = sizeWithMemoryOverhead<KeyCount, MemoryOverheadScale>;
    std::array<uint8_t, modulo> slots;
    hash_seed_type seed;
    for (seed = startingSeed; seed < std::numeric_limits<hash_seed_type>::max(); seed++) {
        slots.fill(0);
        bool hadCollision = false;
        for (const auto& key : keys) {
            auto slotIndex = Hash{}(seed, key) % modulo;
            if (slots[slotIndex] == 0) {
                slots[slotIndex] = 1;
            } else {
                hadCollision = true;
                break;
            }
        }
        if (!hadCollision) {
            break;
        }
    }

    return seed;
}

template <typename InitArr, typename ValueArr, typename Hash>
constexpr ValueArr initValueArray(hash_seed_type seed, const InitArr& init) {
    ValueArr valueArray{};
    for (const auto& key : init) {
        auto index = Hash{}(seed, key) % valueArray.size();
        valueArray[index] = key;
    }
    return valueArray;
}

template <typename InitArr, typename JumpArr, typename Hash>
static constexpr JumpArr initJumpArray(hash_seed_type seed, const InitArr& init) {
    JumpArr jumpArray{};
    jumpArray.fill(1);
    for (const auto& key : init) {
        auto index = Hash{}(seed, key) % jumpArray.size();
        jumpArray[index] = 0;
    }
    if (jumpArray.size() < 3) {
        return jumpArray;
    }

    for (std::size_t i = 1; i < jumpArray.size(); i++) {
        std::size_t index = jumpArray.size() - i - 1;
        if (jumpArray[index] == 0) {
            continue;
        }
        if (jumpArray[index + 1] == std::numeric_limits<IteratorJumpType>::max()) {
            jumpArray[index] = 1;
            continue;
        }
        jumpArray[index] = jumpArray[index + 1] + 1;
    }
    return jumpArray;
}

template <typename T, std::size_t N, bool IsConst>
class SparseIterator {
public:
    using data_array = std::conditional_t<IsConst, const std::array<T, N>, std::array<T, N>>;

    constexpr SparseIterator(data_array& data, const std::array<IteratorJumpType, N>& jump, std::size_t pos, bool goToValid = false)
        : m_data(data), m_jump(jump), m_pos(pos) {
        if (goToValid && m_jump[m_pos] != 0) {
            operator++();
        }
    }

    constexpr T& operator*()
        requires(!IsConst)
    {
        return m_data[m_pos];
    }
    constexpr const T& operator*() const { return m_data[m_pos]; }

    constexpr T* operator->()
        requires(!IsConst)
    {
        return &m_data[m_pos];
    }
    constexpr const T* operator->() const { return &m_data[m_pos]; }

    constexpr SparseIterator& operator++() {
        do {
            auto jumpCount = m_jump[m_pos];
            m_pos += jumpCount ? jumpCount : 1;
        } while (m_pos < N && m_jump[m_pos] != 0);
        return *this;
    }
    constexpr SparseIterator operator++(int) {
        SparseIterator tmp = *this;
        operator++();
        return tmp;
    }
    constexpr SparseIterator operator+(std::size_t offset) const {
        SparseIterator tmp = *this;

        for (std::size_t i = 0; i < offset && tmp.m_pos < N; i++) {
            ++tmp;
        }

        return tmp;
    }

    constexpr SparseIterator increment_unsafe(std::size_t offset) const {
        SparseIterator tmp = *this;
        tmp.m_pos += offset;
        return tmp;
    }

    constexpr bool operator!=(const SparseIterator& other) const { return m_pos != other.m_pos; }
    constexpr bool operator==(const SparseIterator& other) const { return m_pos == other.m_pos; }

private:
    data_array& m_data;
    const std::array<IteratorJumpType, N>& m_jump;
    std::size_t m_pos;
};

} // namespace phf::internal