#include <benchmark/benchmark.h>

#include "../../phf/include/phf/hash.h"

#include "gen_data.h"

static void BM_hash_phf(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& key : testData_long) {
            volatile auto h = phf::hash<std::string_view>{}(0, key);
            benchmark::DoNotOptimize(h);
        }
    }
}
BENCHMARK(BM_hash_phf);
static void BM_hash_std(benchmark::State& state) {
    for (auto _ : state) {
        for (const auto& key : testData_long) {
            volatile auto h = std::hash<std::string_view>{}(key);
            benchmark::DoNotOptimize(h);
        }
    }
}
BENCHMARK(BM_hash_std);