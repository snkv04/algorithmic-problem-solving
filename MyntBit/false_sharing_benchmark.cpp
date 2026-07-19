#include <atomic>
#include <cstdint>

class AlignedCounters {
private:
    alignas(64) std::atomic<long long> a;
    alignas(64) std::atomic<long long> b;
    
public:
    AlignedCounters() {
        a = 0;
        b = 0;
    }

    void incrementA() {
        a += 1;
    }

    void incrementB() {
        b += 1;
    }

    long long getA() const {
        return a; 
    }

    long long getB() const {
        return b;
    }
    
    const void* getAddrA() const {
        return &a;
    }
    
    const void* getAddrB() const {
        return &b;
    }
};
