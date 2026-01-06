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

constexpr int INF = 2e9;

class Solution {
    void recurse(
        TreeNode *curr_node, int depth, unordered_map<int, int> &level_to_sum
    ) {
        if (curr_node == nullptr) {
            return;
        }

        // process current node
        if (level_to_sum.find(depth) == level_to_sum.end()) {
            level_to_sum[depth] = 0;
        }
        level_to_sum[depth] += curr_node->val;

        // process children
        recurse(curr_node->left, depth + 1, level_to_sum);
        recurse(curr_node->right, depth + 1, level_to_sum);
    }
    
public:
    int maxLevelSum(TreeNode* root) {
        unordered_map<int, int> level_to_sum;
        recurse(root, 1, level_to_sum);

        int max_sum = -INF;
        for (const auto entry : level_to_sum) {
            max_sum = max(max_sum, entry.second);
        }

        int min_level = INF;
        for (const auto entry : level_to_sum) {
            if (entry.second == max_sum) {
                min_level = min(min_level, entry.first);
            }
        }
        return min_level;
    }
};
