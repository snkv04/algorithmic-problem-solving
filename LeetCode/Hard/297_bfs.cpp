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

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream oss;
        queue<TreeNode*> q;
        q.push(root);
        while (q.size()) {
            TreeNode *node = q.front();
            q.pop();

            if (node == nullptr) {
                oss << bitset<BITSET_SIZE>(INF).to_string();
            } else {
                oss << bitset<BITSET_SIZE>(node->val).to_string();
                q.push(node->left);
                q.push(node->right);
            }
        }
        return oss.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() == BITSET_SIZE) return nullptr;

        // Initialize root
        int first_val = _bitset_to_int(bitset<BITSET_SIZE>(data.substr(0, BITSET_SIZE)));
        TreeNode *root = new TreeNode(first_val);

        // Traverse remaining nodes
        queue<TreeNode*> q;
        q.push(root);
        int idx = BITSET_SIZE;
        while (q.size()) {
            TreeNode *node = q.front();
            q.pop();

            // Each node corresponds to the parent of the next two values
            // in the string
            int left_val = _bitset_to_int(bitset<BITSET_SIZE>(data.substr(idx, BITSET_SIZE)));
            int right_val = _bitset_to_int(bitset<BITSET_SIZE>(data.substr(idx + BITSET_SIZE, BITSET_SIZE)));
            idx += 2 * BITSET_SIZE;
            if (left_val != INF) {
                node->left = new TreeNode(left_val);
                q.push(node->left);
            }
            if (right_val != INF) {
                node->right = new TreeNode(right_val);
                q.push(node->right);
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
