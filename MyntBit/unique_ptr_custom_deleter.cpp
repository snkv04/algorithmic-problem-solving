#include <memory>
#include <vector>
#include <iostream>

// --- MOCK LEGACY API (DO NOT MODIFY) ---
struct LegacyHandle {
    int id;
};

// Global log to track closed resource IDs for verification
static std::vector<double> closed_log;

LegacyHandle* open_legacy_resource(int id) {
    return new LegacyHandle{id};
}

void close_legacy_resource(LegacyHandle* handle) {
    if (handle) {
        closed_log.push_back(static_cast<double>(handle->id));
        delete handle;
    }
}
// ---------------------------------------

class SmartResourceWrapper {
private:
    using DeleterType = void(*)(LegacyHandle*);
    std::unique_ptr<LegacyHandle, DeleterType> resource;

public:
    SmartResourceWrapper(int id) :
        resource(open_legacy_resource(id), close_legacy_resource) {}

    int getId() const {
        if (resource.get() == nullptr) {
            return -1;
        } else {
            return resource->id;
        }
    }
};
