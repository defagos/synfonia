#include <gtest/gtest.h>

#include "core/smart_ptr.h"
#include "core/log/logger.h"

using namespace core::log;

//TODO: Better tests
TEST(Logger, someTest)
{
  using std::tr1::shared_ptr;

  shared_ptr<ILogger> pLogger(new Logger("DummyLogger"));

  pLogger->error("This is an error");
}
