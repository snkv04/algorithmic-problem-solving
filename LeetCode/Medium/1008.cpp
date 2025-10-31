/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// class Solution {
//     TreeNode* generate(int &idx, vector<int> &preorder, int mn, int mx) {
//         if (idx >= preorder.size() || preorder[idx] < mn || preorder[idx] > mx) {
//             return nullptr;
//         }

//         int val = preorder[idx++];
//         TreeNode *node = new TreeNode(val);
//         node->left = generate(idx, preorder, mn, val);
//         node->right = generate(idx, preorder, val, mx);
//         return node;
//     }

// public:
//     TreeNode* bstFromPreorder(vector<int>& preorder) {
//         int idx = 0;
//         return generate(idx, preorder, -1e9, 1e9);
//     }
// };
class Solution {
    void generate(TreeNode *node, int &idx, vector<int> &preorder, int mn, int mx) {
        if (
            idx < preorder.size() &&
            preorder[idx] < node->val &&
            preorder[idx] > mn
        ) {
            node->left = new TreeNode(preorder[idx++]);
            generate(node->left, idx, preorder, mn, node->val);
        }
        if (
            idx < preorder.size() &&
            preorder[idx] > node->val &&
            preorder[idx] < mx
        ) {
            node->right = new TreeNode(preorder[idx++]);
            generate(node->right, idx, preorder, node->val, mx);
        }
    }

public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        TreeNode *root = new TreeNode(preorder[0]);
        int idx = 1;
        generate(root, idx, preorder, -1e9, 1e9);
        return root;
    }
};
