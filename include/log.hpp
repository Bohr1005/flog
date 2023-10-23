#pragma once

#include "any.hpp"
#include "datetime.hpp"

namespace details {
bool serialize(view &);

template <typename T, typename... ARGS>
auto serialize(flog::view &v, T &&val, ARGS &&...args) {
  if (!v.add(val)) {
    return false;
  }
  return serialize(v, std::forward<ARGS>(args)...);
}
} // namespace details
namespace flog {

enum class level : uint8_t { DEBUG, INFO, WARN, ERROR };
struct alignas(CACHE_LINE) log {
  template <typename... ARGS>
  log(level lvl, std::string_view filename, int lineno, ARGS &&...args)
      : level(lvl), file(filename.substr(filename.rfind("/") + 1)),
        line(lineno), dt(datetime::now()) {
    view v(view(buf, sizeof(buf)));
    details::serialize(v, std::forward<ARGS>(args)...);
  }

  log() = default;

  flog::level level;
  std::string file;
  int line;
  datetime dt;

  char buf[sizeof(any) * 32];
};

static_assert(CACHE_LINE * 9 == sizeof(log));
} // namespace flog

namespace std {
std::string to_string(flog::level);
}