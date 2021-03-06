// Copyright (c) Eric Nodwell
// See LICENSE for details.


#ifndef N88UTIL_TrackingAllocator_hpp_INCLUDED
#define N88UTIL_TrackingAllocator_hpp_INCLUDED

#include <boost/thread/tss.hpp>
#include <cstdlib>
#include "n88util_export.h"


namespace n88
{

  struct N88UTIL_EXPORT TrackingAllocatorValues
  {
    size_t current;
    size_t peak;
  };

  /**
   * A very elementary class to help you count up when you allocate
   * memory, and count down when you free it. The special feature of
   * this class is that the counter is statically allocated per-thread:
   * every thread gets its own. Thus you can safely use it in multi-threaded
   * programs without the speed impact of mutexes or atomic operations.
   */
  class N88UTIL_EXPORT TrackingAllocator
  {
    public:
      static void* allocate(size_t size);
      static void release(void* p, size_t size);
      static void external_increase (size_t size);
      static void external_decrease (size_t size);
      static size_t get_current_allocated();
      static size_t get_peak_allocated();
      
    private:
      static boost::thread_specific_ptr<TrackingAllocatorValues> allocated;

  };
  
} // namespace n88

#endif
