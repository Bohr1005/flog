#pragma once
#include "date.hpp"
#include "datetime.hpp"
#include "daytime.hpp"
#include <cmath>
#include <cstring>
#include <string_view>

namespace flog {
enum class type_tag : uint8_t {
  none_type,
  // integral
  int_type,
  uint_type,
  int64_type,
  uint64_type,
  bool_type,
  char_type,
  last_integer_type = char_type,
  // floating
  float_type,
  double_type,
  last_numeric_type = double_type,
  string_type,
  pointer_type,
};

class any {
public:
  any() : _type(type_tag::none_type) {}
  any(int val) : _type(type_tag::int_type), int_value(val) {}
  any(uint val) : _type(type_tag::uint_type), uint_value(val) {}
  any(int64_t val) : _type(type_tag::int64_type), int64_value(val) {}
  any(uint64_t val) : _type(type_tag::uint64_type), uint64_value(val) {}
  any(date val) : _type(type_tag::int64_type), int64_value(val.count()) {}
  any(daytime val) : _type(type_tag::int64_type), int64_value(val.count()) {}
  any(datetime val)
      : _type(type_tag::int64_type),
        int64_value(val.time_since_epoch().count()) {}
  any(bool val) : _type(type_tag::bool_type), bool_value(val) {}
  any(char val) : _type(type_tag::char_type), char_value(val) {}
  any(float val) : _type(type_tag::float_type), float_value(val) {}
  any(double val) : _type(type_tag::double_type), double_value(val) {}
  any(const void *val) : _type(type_tag::pointer_type), pointer(val) {}
  any(std::string_view val) : _type(type_tag::string_type) {
    std::memcpy(_buf, val.data(), std::min((int)val.size(), 15));
  }

  auto type() const { return _type; }

  template <typename T> T get() const;

  bool operator!() const { return _type == type_tag::none_type; }
  bool operator!=(any const &rhs) const;
  auto operator==(any const &rhs) const { return !operator!=(rhs); }

private:
  type_tag _type;
  char _buf[7];
  union {
    int int_value;
    uint uint_value;
    int64_t int64_value;
    uint64_t uint64_value;
    bool bool_value;
    char char_value;
    float float_value;
    double double_value;
    void const *pointer;
  };
};
static_assert(sizeof(any) == 16);

class view {
public:
  explicit view(const char *buf);
  view(const char *buf, uint32_t size);
  const char *buf() const;

  uint32_t capacity() const;
  uint32_t count() const;

  bool add(any const &);

  any const &get(uint32_t) const;
  void set(uint32_t, any const &);

private:
  struct alignas(16) header {
    u_int32_t count;
  } * _header;

  uint32_t _capacity;
};
} // namespace flog

namespace details {
using namespace flog;
constexpr bool is_intergral(type_tag t) {
  return t > type_tag::none_type && t <= type_tag::last_integer_type;
}

constexpr bool is_arithmetic(type_tag t) {
  return t > type_tag::none_type && t <= type_tag::last_numeric_type;
}

} // namespace details