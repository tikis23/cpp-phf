#include <benchmark/benchmark.h>

#include "../../phf/include/phf/unordered_map.h"
#include <unordered_map>

#include "gen_data.h"

template <typename Sz>
class UnorderedMap_ShortKeys : public benchmark::Fixture {
public:
    static constexpr auto Size = Sz::value;
    static constexpr auto test_data = get_test_data_pairs<Size>(testData_short);
    static constexpr auto umap_phf = phf::make_unordered_map<std::string_view, int, 32.0>(test_data);
    static const std::unordered_map<std::string_view, int> umap_std;
};
template <typename Sz>
const std::unordered_map<std::string_view, int> UnorderedMap_ShortKeys<Sz>::umap_std{test_data.begin(), test_data.end()};

template <typename Sz>
class UnorderedMap_LongKeys : public benchmark::Fixture {
public:
    static constexpr auto Size = Sz::value;
    static constexpr auto test_data = get_test_data_pairs<Size>(testData_long);
    static constexpr auto umap_phf = phf::make_unordered_map<std::string_view, int, 32.0>(test_data);
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