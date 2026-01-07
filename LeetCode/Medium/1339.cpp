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
    long long ans, sum;

    long long dfs(TreeNode *node) {
        if (node == nullptr) return 0;

        return node->val + dfs(node->left) + dfs(node->right);
    }

    long long dfs2(TreeNode *node) {
        if (node == nullptr) return 0;

        long long subtree_sum = node->val;
        subtree_sum += dfs2(node->left);
        subtree_sum += dfs2(node->right);
        ans = max(ans, (sum - subtree_sum) * subtree_sum);
        return subtree_sum;
    }

public:
    int maxProduct(TreeNode* root) {
        sum = dfs(root);
        ans = 0;
        dfs2(root);
        return ans % static_cast<long long>(1e9 + 7);
    }
};
