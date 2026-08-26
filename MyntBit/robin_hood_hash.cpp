#include <vector>

struct RobinHoodMap {
    static const int TSIZE = 16;
    static const int EMPTY = -1;

    int keys[TSIZE];
    int values[TSIZE];

    RobinHoodMap() {
        for (int i = 0; i < TSIZE; ++i) keys[i] = EMPTY;
    }

    int hash(int k) const { return ((k % TSIZE) + TSIZE) % TSIZE; }

    // Probe distance for a key stored at slot s
    int probe_dist(int slot, int k) const {
        return (slot - hash(k) + TSIZE) % TSIZE;
    }

    // Insert key/value with Robin Hood displacement.
    void insert(int key, int value) {
        int base_slot = hash(key);
        for (int probe_distance = 0; ; ++probe_distance) {
            int curr_slot = (base_slot + probe_distance) % TSIZE;
            if (keys[curr_slot] == EMPTY || keys[curr_slot] == key) {
                keys[curr_slot] = key;
                values[curr_slot] = value;
                break;
            } else if (probe_distance > probe_dist(curr_slot, keys[curr_slot])) {
                std::swap(key, keys[curr_slot]);
                std::swap(value, values[curr_slot]);
                base_slot = curr_slot;
                probe_distance = probe_dist(curr_slot, key);
            }
        }
    }

    // Lookup key. Return value if found, -1 if not found.
    int lookup(int key) const {
        int base_slot = hash(key);
        for (int dist = 0; dist < TSIZE; ++dist) {
            int curr_slot = (base_slot + dist) % TSIZE;
            if (keys[curr_slot] == key) {
                return values[curr_slot];
            } else if (keys[curr_slot] == EMPTY || dist > probe_dist(curr_slot, keys[curr_slot])) {
                break;
            }
        }
        return -1;
    }
};
