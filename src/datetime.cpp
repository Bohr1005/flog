#include "datetime.hpp"
#include "time_offset.hpp"

namespace flog {
datetime::datetime(rep val)
    : std::chrono::time_point<std::chrono::system_clock,
                              std::chrono::nanoseconds>(
          std::chrono::nanoseconds(val)) {}
datetime::datetime(std::chrono::nanoseconds const &val)
    : std::chrono::time_point<std::chrono::system_clock,
                              std::chrono::nanoseconds>(val) {}

datetime::datetime(flog::date date, flog::daytime daytime)
    : datetime(date + daytime) {}
datetime datetime::create(rep year, rep month, rep day, rep hour, rep minute,
                          rep second, rep nano) {
  return datetime{date::create(year, month, day) +
                  daytime::create(hour, minute, second, nano)};
}

datetime datetime::min() { return create(1970, 1, 1); }
datetime datetime::max() {
  return std::chrono::time_point<std::chrono::system_clock,
                                 std::chrono::nanoseconds>::max()
      .time_since_epoch();
}
datetime datetime::now() {
  return duration{(clock::now() + time_offset()).time_since_epoch()};
}
flog::date datetime::date() const {
  using namespace std::chrono_literals;
  return flog::date{static_cast<date::rep>(time_since_epoch() / 24h)};
}
flog::daytime datetime::daytime() const {
  return flog::daytime{time_since_epoch() - date()};
}

datetime::rep datetime::unix_timestamp() const {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             (*this).time_since_epoch())
      .count();
}
datetime::rep datetime::utc_unix_timestamp() const {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             (*this - time_offset()).time_since_epoch())
      .count();
}
datetime datetime::to_utc() const {
  return datetime((*this - time_offset()).time_since_epoch().count());
}
} // namespace flog
namespace std {
std::string to_string(flog::datetime const &datetime) {
  return std::to_string(datetime.date()) + ' ' +
         std::to_string(datetime.daytime());
}
} // namespace std
