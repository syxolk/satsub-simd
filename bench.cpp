#include <cstdint>
#include <cstdlib>
#include <memory>
#include <vector>

#include "satsub.hpp"
#include <benchmark/benchmark.h>

static void BM_SubsNaive(benchmark::State &state) {
    std::vector<std::uint8_t> vec(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        for (std::size_t i = 0; i < vec.size(); i++) {
            vec[i] = i % 256;
        }
        state.ResumeTiming();
        satsub_naive(vec.data(), vec.size(), 1);
    }
}
BENCHMARK(BM_SubsNaive)->Range(1 << 10, 1 << 29);

static void BM_SubsNaive_PreventBranchPrediction(benchmark::State &state) {
    std::vector<std::uint8_t> vec(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        for (std::size_t i = 0; i < vec.size(); i++) {
            vec[i] = i % 2;
        }
        state.ResumeTiming();
        satsub_naive(vec.data(), vec.size(), 1);
    }
}
BENCHMARK(BM_SubsNaive_PreventBranchPrediction)->Range(1 << 10, 1 << 29);

static void BM_SubsBranchless(benchmark::State &state) {
    std::vector<std::uint8_t> vec(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        for (std::size_t i = 0; i < vec.size(); i++) {
            vec[i] = i % 256;
        }
        state.ResumeTiming();
        satsub_branchless(vec.data(), vec.size(), 1);
    }
}
BENCHMARK(BM_SubsBranchless)->Range(1 << 10, 1 << 29);

static void BM_SubsBuiltin(benchmark::State &state) {
    std::vector<std::uint8_t> vec(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        for (std::size_t i = 0; i < vec.size(); i++) {
            vec[i] = i % 256;
        }
        state.ResumeTiming();
        satsub_builtin(vec.data(), vec.size(), 1);
    }
}
BENCHMARK(BM_SubsBuiltin)->Range(1 << 10, 1 << 29);

static void BM_SubsSSE(benchmark::State &state) {
    std::vector<std::uint8_t> vec(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        for (std::size_t i = 0; i < vec.size(); i++) {
            vec[i] = i % 256;
        }
        state.ResumeTiming();
        satsub_sse(vec.data(), vec.size(), 1);
    }
}
BENCHMARK(BM_SubsSSE)->Range(1 << 10, 1 << 29);
