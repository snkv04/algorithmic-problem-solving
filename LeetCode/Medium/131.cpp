class Solution {
    vector<vector<string>> ans;

    bool is_palindrome(string &s, int l, int r) {
        int len = (r - l + 1);
        for (int i = 0; i < len / 2; ++i) {
            if (s[l+i] != s[r-i]) return false;
        }
        return true;
    }

    void dfs(int l, vector<string> &curr, string &s, int n) {
        if (l == n) {
            vector<string> copy = curr;
            ans.push_back(copy);
            return;
        }

        for (int r = l + 1; r <= n; ++r) {
            if (is_palindrome(s, l, r-1)) {
                curr.push_back(s.substr(l, r-l));
                dfs(r, curr, s, n);
                curr.pop_back();
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
        ans.clear();
        vector<string> curr;
        dfs(0, curr, s, s.size());
        return ans;
    }
};
