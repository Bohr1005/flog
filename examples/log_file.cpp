#include "logger.hpp"
#include <memory>

std::unique_ptr<flog::logger> _g_logger;
int main() {
  _g_logger = std::make_unique<flog::logger>(flog::level::INFO, "test", 1024);

  INFO("hello world");
}