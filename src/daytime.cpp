#include "daytime.hpp"

#include <iomanip>
#include <sstream>

#include "time_offset.hpp"
namespace flog {

daytime::daytime(rep val) : std::chrono::nanoseconds(val) {}
daytime::daytime(std::chrono::nanoseconds const &val)
    : std::chrono::nanoseconds(val) {}

daytime daytime::create(rep hour, rep minute, rep second, rep nano) {
  return daytime{(hour * 3600 + minute * 60 + second) * period::den + nano};
}
daytime daytime::min() { return daytime{0}; }
daytime daytime::max() { return daytime{24 * 3600 * period::den}; }
daytime daytime::now() {
  ::timespec t;
  ::clock_gettime(CLOCK_REALTIME, &t);
  auto offset = duration_cast<std::chrono::seconds>(time_offset());
  rep sec = (t.tv_sec + offset.count()) % (3600 * 24);
  return daytime{sec * period::den + (rep)t.tv_nsec};
}
} // namespace flog
namespace std {
std::string to_string(flog::daytime const &daytime) {
  auto total_sec = daytime.count() / flog::daytime::period::den;

  auto hrs = total_sec / 3600;
  auto min = (total_sec - hrs * 3600) / 60;
  auto sec = total_sec % 60;
  auto nano = daytime.count() % flog::daytime::period::den;

  std::ostringstream ss;
  ss << setw(2) << setfill('0') << hrs << ':' << setw(2) << setfill('0') << min
     << ':' << setw(2) << setfill('0') << sec << '.' << setw(9) << setfill('0')
     << nano;
  return ss.str();
}
} // namespace std
