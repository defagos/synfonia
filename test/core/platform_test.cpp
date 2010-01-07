#include <gtest/gtest.h>

#include "core/platform.h"

/**
 * Test the integer sizes
 */
TEST(Platform, TypeSizes)
{
  EXPECT_EQ(1, sizeof(int8));
  EXPECT_EQ(2, sizeof(int16));
  EXPECT_EQ(4, sizeof(int32));
  EXPECT_EQ(8, sizeof(int64));
}
