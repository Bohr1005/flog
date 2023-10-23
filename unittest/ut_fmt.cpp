#include "fmt.hpp"
#include <gtest/gtest.h>
#include <sstream>

TEST(FlogTest, FormatPositiveTest) {
  std::stringstream ss;
  flog::format(ss, "Hello", "World", 123);
  EXPECT_EQ(ss.str(), "Hello World 123 ");
}

TEST(FlogTest, FormatNegativeTest) {
  std::stringstream ss;
  flog::format(ss, "Hello", "World", 123);
  EXPECT_NE(ss.str(), "Hello World 456 ");
}
