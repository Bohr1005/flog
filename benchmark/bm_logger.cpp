#include "log.hpp"
#include "logger.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <ratio>

template <typename... ARGS>
static auto benchmark_cout(uint32_t n, ARGS &&...args) {
  flog::init_logger(flog::level::INFO, n);
  auto start = std::chrono::steady_clock::now();

  for (auto i = 0L; i < n; ++i) {
    INFO(std::forward<ARGS>(args)...);
  }

  auto end = std::chrono::steady_clock::now();
  auto diff = (end - start);

  return std::chrono::duration_cast<std::chrono::duration<double>>(diff);
}

template <typename... ARGS>
static auto benchmark_file(uint32_t n, ARGS &&...args) {
  flog::init_logger(flog::level::INFO, "test", n);
  auto start = std::chrono::steady_clock::now();

  for (auto i = 0L; i < n; ++i) {
    INFO(std::forward<ARGS>(args)...);
  }

  auto end = std::chrono::steady_clock::now();
  auto diff = (end - start);

  return std::chrono::duration_cast<std::chrono::duration<double>>(diff);
}

int main() {
  auto diff = benchmark_file(
      1000000, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  std::cout << "benchmark file elapse:" << diff.count() << " "
            << "avg:" << 1000000 / diff.count() << "/sec" << std::endl;
}