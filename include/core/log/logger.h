#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include <map>
#include <string>

#include "core/hash_table.h"
#include "core/smart_ptr.h"

namespace core {
namespace log {

class LoggingLevel {
public:
  static const LoggingLevel &trace();
  static const LoggingLevel &debug();
  static const LoggingLevel &info();
  static const LoggingLevel &warning();
  static const LoggingLevel &error();
  static const LoggingLevel &fatal();

  const std::string &getDescription() const;
  int getLevel() const;

private:
  explicit LoggingLevel(const std::string &description, int level);

  std::string m_description;
  int m_level;
};

inline const std::string &LoggingLevel::getDescription() const
{
  return m_description;
}

inline int LoggingLevel::getLevel() const
{
  return m_level;
}

class LoggingEvent {
public:
  explicit LoggingEvent(const LoggingLevel &loggingLevel, const std::string &message);
  LoggingLevel getLoggingLevel() const;
  std::string getMessage() const;

private:
  LoggingLevel m_loggingLevel;
  std::string m_message;
};

inline LoggingLevel LoggingEvent::getLoggingLevel() const
{
  return m_loggingLevel;
}

inline std::string LoggingEvent::getMessage() const
{
  return m_message;
}

class Appender;

class Logger : private boost::noncopyable {
public:
  typedef std::tr1::shared_ptr<Logger> Ptr;
  typedef std::tr1::shared_ptr<Appender> AppenderPtr;

  static Ptr getLogger(const std::string &name);

  std::string getName() const;

  LoggingLevel getLevel() const;
  void setLevel(const LoggingLevel &loggingLevel);

  void addAppender(const AppenderPtr &pAppender);
  void removeAppender(const std::string &name);

  void trace(const std::string &message) const;
  void debug(const std::string &message) const;
  void info(const std::string &message) const;
  void warning(const std::string &message) const;
  void error(const std::string &message) const;
  void fatal(const std::string &message) const;

  void enable();
  void disable();
  bool isEnabled() const;

private:
  typedef std::tr1::unordered_map<std::string, Ptr> LoggerMap;
  typedef std::tr1::unordered_map<std::string, AppenderPtr> AppenderMap;

  explicit Logger(const std::string &name, const LoggingLevel &loggingLevel);
  void log(const std::string &message, const LoggingLevel &loggingLevel) const;

  static LoggerMap sm_loggers;
  static boost::mutex sm_mutex;

  std::string m_name;
  LoggingLevel m_loggingLevel;
  bool m_isEnabled;  
  AppenderMap m_appenders;
  mutable boost::mutex m_mutex;
};

inline std::string Logger::getName() const
{
  return m_name;
}

inline void Logger::trace(const std::string &message) const
{
  log(message, LoggingLevel::trace());
}

inline void Logger::debug(const std::string &message) const
{
  log(message, LoggingLevel::debug());
}

inline void Logger::info(const std::string &message) const
{
  log(message, LoggingLevel::info());
}

inline void Logger::warning(const std::string &message) const
{
  log(message, LoggingLevel::warning());
}

inline void Logger::error(const std::string &message) const
{
  log(message, LoggingLevel::error());
}

inline void Logger::fatal(const std::string &message) const
{
  log(message, LoggingLevel::fatal());
}

} // namespace log
} // namespace core

#endif
