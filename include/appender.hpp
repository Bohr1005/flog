#pragma once
#include "any.hpp"
#include "log.hpp"

namespace flog {
class appender {
public:
  appender(FILE *);
  appender(appender const &) = delete;
  auto operator=(appender const &) = delete;

  template <typename T> auto write(T const &v) {
    std::fwrite(" ", 1, 1, _file);
    auto str = std::to_string(v);
    std::fwrite(str.c_str(), 1, str.size(), _file);
  }

  template <typename T, size_t N> void write(const T (&arr)[N]) { write(&arr); }
  void write(const char *);
  void write(std::string_view);

  void on_log(flog::log const &);
  void flush();

  ~appender();

private:
  void deserialize(view const &);

private:
  FILE *_file{nullptr};
};
} // namespace flog