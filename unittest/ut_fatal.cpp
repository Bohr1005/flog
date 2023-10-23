#include "fatal.hpp"
#include <gtest/gtest.h>

using namespace flog;
TEST(FlogTest, FatalError) { EXPECT_THROW(FATAL("test"), flog::fatal_error); }