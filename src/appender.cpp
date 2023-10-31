#include "appender.hpp"
#include "any.hpp"

namespace flog {
appender::appender(FILE *file) : _file(file) {}

void appender::on_log(const flog::log &log) {
  char buf[64];

  auto level = std::to_string(log.level);
  auto time = std::to_string(log.dt.daytime());
  auto file = log.file;
  auto line = log.line;

  auto len = std::snprintf(buf, sizeof(buf), "[%s %s:%d %s]", time.c_str(),
                           file.data(), line, level.c_str());

  std::fwrite(buf, 1, len, _file);

  view v(log.buf);
  deserialize(v);
  std::fwrite("\n", 1, 1, _file);
}
void appender::flush() { std::fflush(_file); }

appender::~appender() { 
    flush();
    std::fclose(_file);
}

template <> auto appender::write<bool>(bool const &v) {
  if (v) {
    std::fwrite(" True", 1, 5, _file);
  } else {
    std::fwrite(" False", 1, 6, _file);
  }
}

void appender::write(const char *v) {
  std::fwrite(" ", 1, 1, _file);
  auto ptr = v;
  while (*ptr != '\0') {
    std::fwrite(ptr++, 1, 1, _file);
  }
}

void appender::write(std::string_view v) { write(v.data()); }

void appender::deserialize(flog::view const &v) {
  for (auto i = 0U; i < v.count(); ++i) {
    auto val = v.get(i);
    switch (val.type()) {
    case type_tag::int_type:
      write(val.get<int>());
      break;
    case type_tag::uint_type:
      write(val.get<uint>());
      break;
    case type_tag::int64_type:
      write(val.get<int64_t>());
      break;
    case type_tag::uint64_type:
      write(val.get<uint64_t>());
      break;
    case type_tag::bool_type:
      write(val.get<bool>());
      break;
    case type_tag::char_type:
      write(val.get<char>());
      break;
    case type_tag::float_type:
      write(val.get<float>());
      break;
    case type_tag::double_type:
      write(val.get<double>());
      break;
    case type_tag::string_type:
      write(val.get<std::string_view>());
      break;
    case type_tag::pointer_type:
      write(val.get<const char *>());
      break;

    default:
      break;
    }
  }
}
} // namespace flog
