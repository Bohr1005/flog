#include "date.hpp"
#include "time_offset.hpp"
#include <iomanip>
#include <tuple>

namespace flog {

template <class Int>
constexpr Int days_from_civil(Int y, unsigned m, unsigned d) noexcept {
  static_assert(std::numeric_limits<unsigned>::digits >= 18,
                "This algorithm has not been ported to a 16 bit "
                "unsigned integer");
  static_assert(std::numeric_limits<Int>::digits >= 20,
                "This algorithm has not been ported to a 16 bit "
                "signed integer");
  y -= m <= 2;
  const Int ERA = (y >= 0 ? y : y - 399) / 400;
  const unsigned YOE = static_cast<unsigned>(y - ERA * 400); // [0, 399]
  const unsigned DOY =
      (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;         // [0, 365]
  const unsigned DOE = YOE * 365 + YOE / 4 - YOE / 100 + DOY; // [0, 146096]
  return ERA * 146097 + static_cast<Int>(DOE) - 719468;
}

template <class Int>
constexpr std::tuple<Int, unsigned, unsigned> civil_from_days(Int z) noexcept {
  static_assert(std::numeric_limits<unsigned>::digits >= 18,
                "This algorithm has not been ported to a 16 bit "
                "unsigned integer");
  static_assert(std::numeric_limits<Int>::digits >= 20,
                "This algorithm has not been ported to a 16 bit "
                "signed integer");
  z += 719468;
  const Int ERA = (z >= 0 ? z : z - 146096) / 146097;
  const unsigned DOE = static_cast<unsigned>(z - ERA * 146097); // [0, 146096]
  const unsigned YOE =
      (DOE - DOE / 1460 + DOE / 36524 - DOE / 146096) / 365; // [0, 399]
  const Int Y = static_cast<Int>(YOE) + ERA * 400;
  const unsigned DOY = DOE - (365 * YOE + YOE / 4 - YOE / 100); // [0, 365]
  const unsigned MP = (5 * DOY + 2) / 153;                      // [0, 11]
  const unsigned D = DOY - (153 * MP + 2) / 5 + 1;              // [1, 31]
  const unsigned M = MP + (MP < 10 ? 3 : -9);                   // [1, 12]
  return std::tuple<Int, unsigned, unsigned>(Y + (M <= 2), M, D);
}

date::date(rep val) : std::chrono::days(val) {}

date date::create(rep year, rep month, rep day) {
  return date(days_from_civil(year, month, day));
}

date date::min() { return create(1970, 1, 1); }
date date::max() { return create(9999, 12, 31); }

date date::utc_today() {
  constexpr rep day = 3600 * 24;
  std::time_t tm;
  rep sec = std::time(&tm);

  return date{sec / day};
}

date date::today() {
  constexpr rep day = 3600 * 24;

  auto offset = std::chrono::duration_cast<std::chrono::seconds>(time_offset());
  std::time_t tm;
  rep sec = std::time(&tm) + offset.count();

  return date{sec / day};
}
} // namespace flog
namespace std {
std::string to_string(flog::date const &date) {
  auto [year, mon, day] = flog::civil_from_days(date.count());

  std::ostringstream ss;
  ss << year << setw(2) << setfill('0') << mon << setw(2) << setfill('0')
     << day;
  return ss.str();
}
} // namespace std
