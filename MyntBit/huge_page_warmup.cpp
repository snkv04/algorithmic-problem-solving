#include <vector>

constexpr int PAGE_SIZE = 4096;  // Standard (not huge) page size on many OSs
std::vector<char> buffer;
long warmup_pages(long size_bytes) {
    // Allocate buffer and touch each page to load it into the page table
    buffer.resize(size_bytes);
    size_t pages_touched = 0;
    for (size_t idx = 0; idx < size_bytes; idx += PAGE_SIZE) {
        buffer[idx] = '\0';  // Forces a page fault now, instead of later
        pages_touched += 1;
    }
    return pages_touched;
}
