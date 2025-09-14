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
class Solution {
private:
    int ans;

    int _recurse(TreeNode *node) {
        int best = node->val;
        int left = 0, right = 0;
        if (node->left != nullptr) left = _recurse(node->left);
        if (node->right != nullptr) right = _recurse(node->right);

        // goes through node without either end (necessarily) being
        // on the node
        ans = max(ans, left + node->val + right);

        // goes through the node with one end on the node
        best = max(best, max(node->val + left, node->val + right));
        ans = max(ans, best);
        return best;
    }

public:
    int maxPathSum(TreeNode* root) {
        ans = -1e9;
        _recurse(root);
        return ans;
    }
};
