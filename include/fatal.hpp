#pragma once
#include "datetime.hpp"
#include "fmt.hpp"
#include <sstream>

namespace flog {
class fatal_error : public std::exception {
public:
  fatal_error(std::string_view msg) : _msg(msg) {}
  const char *what() const noexcept override { return _msg.c_str(); }

private:
  std::string _msg;
};

template <typename... ARGS>
auto format_message(std::string_view file, int line, ARGS &&...args) {
  auto filename = file.substr(file.rfind("/") + 1);
  std::ostringstream ss;
  ss << "[" << std::to_string(datetime::now()) << ' ' << filename << ':' << line
     << ' ' << "FATAL"
     << "] ";
  format(ss, std::forward<ARGS>(args)...);

  return ss.str();
}

template <typename... ARGS> auto throw_fatal_error(ARGS &&...args) {
  throw fatal_error(format_message(std::forward<ARGS>(args)...));
}
} // namespace flog

#define FATAL(...) flog::throw_fatal_error(__FILE__, __LINE__, __VA_ARGS__)