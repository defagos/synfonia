#include "core/log/logger.h"

#include "core/log/appender.h"

namespace core {
namespace log {

const LoggingLevel &LoggingLevel::trace()
{
  static const LoggingLevel logLevel("[TRACE]", 0);
  return logLevel;
}

const LoggingLevel &LoggingLevel::debug()
{
  static const LoggingLevel logLevel("[DEBUG]", 1);
  return logLevel;
}

const LoggingLevel &LoggingLevel::info()
{
  static const LoggingLevel logLevel("[INFO]", 2);
  return logLevel;
}

const LoggingLevel &LoggingLevel::warning()
{
  static const LoggingLevel logLevel("[WARNING]", 3);
  return logLevel;
}

const LoggingLevel &LoggingLevel::error()
{
  static const LoggingLevel logLevel("[ERROR]", 4);
  return logLevel;
}

const LoggingLevel &LoggingLevel::fatal()
{
  static const LoggingLevel logLevel("[FATAL]", 5);
  return logLevel;
}

LoggingLevel::LoggingLevel(const std::string &description, int level)
: m_description(description),
  m_level(level)
{}

LoggingEvent::LoggingEvent(const LoggingLevel &loggingLevel, const std::string &message)
: m_loggingLevel(loggingLevel),
  m_message(message)
{}

Logger::Logger(const std::string &name)
: m_pImpl(new MutableLogger<NoLockOnAccess>(name))
{}

} // namespace log
} // namespace core
