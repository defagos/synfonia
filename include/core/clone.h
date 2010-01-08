#pragma once
#ifndef CLONE_H
#define CLONE_H

namespace core {

/**
 * ICloneable interface. 
 * <p>
 * To get a cloneable class, simply inherit from ICloneable, implement
 * the copy constructor and use the CLONE_IMPL(className) macro within
 * the class definition.
 *
 * @author defagos
 */
class ICloneable {
public:
  /**
   * Returns a pointer to a heap-allocated clone of the object
   */
  virtual ICloneable *clone() const = 0;
  virtual ~ICloneable();
};

inline ICloneable::~ICloneable()
{}

} // namespace core

/**
 * Helper macro for implementing the clone interface in classes
 * implementing the ICloneable interface
 */
#define CLONE_IMPL(className)                 \
  className *clone() const                    \
  {                                           \
    return new className(*this);              \
  }

#endif
