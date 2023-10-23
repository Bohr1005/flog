#include "any.hpp"
#include <cassert>

namespace flog {
bool any::operator!=(any const &rhs) const {
  if (rhs.type() != _type) {
    return true;
  }
  switch (_type) {
  case type_tag::int_type:
    return int_value != rhs.int_value;
  case type_tag::uint_type:
    return uint_value != rhs.uint_value;
  case type_tag::int64_type:
    return int64_value != rhs.int64_value;
  case type_tag::uint64_type:
    return uint64_value != rhs.uint64_value;
  case type_tag::bool_type:
    return bool_value != rhs.bool_value;
  case type_tag::char_type:
    return char_value != rhs.char_value;
  case type_tag::float_type:
    return std::fabs(float_value - rhs.float_value) > 1e-7;
  case type_tag::double_type:
    return std::fabs(double_value - rhs.double_value) > 1e-10;
  case type_tag::string_type:
    return std::strcmp(&_buf[0], &rhs._buf[0]);
  case type_tag::pointer_type:
    return pointer != rhs.pointer;
  default:
    return true;
  }
}

template <> int any::get() const { return int_value; }
template <> uint any::get() const { return uint_value; }
template <> int64_t any::get() const { return int64_value; }
template <> uint64_t any::get() const { return uint64_value; }
template <> date any::get() const { return date{int64_value}; }
template <> daytime any::get() const { return daytime(int64_value); }
template <> datetime any::get() const { return datetime(int64_value); }
template <> bool any::get() const { return bool_value; }
template <> char any::get() const { return char_value; }
template <> float any::get() const { return float_value; }
template <> double any::get() const { return double_value; }
template <> std::string_view any::get() const { return &_buf[0]; }
template <> const char *any::get() const {
  return reinterpret_cast<const char *>(pointer);
}
template <> std::string any::get() const { return std::string(&_buf[0], 15); }

view::view(const char *buf)
    : _header((header *)buf), _capacity(_header->count) {}

view::view(const char *buf, uint32_t size)
    : _header((header *)buf), _capacity(size / sizeof(any) - 1) {
  assert(sizeof(header) <= size);
  _header->count = 0;
}

const char *view::buf() const { return (const char *)(_header); }

uint32_t view::capacity() const { return _capacity; }
uint32_t view::count() const { return _header->count; }

bool view::add(any const &val) {
  if (_header->count >= capacity()) {
    return false;
  }

  ((any *)_header)[++_header->count] = val;
  return true;
}

any const &view::get(uint32_t i) const {
  if (i < count()) {
    return ((any *)_header)[i + 1];
  }

  auto static invalid_val = any();
  return invalid_val;
}

void view::set(uint32_t i, any const &val) {
  if (i < count()) {
    ((any *)_header)[i + 1] = val;
  }
}
} // namespace flog