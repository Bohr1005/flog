#include "log.hpp"

namespace details {
bool serialize(view &) { return true; }
} // namespace details

namespace std {
std::string to_string(flog::level lvl) {
  switch (lvl) {
  case flog::level::DEBUG:
    return "ERROR";
  case flog::level::INFO:
    return "INFO";
  case flog::level::ERROR:
    return "ERROR";
  case flog::level::WARN:
    return "WARN";
  default:
    return "KNOWN";
  }
}
} // namespace std