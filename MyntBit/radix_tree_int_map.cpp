#include <vector>
#include <cstdint>
#include <algorithm>
#include <array>

class RadixMap {
private:
    struct Node {
        std::array<Node*, 256> children{nullptr};
        uint64_t subtree_cnt{0};
        uint64_t value;
    };

    Node *root;

    void deallocate(Node *curr) {
        for (int block = 0; block < 256; ++block) {
            if (curr->children[block]) {
                deallocate(curr->children[block]);
            }
        }
        delete curr;
    }

public:
    RadixMap() {
        root = new Node();
    }

    ~RadixMap() {
        // just recursively destroys everything
        deallocate(root);
        root = nullptr;
    }

    void insert(uint64_t key, uint64_t value) {
        // keeps track of path, to increment subtree counts
        // in the case that the key does not already exist
        std::array<Node*, 9> path;
        path[0] = root;
        Node *curr = root;
        for (int i = 1; i <= 8; ++i) {
            int shift = (i - 1) * 8;
            int block = (key >> shift) & 255;
            if (curr->children[block] == nullptr) {
                curr->children[block] = new Node();
            }
            curr = curr->children[block];
            path[i] = curr;
        }

        // updates value and, optionally, subtree counts
        if (path[8]->subtree_cnt == 0) {
            // key didn't already exist
            for (int depth = 0; depth <= 8; ++depth) {
                path[depth]->subtree_cnt += 1;
            }
        }
        path[8]->value = value;
    }

    bool search(uint64_t key, uint64_t& outValue) {
        Node *curr = root;
        for (int shift = 0; shift < 64; shift += 8) {
            int block = (key >> shift) & 255;
            if (curr->children[block] == nullptr) {
                outValue = -1;
                return false;
            } else {
                curr = curr->children[block];
            }
        }
        outValue = curr->value;
        return true;
    }

    bool remove(uint64_t key) {
        // builds path
        std::array<Node*, 9> path;
        std::array<int, 8> blocks;
        path[0] = root;
        Node *curr = root;
        for (int i = 1; i <= 8; ++i) {
            int shift = (i - 1) * 8;
            int block = (key >> shift) & 255;
            if (curr->children[block] == nullptr) {
                return false;
            } else {
                curr = curr->children[block];
                path[i] = curr;
                blocks[i - 1] = block;
            }
        }

        // walks through path backward
        for (int i = 7; i >= 0; --i) {
            Node *parent = path[i], *child = path[i + 1];
            child->subtree_cnt -= 1;
            if (child->subtree_cnt == 0) {
                delete child;
                parent->children[blocks[i]] = nullptr;
            }
        }
        root->subtree_cnt -= 1;
        return true;
    }
};
