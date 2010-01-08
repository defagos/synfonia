#include <gtest/gtest.h>

#include "core/exception.h"

using core::Exception;

namespace {
  EXCEPTION_DECLARE_BASIC(BasicException, Exception)
  EXCEPTION_IMPLEMENT_BASIC(BasicException, Exception)
}

/**
 * Test creation of a basic exception class
 */
TEST(Exception, Basic)
{
  try {
    throw BasicException("Exception message");
  }
  catch (const Exception &e) {
    EXPECT_STREQ("Exception message", e.what());
  }
}
