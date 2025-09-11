/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
private:
    static constexpr int BITSET_SIZE = 14;
    static constexpr int INF = 8000;

    int _bitset_to_int(bitset<BITSET_SIZE> bs) {
        unsigned long long val = bs.to_ullong();
        if (bs[BITSET_SIZE - 1]) {
            val -= (1 << BITSET_SIZE);
        }
        return val;
    }

    int _deserialize(TreeNode *node, string &data, int idx) {
        int left_val = _bitset_to_int(bitset<BITSET_SIZE>(data.substr(idx, BITSET_SIZE)));
        if (left_val == INF) {
            idx += BITSET_SIZE;
        } else {
            node->left = new TreeNode(left_val);
            idx = _deserialize(node->left, data, idx + BITSET_SIZE);
        }

        int right_val = _bitset_to_int(bitset<BITSET_SIZE>(data.substr(idx, BITSET_SIZE)));
        if (right_val == INF) {
            idx += BITSET_SIZE;
        } else {
            node->right = new TreeNode(right_val);
            idx = _deserialize(node->right, data, idx + BITSET_SIZE);
        }
        return idx;
    }

    void _load_into_stringstream(TreeNode *root, ostringstream &oss) {
        if (root == nullptr) {
            oss << (bitset<BITSET_SIZE>(INF));
            return;
        }

        oss << bitset<BITSET_SIZE>(root->val);
        _load_into_stringstream(root->left, oss);
        _load_into_stringstream(root->right, oss);
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return bitset<BITSET_SIZE>(INF).to_string();
        }

        ostringstream oss;
        _load_into_stringstream(root, oss);
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() == BITSET_SIZE) return nullptr;

        int first_val = _bitset_to_int(bitset<BITSET_SIZE>(data.substr(0, BITSET_SIZE)));
        TreeNode *root = new TreeNode(first_val);
        _deserialize(root, data, BITSET_SIZE);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
