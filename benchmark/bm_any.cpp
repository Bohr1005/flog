#include "any.hpp"
#include <any>
#include <benchmark/benchmark.h>

template <typename T> static void std_any(benchmark::State &state) {
  T seed{};
  for (auto _ : state) { // NOLINT
    benchmark::DoNotOptimize(std::any(seed));
  }
}

template <typename T> static void bm_any(benchmark::State &state) {
  using namespace flog;
  T seed{};
  for (auto _ : state) { // NOLINT
    benchmark::DoNotOptimize(any(seed));
  }
}

BENCHMARK_TEMPLATE(std_any, int8_t);
BENCHMARK_TEMPLATE(bm_any, int8_t);
BENCHMARK_TEMPLATE(std_any, int16_t);
BENCHMARK_TEMPLATE(bm_any, int16_t);
BENCHMARK_TEMPLATE(std_any, int32_t);
BENCHMARK_TEMPLATE(bm_any, int32_t);
BENCHMARK_TEMPLATE(std_any, int64_t);
BENCHMARK_TEMPLATE(bm_any, int64_t);
BENCHMARK_TEMPLATE(std_any, uint8_t);
BENCHMARK_TEMPLATE(bm_any, uint8_t);
BENCHMARK_TEMPLATE(std_any, uint16_t);
BENCHMARK_TEMPLATE(bm_any, uint16_t);
BENCHMARK_TEMPLATE(std_any, uint32_t);
BENCHMARK_TEMPLATE(bm_any, uint32_t);
BENCHMARK_TEMPLATE(std_any, uint64_t);
BENCHMARK_TEMPLATE(bm_any, uint64_t);
BENCHMARK_TEMPLATE(std_any, float);
BENCHMARK_TEMPLATE(bm_any, float);
BENCHMARK_TEMPLATE(std_any, bool);
BENCHMARK_TEMPLATE(bm_any, bool);
BENCHMARK_TEMPLATE(std_any, flog::date);
BENCHMARK_TEMPLATE(bm_any, flog::date);
BENCHMARK_TEMPLATE(std_any, flog::daytime);
BENCHMARK_TEMPLATE(bm_any, flog::daytime);
BENCHMARK_TEMPLATE(std_any, flog::datetime);
BENCHMARK_TEMPLATE(bm_any, flog::datetime);

static void bm_any_char(benchmark::State &state) {
  using namespace flog;
  char c = 'a';
  for (auto _ : state) { // NOLINT
    benchmark::DoNotOptimize(any(c));
  }
}

static void std_any_char(benchmark::State &state) {
  char c = 'a';
  for (auto _ : state) { // NOLINT
    benchmark::DoNotOptimize(std::any(c));
  }
}

static void bm_any_cstr(benchmark::State &state) {
  using namespace flog;
  auto cs = +"cstr";
  for (auto _ : state) { // NOLINT
    benchmark::DoNotOptimize(any(cs));
  }
}

static void std_any_cstr(benchmark::State &state) {
  auto cs = +"cstr";
  for (auto _ : state) { // NOLINT
    benchmark::DoNotOptimize(std::any(cs));
  }
}

static void bm_any_str(benchmark::State &state) {
  using namespace flog;
  auto str = std::string("abcd");
  for (auto _ : state) { // NOLINT
    benchmark::DoNotOptimize(any(str));
  }
}

static void std_any_str(benchmark::State &state) {
  auto str = std::string("abcd");
  for (auto _ : state) { // NOLINT
    benchmark::DoNotOptimize(std::any(str));
  }
}

BENCHMARK(bm_any_char);
BENCHMARK(std_any_char);
BENCHMARK(bm_any_cstr);
BENCHMARK(std_any_cstr);
BENCHMARK(bm_any_str);
BENCHMARK(std_any_str);

BENCHMARK_MAIN();