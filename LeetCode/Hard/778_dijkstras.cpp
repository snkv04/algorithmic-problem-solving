class Solution {
    struct Comp {
        bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
            return a.second > b.second;
        }
    };

    int toidx(int i, int j, int c) {
        return i * c + j;
    }

public:
    int swimInWater(vector<vector<int>>& grid) {
        vector<vector<int>> delta = {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0}
        };

        int rows = grid.size(), cols = grid[0].size();
        vector<int> dist(rows * cols, 1e9);
        priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> pq;
        dist[0] = grid[0][0];
        pq.push(make_pair(0, grid[0][0]));
        while (pq.size()) {
            pair<int, int> p = pq.top();
            pq.pop();
            int i = p.first / cols, j = p.first % cols, maxonpath = p.second;

            for (int k = 0; k < 4; ++k) {
                int newi = i + delta[k][0], newj = j + delta[k][1];
                if (newi >= 0 && newi < rows && newj >= 0 && newj < cols) {
                    int newdist = max(maxonpath, grid[newi][newj]);
                    int newidx = newi * cols + newj;
                    if (newdist < dist[newidx]) {
                        dist[newidx] = newdist;
                        pq.push(make_pair(newidx, newdist));
                    }
                }
            }
        }
        return dist[(rows - 1) * cols + cols - 1];
    }
};
