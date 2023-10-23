#include "log.hpp"
#include "logger.hpp"
#include <gtest/gtest.h>
#include <memory>

std::unique_ptr<flog::logger> _g_logger;
TEST(LoggerTest, STDOUT) {
  _g_logger = std::make_unique<flog::logger>(flog::level::INFO, 1024);

  for (auto i = 0; i < 1000; ++i) {
    INFO("asd");
  }
}

TEST(LoggerTest, FILE) {
  _g_logger = std::make_unique<flog::logger>(flog::level::INFO, "test", 1024);

  for (auto i = 0; i < 1000; ++i) {
    INFO("asd");
  }
}