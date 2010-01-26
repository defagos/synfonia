#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include <string>
#include <utility>

#include "core/hash_table.h"
#include "core/smart_ptr.h"
#include "core/log/appender.h"

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

inline bool operator<(const LoggingLevel &lhs, const LoggingLevel &rhs)
{
  return lhs.getLevel() < rhs.getLevel();
}

inline bool operator==(const LoggingLevel &lhs, const LoggingLevel &rhs)
{
  return !operator<(lhs, rhs) && !operator<(rhs, lhs);
}

using namespace std::rel_ops;

// TODO: Add more information (timestamp, etc.)
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

class ILogger : private boost::noncopyable {
public:
  virtual std::string getName() const = 0;
  virtual void trace(const std::string &message) const = 0;
  virtual void debug(const std::string &message) const = 0;
  virtual void info(const std::string &message) const = 0;
  virtual void warning(const std::string &message) const = 0;
  virtual void error(const std::string &message) const = 0;
  virtual void fatal(const std::string &message) const = 0;
  virtual ~ILogger();
};

inline ILogger::~ILogger()
{}

class NoLockOnAccess {
public:
  class Lock {
    // Empty inline default ctor and dtor
  };

protected:
  ~NoLockOnAccess()
  {}
};

class LockOnAccess {
public:
  class Lock {
  public:
    Lock()
    {
      m_mutex.lock();
    }
    ~Lock()
    {
      m_mutex.unlock();
    }

  private:
    boost::mutex m_mutex;
  };

protected:
  ~LockOnAccess()
  {}
};

class IAppender;

template<class LockingPolicy>
class MutableLogger : public ILogger, public LockingPolicy {
public:
  MutableLogger(const std::string &name);

  virtual std::string getName() const;

  LoggingLevel getLoggingLevel() const;
  void setLoggingLevel(const LoggingLevel &loggingLevel);

  virtual void trace(const std::string &message) const;
  virtual void debug(const std::string &message) const;
  virtual void info(const std::string &message) const;
  virtual void warning(const std::string &message) const;
  virtual void error(const std::string &message) const;
  virtual void fatal(const std::string &message) const;

  void addAppender(const std::string &name);
  void removeAppender(const std::string &name);

private:
  typedef std::tr1::shared_ptr<IAppender> IAppenderPtr;
  typedef std::tr1::unordered_map<std::string, IAppenderPtr> IAppenderMap;

  void log(const LoggingLevel &loggingLevel, const std::string &message) const;

  std::string m_name;
  LoggingLevel m_loggingLevel;
  IAppenderMap m_appenders;
};

// TODO: Read level from config and set it. AddAppenders setup in configuration file
template<class LockingPolicy>
MutableLogger<LockingPolicy>::MutableLogger(const std::string &name)
: m_name(name),
//TODO: Must be read from file, for the moment some default value
  m_loggingLevel(LoggingLevel::debug())
{
  //TODO: Must be read from file, here just for tests
  m_appenders["ConsoleAppenderTest"] = IAppenderPtr(new ConsoleAppender());
}

template<class LockingPolicy>
inline std::string MutableLogger<LockingPolicy>::getName() const
{
  // Read-only, no lock required here
  return m_name;
}

template<class LockingPolicy>
LoggingLevel MutableLogger<LockingPolicy>::getLoggingLevel() const
{
  typename LockingPolicy::Lock lock;
  return m_loggingLevel;
}

template<class LockingPolicy>
void MutableLogger<LockingPolicy>::setLoggingLevel(const LoggingLevel &loggingLevel)
{
  typename LockingPolicy::Lock lock;
  m_loggingLevel = loggingLevel;
}

template<class LockingPolicy>
void MutableLogger<LockingPolicy>::trace(const std::string &message) const
{
  typename LockingPolicy::Lock lock;
  if (m_loggingLevel <= LoggingLevel::trace()) {
    log(LoggingLevel::trace(), message);
  }
}

template<class LockingPolicy>
void MutableLogger<LockingPolicy>::debug(const std::string &message) const
{
  typename LockingPolicy::Lock lock;
  if (m_loggingLevel <= LoggingLevel::debug()) {
    log(LoggingLevel::debug(), message);
  }
}

template<class LockingPolicy>
void MutableLogger<LockingPolicy>::info(const std::string &message) const
{
  typename LockingPolicy::Lock lock;
  if (m_loggingLevel <= LoggingLevel::info()) {
    log(LoggingLevel::info(), message);
  }
}

template<class LockingPolicy>
void MutableLogger<LockingPolicy>::warning(const std::string &message) const
{
  typename LockingPolicy::Lock lock;
  if (m_loggingLevel <= LoggingLevel::warning()) {
    log(LoggingLevel::warning(), message);
  }
}

template<class LockingPolicy>
void MutableLogger<LockingPolicy>::error(const std::string &message) const
{
  typename LockingPolicy::Lock lock;
  if (m_loggingLevel <= LoggingLevel::error()) {
    log(LoggingLevel::error(), message);
  }
}

template<class LockingPolicy>
void MutableLogger<LockingPolicy>::fatal(const std::string &message) const
{
  typename LockingPolicy::Lock lock;
  if (m_loggingLevel <= LoggingLevel::fatal()) {
    log(LoggingLevel::fatal(), message);
  }
}

template<class LockingPolicy>
void MutableLogger<LockingPolicy>::addAppender(const std::string &name)
{
  typename LockingPolicy::Lock lock;

  // TODO: Get appender and attach it
}

template<class LockingPolicy>
void MutableLogger<LockingPolicy>::removeAppender(const std::string &name)
{
  typename LockingPolicy::Lock lock;
  m_appenders.erase(name);
}

template<class LockingPolicy>
void MutableLogger<LockingPolicy>::log(const LoggingLevel &loggingLevel, const std::string &message) const
{
  LoggingEvent loggingEvent(loggingLevel, message);

  typename LockingPolicy::Lock lock;
  for (IAppenderMap::const_iterator it = m_appenders.begin();
      it != m_appenders.end(); ++it) {
    it->second->append(loggingEvent);
  }
}

class Logger : public ILogger {
public:
  Logger(const std::string &name);

  virtual std::string getName() const;
  LoggingLevel getLoggingLevel() const;

  virtual void trace(const std::string &message) const;
  virtual void debug(const std::string &message) const;
  virtual void info(const std::string &message) const;
  virtual void warning(const std::string &message) const;
  virtual void error(const std::string &message) const;
  virtual void fatal(const std::string &message) const;

private:
  boost::scoped_ptr<MutableLogger<NoLockOnAccess> > m_pImpl;
};

inline std::string Logger::getName() const
{
  return m_pImpl->getName();
}

inline LoggingLevel Logger::getLoggingLevel() const
{
  return m_pImpl->getLoggingLevel();
}

inline void Logger::trace(const std::string &message) const
{
  m_pImpl->trace(message);
}

inline void Logger::debug(const std::string &message) const
{
  m_pImpl->debug(message);
}

inline void Logger::info(const std::string &message) const
{
  m_pImpl->info(message);
}

inline void Logger::warning(const std::string &message) const
{
  m_pImpl->warning(message);
}

inline void Logger::error(const std::string &message) const
{
  m_pImpl->error(message);
}

inline void Logger::fatal(const std::string &message) const
{
  m_pImpl->fatal(message);
}

} // namespace log
} // namespace core

#endif
