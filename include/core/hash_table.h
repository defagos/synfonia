#pragma once
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

// Until all compilers implement tr1 hash tables, we need to cope with those which
// don't
#if PLATFORM_USE_NATIVE_TR1
  // Use native hash table implementations
  #include <unordered_map>
  #include <unordered_set>
#else
  // Use Boost hash table implementations
  #include <boost/tr1/unordered_map.hpp>
  #include <boost/tr1/unordered_set.hpp>
#endif

#endif
