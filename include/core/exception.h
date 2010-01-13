#pragma once
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <iosfwd>
#include <string>

namespace core {

/**
 * Exception class. 
 * <p>
 * Base class for defining exceptions. Provides the standard std::exception
 * class with some additional features like exception nesting.
 *
 * @author defagos
 */
class Exception : public std::exception {
public:
  /**
   * Constructor whithout exception nesting
   *
   * @param message the exception message
   */
  explicit Exception(const std::string &message);
  /**
   * Constructor with exception nesting
   *
   * @param message the exception message
   * @param nested the nested exception
   */
  explicit Exception(const std::string &message, const Exception &nested);
  virtual ~Exception() throw();
  /**
   * Returns the class name. The name returned is implementation-defined and
   * should only be used for information purposes.
   */
  const char *className() const throw();
  /**
   * Returns the exception message
   */
  virtual const char *what() const throw();
  /**
   * Returns a stack trace of the exception
   */
  std::string stackTrace() const;

private:
  std::string m_message;              // Exception message
  std::string m_nestedStackTrace;     // Stack trace of the nested exception
};

/**
 * Writes the exception message to an output stream
 */
std::ostream& operator<<(std::ostream& os, const Exception &exception);

/**
 * Helper macro to quickly declare a basic exception class Name derived from
 * class Base
 */
#define EXCEPTION_DECLARE_BASIC(Name, Base)                             \
  class Name : public Base {                                            \
  public:                                                               \
    Name(const std::string &message);                                   \
    Name(const std::string &message, const Exception &nested);          \
  };

/**
 * Helper macro to quickly implement a basic exception class Name derived from
 * class Base
 */
#define EXCEPTION_IMPLEMENT_BASIC(Name, Base)                           \
  Name::Name(const std::string &message)                                \
  : Base(message)                                                       \
  {}                                                                    \
                                                                        \
  Name::Name(const std::string &message, const Exception &nested)       \
  : Base(message, nested)                                               \
  {}

} // namespace core

#endif
