#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    void dfs(TreeNode *curr, vector<int> &values) {
        if (curr == nullptr) return;

        values.push_back(curr->val);
        dfs(curr->left, values);
        dfs(curr->right, values);
    }

    TreeNode* dfs2(vector<int> &values, int l, int r) {
        if (r < l) return nullptr;

        int idx = (l + r) / 2;
        TreeNode *curr = new TreeNode(values[idx]);
        curr->left = dfs2(values, l, idx - 1);
        curr->right = dfs2(values, idx + 1, r);
        return curr;
    }

public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> values;
        dfs(root, values);
        sort(values.begin(), values.end());

        return dfs2(values, 0, values.size() - 1);
    }
};
