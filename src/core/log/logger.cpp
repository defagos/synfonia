#include "core/log/logger.h"

#include <boost/thread/locks.hpp>

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
  static const LoggingLevel logLevel("[DEBUG]", 0);
  return logLevel;
}

const LoggingLevel &LoggingLevel::info()
{
  static const LoggingLevel logLevel("[INFO]", 0);
  return logLevel;
}

const LoggingLevel &LoggingLevel::warning()
{
  static const LoggingLevel logLevel("[WARNING]", 0);
  return logLevel;
}

const LoggingLevel &LoggingLevel::error()
{
  static const LoggingLevel logLevel("[ERROR]", 0);
  return logLevel;
}

const LoggingLevel &LoggingLevel::fatal()
{
  static const LoggingLevel logLevel("[FATAL]", 0);
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

Logger::Ptr Logger::getLogger(const std::string &name)
{
  /* Double-checked locking */
  LoggerMap::const_iterator it = sm_loggers.find(name);
  if (it == sm_loggers.end()) {
    boost::mutex::scoped_lock lock(sm_mutex);
    return sm_loggers[name];
  }

  return it->second;
}

LoggingLevel Logger::getLevel() const
{
  boost::mutex::scoped_lock lock(m_mutex);
  return m_loggingLevel;
}

void Logger::setLevel(const LoggingLevel &loggingLevel)
{
  boost::mutex::scoped_lock lock(m_mutex);
  m_loggingLevel = loggingLevel;
}

void Logger::addAppender(const AppenderPtr &pAppender)
{
  boost::mutex::scoped_lock lock(m_mutex);
  m_appenders[pAppender->getName()] = pAppender;
}

void Logger::removeAppender(const std::string &name)
{
  boost::mutex::scoped_lock lock(m_mutex);
  m_appenders.erase(name);
}

void Logger::enable()
{
  boost::mutex::scoped_lock lock(m_mutex);
  m_isEnabled = true;
}

void Logger::disable()
{
  boost::mutex::scoped_lock lock(m_mutex);
  m_isEnabled = false;
}

bool Logger::isEnabled() const
{
  boost::mutex::scoped_lock lokc(m_mutex);
  return m_isEnabled;
}

Logger::Logger(const std::string &name, const LoggingLevel &loggingLevel)
: m_name(name),
  m_loggingLevel(loggingLevel),
  m_isEnabled(true)
{}

void Logger::log(const std::string &message, const LoggingLevel &loggingLevel) const
{
  LoggingEvent loggingEvent(loggingLevel, message);

  boost::mutex::scoped_lock lock(m_mutex);
  for (AppenderMap::const_iterator it = m_appenders.begin();
      it != m_appenders.end(); ++it) {
    it->second->append(loggingEvent);
  }
}

} // namespace log
} // namespace core
