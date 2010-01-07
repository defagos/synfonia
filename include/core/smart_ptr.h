#pragma once
#ifndef SMART_PTR_H
#define SMART_PTR_H

#include "core/platform.h"

// scoped_ptr is not in tr1 but has better semantics than std::auto_ptr. Since it 
// is still useful, we make the one from Boost available
#include <boost/scoped_ptr.hpp>

// Until all compilers implement smart pointers, we need to cope with those which
// don't
#if PLATFORM_USE_NATIVE_TR1
  // Use native smart pointer implementation
  #include <memory>
#else
  // Use Boost smart pointer implementations
  #include <boost/tr1/memory.hpp>
#endif

#endif
