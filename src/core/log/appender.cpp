#include "core/log/appender.h"

#include <iostream>

#include "core/log/logger.h"

namespace core {
namespace log {

void ConsoleAppender::append(const LoggingEvent &logEvent)
{
  //TODO: Just a very basic implementation, no thread-safety, just for tests
  std::cout << logEvent.getLoggingLevel().getDescription() << " " << logEvent.getMessage()
    << std::endl;
}

} // namespace log
} // namespace core
