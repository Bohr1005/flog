#pragma once
#include "appender.hpp"
#include "channel.hpp"
#include "log.hpp"
#include <atomic>
#include <memory>

namespace flog {
class logger {
public:
  explicit logger(flog::level, uint32_t = 1024);
  logger(flog::level, std::string_view, uint32_t = 1024);

  logger(logger const &) = delete;
  auto operator=(logger const &) = delete;

  flog::level level() const;

  template <typename... ARGS>
  auto log_msg(flog::level lvl, std::string_view file, int lineno,
               ARGS &&...args) {
    if (enable_log(lvl)) {
      _channel.emplace(lvl, file, lineno, std::forward<ARGS>(args)...);
    }
  }
  ~logger();

private:
  void open_file(std::string_view);

  bool enable_log(flog::level) const;
  void init_worker();
  void stop();

private:
  flog::level _lvl;
  channel<log> _channel;

  std::unique_ptr<appender> _appender;
  std::atomic<bool> _active{false};
};
} // namespace flog

template <typename... ARGS> auto log(ARGS &&...args) {
  extern std::unique_ptr<flog::logger> _g_logger;
  _g_logger->log_msg(std::forward<ARGS>(args)...);
}

#define DEBUG(...) log(flog::level::DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define INFO(...) log(flog::level::INFO, __FILE__, __LINE__, __VA_ARGS__)
#define WARN(...) log(flog::level::WARN, __FILE__, __LINE__, __VA_ARGS__)
#define ERROR(...) log(flog::level::ERROR, __FILE__, __LINE__, __VA_ARGS__)