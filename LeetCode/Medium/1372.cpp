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
    int ans;

    pair<int, int> dfs(TreeNode *node) {
        pair<int, int> result = {0, 0};
        if (node->left != nullptr) {
            pair<int, int> from_left = dfs(node->left);
            result.first = 1 + from_left.second;
        }
        if (node->right != nullptr) {
            pair<int, int> from_right = dfs(node->right);
            result.second = 1 + from_right.first;
        }
        ans = max(ans, max(result.first, result.second));
        return result;
    }

public:
    int longestZigZag(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};
