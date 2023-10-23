#pragma once
#include <chrono>
#include <string>

namespace flog {
class daytime : public std::chrono::nanoseconds {
public:
  daytime() = default;
  explicit daytime(rep val);
  daytime(std::chrono::nanoseconds const &);

  static daytime create(rep, rep, rep, rep);
  static daytime min();
  static daytime max();
  static daytime now();
};
} // namespace flog
namespace std {
std::string to_string(flog::daytime const &);
} // namespace std
