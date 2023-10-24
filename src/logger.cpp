#include "logger.hpp"
#include "fatal.hpp"
#include <filesystem>
#include <thread>

namespace flog {
logger::logger(flog::level level, uint32_t capacity)
    : _lvl(level), _channel(capacity), _appender(new appender(stdout)) {
  init_worker();
}

logger::logger(flog::level level, std::string_view filename, uint32_t capacity)
    : _lvl(level), _channel(capacity) {
  open_file(filename);
  init_worker();
}

flog::level logger::level() const { return _lvl; }

logger::~logger() { stop(); }

void logger::open_file(std::string_view filename) {
  auto path = std::filesystem::current_path() / "log/";
  if (!std::filesystem::exists(path)) {
    std::error_code ec;
    std::filesystem::create_directory(path, ec);
    if (ec) {
      FATAL(path, ec.message());
    }
  }

  path.append(filename).replace_extension(".log");

  auto file = std::fopen(path.c_str(), "a+");
  if (!file) {
    FATAL(path, errno, strerror(errno));
  }
  _appender = std::make_unique<appender>(file);
}

bool logger::enable_log(flog::level lvl) const { return lvl >= _lvl; }
void logger::init_worker() {
  _active.store(true, std::memory_order_relaxed);
  std::thread worker{[&]() {
    while (1) {
      using namespace std::chrono_literals;

      std::this_thread::sleep_for(1s);
      if (!_active.load(std::memory_order_relaxed)) {
        break;
      }
      while (auto log = _channel.recv()) {
        _appender->on_log(*log);
      }
      _appender->flush();
    }
  }};
  worker.detach();
}

void logger::stop() {
  _active.store(false, std::memory_order_relaxed);
  while (auto log = _channel.recv()) {
    _appender->on_log(*log);
  }
  _appender->flush();
};
} // namespace flog