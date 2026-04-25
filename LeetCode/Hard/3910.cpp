class Solution {
    int count(int mask, vector<int> &nums) {
        int cnt = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if ((1 << i) & mask) cnt += nums[i];
        }
        return cnt;
    }

    bool is_connected(vector<vector<int>> &adj, int mask) {
        int n = adj.size();
        int start = -1;
        for (int i = 0; i < n; ++i) {
            if ((1 << i) & mask) {
                start = i;
                break;
            }
        }

        queue<int> q;
        vector<bool> visited(n, false);
        q.push(start);
        while (q.size()) {
            int node = q.front();
            q.pop();
            if (visited[node]) continue;

            visited[node] = true;
            for (int next : adj[node]) {
                if (!visited[next]) {
                    q.push(next);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (((1 << i) & mask) && !visited[i]) return false;
        }
        return true;
    }

public:
    int evenSumSubgraphs(vector<int>& nums, vector<vector<int>>& edges) {
        int ans = 0;
        int n = nums.size(), m = edges.size();
        for (int mask = 1; mask < (1 << n); ++mask) {
            if (count(mask, nums) % 2) continue;

            vector<vector<int>> adj(n);
            for (int i = 0; i < m; ++i) {
                int a = edges[i][0], b = edges[i][1];
                if (
                    ((1 << a) & mask) &&
                    ((1 << b) & mask)
                ) {
                    adj[a].push_back(b);
                    adj[b].push_back(a);
                }
            }
            if (!is_connected(adj, mask)) continue;

            ++ans;
        }
        return ans;
    }
};
