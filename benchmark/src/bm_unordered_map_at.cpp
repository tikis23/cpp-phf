#include <benchmark/benchmark.h>

#include <frozen/unordered_map.h>
#include <phf/unordered_map.h>
#include <unordered_map>

#include "gen_data.h"

constexpr double PHF_MEMORY_OVERHEAD = 24.0;

struct frozen_string_view_hash {
    static_assert(std::is_same_v<std::size_t, phf::hash_seed_type>);
    constexpr std::size_t operator()(const std::string_view& value, std::size_t seed) const {
        return phf::hash<std::string_view>{}(seed, value);
    }
};

template <typename Sz>
class UnorderedMap_ShortKeys : public benchmark::Fixture {
public:
    static constexpr auto Size = Sz::value;
    static constexpr auto test_data = get_test_data_pairs<Size>(testData_short);
    static constexpr auto umap_phf = phf::make_unordered_map<std::string_view, int, PHF_MEMORY_OVERHEAD>(test_data);
    static constexpr frozen::unordered_map<std::string_view, int, Size, frozen_string_view_hash> umap_frozen{test_data};
    static const std::unordered_map<std::string_view, int> umap_std;
};
template <typename Sz>
const std::unordered_map<std::string_view, int> UnorderedMap_ShortKeys<Sz>::umap_std{test_data.begin(), test_data.end()};

template <typename Sz>
class UnorderedMap_LongKeys : public benchmark::Fixture {
public:
    static constexpr auto Size = Sz::value;
    static constexpr auto test_data = get_test_data_pairs<Size>(testData_long);
    static constexpr auto umap_phf = phf::make_unordered_map<std::string_view, int, PHF_MEMORY_OVERHEAD>(test_data);
    static constexpr frozen::unordered_map<std::string_view, int, Size, frozen_string_view_hash> umap_frozen{test_data};
    static const std::unordered_map<std::string_view, int> umap_std;
};
template <typename Sz>
const std::unordered_map<std::string_view, int> UnorderedMap_LongKeys<Sz>::umap_std{test_data.begin(), test_data.end()};

BENCHMARK_TEMPLATE_F(UnorderedMap_ShortKeys, At_phf_10, std::integral_constant<std::size_t, 10>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_phf.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_ShortKeys, At_std_10, std::integral_constant<std::size_t, 10>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_std.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_ShortKeys, At_frozen_10, std::integral_constant<std::size_t, 10>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_frozen.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_ShortKeys, At_phf_100, std::integral_constant<std::size_t, 100>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_phf.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_ShortKeys, At_std_100, std::integral_constant<std::size_t, 100>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_std.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_ShortKeys, At_frozen_100, std::integral_constant<std::size_t, 100>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_frozen.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_ShortKeys, At_phf_256, std::integral_constant<std::size_t, 256>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_phf.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_ShortKeys, At_std_256, std::integral_constant<std::size_t, 256>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_std.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_ShortKeys, At_frozen_256, std::integral_constant<std::size_t, 256>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_frozen.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}

BENCHMARK_TEMPLATE_F(UnorderedMap_LongKeys, At_phf_10, std::integral_constant<std::size_t, 10>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_phf.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_LongKeys, At_std_10, std::integral_constant<std::size_t, 10>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_std.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_LongKeys, At_frozen_10, std::integral_constant<std::size_t, 10>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_frozen.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_LongKeys, At_phf_100, std::integral_constant<std::size_t, 100>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_phf.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_LongKeys, At_std_100, std::integral_constant<std::size_t, 100>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_std.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_LongKeys, At_frozen_100, std::integral_constant<std::size_t, 100>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_frozen.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_LongKeys, At_phf_256, std::integral_constant<std::size_t, 256>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_phf.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_LongKeys, At_std_256, std::integral_constant<std::size_t, 256>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_std.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}
BENCHMARK_TEMPLATE_F(UnorderedMap_LongKeys, At_frozen_256, std::integral_constant<std::size_t, 256>)(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& [k, _] : test_data) {
            volatile auto value = umap_frozen.at(k);
            benchmark::DoNotOptimize(value);
        }
    }
}