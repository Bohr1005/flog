#pragma once

#include <chrono>
#include <string>

namespace flog {
using std::chrono::days;

class date : public days {
public:
  date() = default;
  explicit date(rep val);

  static date create(rep year, rep month, rep day);
  static date min();
  static date max();

  static date utc_today();

  static date today();
};
} // namespace flog
namespace std {
std::string to_string(flog::date const &);
} // namespace std