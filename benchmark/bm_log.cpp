#include "log.hpp"
#include <benchmark/benchmark.h>

static void bm_log(benchmark::State &state) {

  for (auto _ : state) {
    benchmark::DoNotOptimize(
        flog::log(flog::level::INFO, __FILE__, __LINE__, ""));
  }
}

BENCHMARK(bm_log);
BENCHMARK_MAIN();