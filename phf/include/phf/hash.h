#pragma once

#include <string_view>
#include <type_traits>

#include "internal/constexpr-xxh3.h"

// std::hash does not support constexpr, so we have to implement our own
namespace phf {
using hash_type = uint64_t;
using hash_seed_type = uint64_t;

// only allow specializations
template <typename T>
struct hash {
    hash() = delete;
};

// integral primitives (specialize if sizeof(T) > sizeof(hash_type) is needed)
template <typename T>
    requires((std::is_integral_v<T> || std::is_enum_v<T>) && (sizeof(T) <= sizeof(hash_type)))
struct hash<T> {
    constexpr hash_type operator()(hash_seed_type seed, const T& key) const {
        return seed ^ (static_cast<hash_type>(key) + 0x9e3779b97f4a7c16 + (seed << 6) + (seed >> 2));
    }
};

// std::string_view
template <>
struct hash<std::string_view> {
    constexpr hash_type operator()(hash_seed_type seed, const std::string_view& key) const {
        return constexpr_xxh3::XXH3_64bits_withSeed_const(key.data(), key.size(), seed);
    }
};

// concepts
template <typename T> // TODO: allow specialized hash functions
concept Hashable = requires(T a) {
    { hash<T>{}(0, a) } -> std::convertible_to<hash_type>;
};

} // namespace phf