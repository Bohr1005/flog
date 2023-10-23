#include "time_offset.hpp"
#include <cstring>
#include <stdexcept>

namespace flog {
static std::chrono::nanoseconds g_time_offset;

struct init_time_offset {
  init_time_offset() {
    std::time_t loc_now{};
    auto local_tm = std::localtime(&loc_now);
    if (!local_tm) {
      std::runtime_error(strerror(errno));
    }

    auto loc = std::mktime(local_tm);

    std::time_t gmt_now{};
    auto gmt_tm = std::gmtime(&gmt_now);
    if (!gmt_tm) {
      std::runtime_error(strerror(errno));
    }
    auto gmt = std::mktime(gmt_tm);
    g_time_offset = std::chrono::seconds(loc - gmt);
  }
} g_init_time_offset;

std::chrono::nanoseconds time_offset() { return g_time_offset; }
} // namespace flog