#include <atomic>
#include <new>

// Use this fallback if the hardware constant is missing
#ifndef __cpp_lib_hardware_interference_size
    constexpr std::size_t hardware_destructive_interference_size = 64;
#else
    using std::hardware_destructive_interference_size;
#endif

struct CacheAlignedCounters {
    // This ensures `a` and `b` fall onto separate cache lines
    // to avoid false sharing
    alignas(hardware_destructive_interference_size) std::atomic<long long> a{0};
    alignas(hardware_destructive_interference_size) std::atomic<long long> b{0};
};
