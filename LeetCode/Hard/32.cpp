#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.empty()) {
            return 0;
        }

        int n = s.size();
        vector<int> pre(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            pre[i] = pre[i - 1] + (s[i - 1] == '(' ? 1 : -1);
        }

        vector<int> next(n + 1, -1);
        stack<int> stk;
        stk.push(0);
        for (int i = 1; i <= n; ++i) {
            while (stk.size() && pre[stk.top()] >= pre[i]) {
                next[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }
        for (int i = 0; i <= n; ++i) {
            cout << next[i] << endl;
        }

        int ans = 0;
        vector<bool> visited(n + 1, false);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                int len = 0, curr = i;
                while (next[curr] != -1 && !visited[curr]) {
                    visited[curr] = true;
                    int adding = next[curr] - curr;
                    if (adding != 1) {
                        len += adding;
                        curr = next[curr];
                    } else {
                        break;
                    }
                }
                ans = max(ans, len);
            }
        }
        return ans;
    }
};
