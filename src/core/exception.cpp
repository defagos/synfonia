#include "core/exception.h"

#include <ostream>
#include <typeinfo>

namespace core {

Exception::Exception(const std::string &message)
: m_message(message)
{}

Exception::Exception(const std::string &message, const Exception &nested)
: m_message(message),
  m_nestedStackTrace(nested.stackTrace())
{
  // We do not save a clone of the nested exception, simply its stack trace.  We could,
  // but in C++ cloneable interfaces put a burden on the programmer subclassing a 
  // cloneable class. For a class like Exception, which is intended to be subclassed
  // easily, this would have been undesirable.
}

Exception::~Exception() throw()
{}

const char *Exception::className() const throw()
{
  /* Exception is a polymorphic class. This guarantees that typeid returns the proper type */
  return typeid(*this).name();
}

const char *Exception::what() const throw()
{
  return m_message.c_str();
}

std::string Exception::stackTrace() const
{
  std::string message = std::string(className()) + ": " + m_message;
  if (! m_nestedStackTrace.empty()) {
    message.append("\n  at " + m_nestedStackTrace);
  }
  return message;
}

std::ostream& operator<<(std::ostream& os, const Exception &exception)
{
  os << exception.what();
  return os;
}

} // namespace core
