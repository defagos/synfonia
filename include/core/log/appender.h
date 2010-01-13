#pragma once
#ifndef APPENDER_H
#define APPENDER_H

#include <string>

#include <boost/noncopyable.hpp>

namespace core {
namespace log {

class LoggingEvent;

class IAppender : private boost::noncopyable {
public:
  virtual void append(const LoggingEvent &logEvent) = 0;
  ~IAppender();
};

inline IAppender::~IAppender()
{}

class ConsoleAppender : public IAppender {
public:
  virtual void append(const LoggingEvent &logEvent);
};

} // namespace log
} // namespace core

#endif
