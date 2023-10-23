#include "log.hpp"
#include <gtest/gtest.h>

TEST(LogTest, Constructor_Positive) {

  flog::log l(flog::level::INFO, "test.cpp", 10, "Message");

  // Assert statements to validate the log object
  EXPECT_EQ(l.level, flog::level::INFO);
  EXPECT_EQ(l.file, "test.cpp");
  EXPECT_EQ(l.line, 10);
  // Add more assertions as needed
}
