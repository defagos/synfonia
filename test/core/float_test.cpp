#include <gtest/gtest.h>

#include "core/float.h"

/**
 * Test floating point number comparisons
 */
TEST(FloatComparisons, Correctness)
{
  EXPECT_TRUE(floateq(1.0, 1.0));
  EXPECT_TRUE(floateq(0., -0.0));
  EXPECT_FALSE(floateq(0.0, 1.0));

  EXPECT_TRUE(floatle(0.0, 1.0));
  EXPECT_TRUE(floatle(1.0, 1.0));
  EXPECT_FALSE(floatle(1.0, 0.0));

  EXPECT_TRUE(floatge(1.0, 0.0));
  EXPECT_TRUE(floatge(1.0, 1.0));
  EXPECT_FALSE(floatge(0.0, 1.0));

  EXPECT_TRUE(floatgt(1.0, 0.0));
  EXPECT_FALSE(floatgt(1.0, 1.0));

  EXPECT_TRUE(floatlt(0.0, 1.0));
  EXPECT_FALSE(floatlt(1.0, 1.0));

  EXPECT_TRUE(doubleeq(1.0, 1.0));
  EXPECT_TRUE(doubleeq(0., -0.0));
  EXPECT_FALSE(doubleeq(0.0, 1.0));
  EXPECT_TRUE(doublele(0.0, 1.0));
  EXPECT_TRUE(doublele(1.0, 1.0));
  EXPECT_FALSE(doublele(1.0, 0.0));

  EXPECT_TRUE(doublege(1.0, 0.0));
  EXPECT_TRUE(doublege(1.0, 1.0));
  EXPECT_FALSE(doublege(0.0, 1.0));

  EXPECT_TRUE(doublegt(1.0, 0.0));
  EXPECT_FALSE(doublegt(1.0, 1.0));

  EXPECT_TRUE(doublelt(0.0, 1.0));
  EXPECT_FALSE(doublelt(1.0, 1.0));
}
