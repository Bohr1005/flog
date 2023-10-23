#include "any.hpp"
#include <cstring>
#include <gtest/gtest.h>
#include <string_view>

using namespace flog;

TEST(AnyTest, DefaultConstructor) {
  any a;
  EXPECT_EQ(a.type(), type_tag::none_type);
  EXPECT_TRUE(!a);
}

TEST(AnyTest, IntConstructor) {
  any a(42);
  EXPECT_EQ(a.type(), type_tag::int_type);
  EXPECT_EQ(a.get<int>(), 42);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, UIntConstructor) {
  any a(static_cast<uint>(42));
  EXPECT_EQ(a.type(), type_tag::uint_type);
  EXPECT_EQ(a.get<uint>(), 42);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, Int64Constructor) {
  any a(static_cast<int64_t>(42));
  EXPECT_EQ(a.type(), type_tag::int64_type);
  EXPECT_EQ(a.get<int64_t>(), 42);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, UInt64Constructor) {
  any a(static_cast<uint64_t>(42));
  EXPECT_EQ(a.type(), type_tag::uint64_type);
  EXPECT_EQ(a.get<uint64_t>(), 42);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, DateConstructor) {
  date d = date::create(2022, 1, 1);
  any a(d);
  EXPECT_EQ(a.type(), type_tag::int64_type);
  EXPECT_EQ(a.get<date>(), d);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, DaytimeConstructor) {
  daytime dt = daytime::create(12, 0, 0, 0);
  any a(dt);
  EXPECT_EQ(a.type(), type_tag::int64_type);
  EXPECT_EQ(a.get<daytime>(), dt);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, DatetimeConstructor) {
  datetime dt(date::create(2022, 1, 1), daytime::create(12, 0, 0, 0));
  any a(dt);
  EXPECT_EQ(a.type(), type_tag::int64_type);
  EXPECT_EQ(a.get<datetime>(), dt);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, BoolConstructor) {
  any a(true);
  EXPECT_EQ(a.type(), type_tag::bool_type);
  EXPECT_EQ(a.get<bool>(), true);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, CharConstructor) {
  any a('a');
  EXPECT_EQ(a.type(), type_tag::char_type);
  EXPECT_EQ(a.get<char>(), 'a');
  EXPECT_FALSE(!a);
}

TEST(AnyTest, FloatConstructor) {
  any a(3.14f);
  EXPECT_EQ(a.type(), type_tag::float_type);
  EXPECT_FLOAT_EQ(a.get<float>(), 3.14f);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, DoubleConstructor) {
  any a(3.14159);
  EXPECT_EQ(a.type(), type_tag::double_type);
  EXPECT_DOUBLE_EQ(a.get<double>(), 3.14159);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, StringConstructor) {
  std::string_view str("Hello, World!");
  any a(str);
  EXPECT_EQ(a.type(), type_tag::string_type);
  EXPECT_EQ(a.get<std::string_view>(), str);
  EXPECT_FALSE(!a);
}

TEST(AnyTest, EqualityOperator) {
  any a1(42);
  any a2(42);
  any a3(43);

  EXPECT_TRUE(a1 == a2);
  EXPECT_FALSE(a1 == a3);
}

TEST(AnyTest, InequalityOperator) {
  any a1(42);
  any a2(42);
  any a3(43);

  EXPECT_FALSE(a1 != a2);
  EXPECT_TRUE(a1 != a3);
}

TEST(AnyTest, StringEqualityOperator) {
  any a1("Hello");
  any a2("Hello");
  any a3("World");

  EXPECT_TRUE(a1 == a2);
  EXPECT_FALSE(a1 == a3);
}

TEST(AnyTest, StringInequalityOperator) {
  any a1("Hello");
  any a2("Hello");
  any a3("World");

  EXPECT_FALSE(a1 != a2);
  EXPECT_TRUE(a1 != a3);
}

TEST(ViewTest, AddGet) {
  char buf[256];
  std::memset(buf, 0, sizeof(buf));

  view v(buf, sizeof(buf));
  EXPECT_EQ(v.capacity(), 15);
  EXPECT_EQ(v.count(), 0);

  EXPECT_TRUE(v.add(any(1)));
  EXPECT_TRUE(v.add(any('c')));
  EXPECT_TRUE(v.add(any(true)));
  EXPECT_EQ(v.count(), 3);

  auto a = v.get(0);
  EXPECT_EQ(a.type(), type_tag::int_type);
  EXPECT_EQ(a.get<int>(), 1);

  auto b = v.get(1);
  EXPECT_EQ(b.type(), type_tag::char_type);
  EXPECT_EQ(b.get<char>(), 'c');

  auto c = v.get(2);
  EXPECT_EQ(c.type(), type_tag::bool_type);
  EXPECT_EQ(c.get<bool>(), true);
}