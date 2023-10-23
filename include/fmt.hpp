#pragma once
#include <ostream>

namespace flog {
template <typename... ARGS> auto format(std::ostream &os, ARGS &&...args) {
  ((os << std::forward<ARGS>(args) << ' '), ...);
}
} // namespace flog