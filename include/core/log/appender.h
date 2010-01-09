#pragma once
#ifndef APPENDER_H
#define APPENDER_H

#include <string>

#include <boost/noncopyable.hpp>

namespace core {
namespace log {

class LoggingEvent;

class Appender : private boost::noncopyable {
public:
  std::string getName() const;
  virtual void append(const LoggingEvent &logEvent) = 0;

protected:
  Appender(const std::string &name);

private:
  std::string m_name;
};

inline std::string Appender::getName() const
{
  return m_name;
}

} // namespace log
} // namespace core

#endif
