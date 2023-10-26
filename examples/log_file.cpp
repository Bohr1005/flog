#include "logger.hpp"
#include <memory>

int main() {
  init_logger(flog::level::INFO, "test", 1024);
  INFO("hello", "world");
}