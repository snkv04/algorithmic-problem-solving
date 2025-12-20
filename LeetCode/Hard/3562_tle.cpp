class Solution {
    vector<vector<int>> children;
    vector<vector<vector<int>>> mem;
    vector<vector<vector<bool>>> possible;
    vector<bool> visited;
    int budget;

    void dfs(
        int node, const vector<int> &present, const vector<int> &future
    ) {
        visited[node] = true;
        for (int next : children[node]) {
            if (!visited[next]) {
                dfs(next, present, future);
            }
        }

        // consider not buying it
        possible[node][0][0] = true;
        mem[node][0][0] = 0;
        for (int next : children[node]) {
            for (int cost = budget; cost >= 0; --cost) {
                for (int prevcost = 0; prevcost <= cost; ++prevcost) {
                    // consider not buying child
                    if (
                        possible[node][0][cost-prevcost] &&
                        possible[next][0][prevcost]
                    ) {
                        possible[node][0][cost] = true;
                        mem[node][0][cost] = max(
                            mem[node][0][cost],
                            mem[node][0][cost-prevcost] + mem[next][0][prevcost]
                        );
                    }

                    // consider buying child
                    if (
                        possible[node][0][cost-prevcost] &&
                        possible[next][1][prevcost]
                    ) {
                        possible[node][0][cost] = true;
                        mem[node][0][cost] = max(
                            mem[node][0][cost],
                            mem[node][0][cost-prevcost] + mem[next][1][prevcost]
                        );
                    }
                }
            }
        }

        // consider buying it
        if (present[node] <= budget) {
            possible[node][1][present[node]] = true;
            mem[node][1][present[node]] = future[node] - present[node];
            for (int next : children[node]) {
                vector<int> ifchild = mem[node][1], ifnotchild = mem[node][1];
                vector<bool> possibleifchild = possible[node][1],
                            possibleifnot = possibleifchild;
                for (int cost = budget; cost >= present[node]; --cost) {
                    for (int prevcost = 0; prevcost <= cost; ++prevcost) {
                        // consider not buying child
                        if (
                            possibleifnot[cost - prevcost] &&
                            possible[next][0][prevcost]
                        ) {
                            possibleifnot[cost] = true;
                            ifnotchild[cost] = max(
                                ifnotchild[cost],
                                ifnotchild[cost-prevcost] + mem[next][0][prevcost]
                            );
                        }

                        // consider buying child
                        int saved = (present[next] + 1) / 2;
                        if (
                            prevcost + saved <= budget &&
                            possibleifchild[cost - prevcost] &&
                            possible[next][1][prevcost+saved]
                        ) {
                            possibleifchild[cost] = true;
                            ifchild[cost] = max(
                                ifchild[cost],
                                ifchild[cost-prevcost] + mem[next][1][prevcost+saved] + saved
                            );
                        }
                    }
                }

                // take max of both choices for each cost
                for (int cost = 0; cost <= budget; ++cost) {
                    mem[node][1][cost] = max({
                        mem[node][1][cost],
                        ifnotchild[cost],
                        ifchild[cost]
                    });
                    possible[node][1][cost] = (
                        possible[node][1][cost] ||
                        possibleifnot[cost] ||
                        possibleifchild[cost]
                    );
                }
            }
        }
    }

public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        // - mem[i][j][k] = maximum profit within the subtree rooted at node i
        // if we spend exactly k, where we do buy node i if j == 1 and don't buy
        // node i if j == 0
        // - possible[i][j][k] = whether or not it's possible to spend exactly k
        // within the subtree rooted at node i, where we do buy node i if j == 1
        // and don't buy node i if j == 0
        this->budget = 2 * budget + 1;
        children.clear();
        children.resize(n);
        for (auto edge : hierarchy) {
            children[edge[0] - 1].push_back(edge[1] - 1);
        }
        mem = vector<vector<vector<int>>>(
            n,
            vector<vector<int>>(
                2,
                vector<int>(
                    this->budget + 1,
                    // 0
                    -1e9
                )
            )
        );
        possible = vector<vector<vector<bool>>>(
            n,
            vector<vector<bool>>(
                2,
                vector<bool>(
                    this->budget + 1,
                    false
                )
            )
        );

        // solve
        int root = -1;
        visited = vector<bool>(n, false);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i, present, future);
                root = i;
            }
        }

        int ans = 0;
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k <= budget; ++k) {
                if (possible[root][j][k])
                    ans = max(ans, mem[root][j][k]);
            }
        }
        return ans;
    }
};
