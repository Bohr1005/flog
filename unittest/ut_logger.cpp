#include "log.hpp"
#include "logger.hpp"
#include <gtest/gtest.h>
#include <memory>

TEST(LoggerTest, STDOUT) {
  flog::init_logger(flog::level::INFO, 1024);
  for (auto i = 0; i < 1000; ++i) {
    INFO("asd");
  }
}

TEST(LoggerTest, FILE) {
  flog::init_logger(flog::level::INFO, "test", 1024);
  for (auto i = 0; i < 1000; ++i) {
    INFO("asd");
  }
}