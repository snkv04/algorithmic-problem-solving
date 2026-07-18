#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool dfs(int si, int pi, vector<vector<int>> &mem, string &s, string &p) {
        if (si == s.size() && pi == p.size()) return true;
        if (pi == p.size()) return false;
        if (mem[si][pi] != -1) return mem[si][pi];

        char cs = si < s.size() ? s[si] : ' ', cp = p[pi];
        int &result = mem[si][pi];
        if (cp == '?') {
            if (cs != ' ') {
                result = dfs(si + 1, pi + 1, mem, s, p);
            } else {
                result = 0;
            }
        } else if (cp == '*') {
            result = (
                (si < s.size() ? dfs(si + 1, pi + 1, mem, s, p) : false) ||
                (si < s.size() ? dfs(si + 1, pi, mem, s, p) : false) ||
                dfs(si, pi + 1, mem, s, p)
            );
        } else {
            if (cs == cp) {
                result = dfs(si + 1, pi + 1, mem, s, p);
            } else {
                result = 0;
            }
        }
        return result;
    }

public:
    bool isMatch(string s, string p) {
        if (s.empty()) {
            bool valid = true;
            for (const char &c : p) {
                if (c != '*') valid = false;
            }
            return valid;
        }
        if (p.empty()) {
            return false;
        }

        vector<vector<int>> mem(s.size() + 1, vector<int>(p.size() + 1, -1));
        return dfs(0, 0, mem, s, p);
    }
};
