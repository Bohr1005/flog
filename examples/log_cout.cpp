#include "log.hpp"
#include "logger.hpp"
#include <memory>

int main() {
  init_logger(flog::level::INFO, 1024);
  INFO("hello", "world");
}