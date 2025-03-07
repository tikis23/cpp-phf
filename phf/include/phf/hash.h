#pragma once

#include <string_view>
#include <type_traits>

// std::hash does not support constexpr, so we have to implement our own
namespace phf {
// only allow specializations
template <typename T>
struct hash {
    hash() = delete;
};

// integral primitives (specialize if sizeof(T) > sizeof(std::size_t) is needed)
template <typename T>
    requires((std::is_integral_v<T> || std::is_enum_v<T>) && (sizeof(T) <= sizeof(std::size_t)))
struct hash<T> {
    constexpr std::size_t operator()(std::size_t seed, const T& key) const {
        return seed ^ (static_cast<std::size_t>(key) + 0x9e3779b97f4a7c16 + (seed << 6) + (seed >> 2));
    }
};

// std::string_view
template <>
struct hash<std::string_view> {
    constexpr std::size_t operator()(std::size_t seed, const std::string_view& key) const {
        const std::size_t fnv_prime = 1099511628211ull;
        const std::size_t offset = 14695981039346656037ull;

        std::size_t out = offset;
        for (const auto c : key) {
            out = (out ^ c) * fnv_prime;
        }
        return hash<std::size_t>{}(seed, out);
    }
};

// concepts
template <typename T>
concept Hashable = requires(T a) {
    { hash<T>{}(0, a) } -> std::convertible_to<std::size_t>;
};

} // namespace phf