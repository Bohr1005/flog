#pragma once

#include "date.hpp"
#include "daytime.hpp"

namespace flog {
class datetime : public std::chrono::time_point<std::chrono::system_clock,
                                                std::chrono::nanoseconds> {
public:
  datetime() = default;
  explicit datetime(rep);
  datetime(std::chrono::nanoseconds const &);
  datetime(flog::date, flog::daytime);

  static datetime create(rep, rep, rep, rep = 0, rep = 0, rep = 0, rep = 0);
  static datetime min();
  static datetime max();
  static datetime now();

  flog::date date() const;
  flog::daytime daytime() const;

  rep unix_timestamp() const;
  rep utc_unix_timestamp() const;
  datetime to_utc() const;

  template <typename Rep, typename Period>
  auto operator+(std::chrono::duration<Rep, Period> const &du) {
    auto nano = std::chrono::duration_cast<duration>(du);
    return datetime{time_since_epoch() + nano};
  }

  template <typename Rep, typename Period>
  auto operator-(std::chrono::duration<Rep, Period> const &du) {
    auto nano = std::chrono::duration_cast<duration>(du);
    return datetime{time_since_epoch() - nano};
  }
};
} // namespace flog
namespace std {
std::string to_string(flog::datetime const &);
} // namespace std
