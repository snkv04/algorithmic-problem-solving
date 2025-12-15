struct Hash {
    size_t operator()(const vector<vector<int>> &arr) const {
        size_t hash = 0;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                hash = 6 * hash + arr[i][j];
            }
        }
        return hash;
    }
};

class Solution {
    vector<int> dr = {0, 0, 1, -1}, dc = {1, -1, 0, 0};

public:
    int slidingPuzzle(vector<vector<int>>& board) {
        unordered_map<vector<vector<int>>, int, Hash> dist;
        dist[board] = 0;
        queue<pair<vector<vector<int>>, int>> q;
        q.push(make_pair(board, 0));
        while (q.size()) {
            auto node = q.front();
            q.pop();
            vector<vector<int>> curr_board = node.first;
            int distance = node.second;
            if (distance > dist[curr_board]) continue;

            int r = -1, c = -1;
            for (int i = 0; i < 2 && r == -1; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (curr_board[i][j] == 0) {
                        r = i;
                        c = j;
                        break;
                    }
                }
            }

            for (int k = 0; k < 4; ++k) {
                int newr = r + dr[k], newc = c + dc[k];
                if (newr >= 0 && newr <= 1 && newc >= 0 && newc <= 2) {
                    swap(curr_board[r][c], curr_board[newr][newc]);
                    if (dist.find(curr_board) == dist.end() || dist[curr_board] > distance + 1) {
                        dist[curr_board] = distance + 1;
                        q.push(make_pair(curr_board, distance + 1));
                    }
                    swap(curr_board[r][c], curr_board[newr][newc]);
                }
            }
        }

        vector<vector<int>> end_state = {{1, 2, 3}, {4, 5, 0}};
        if (dist.find(end_state) == dist.end()) {
            return -1;
        } else {
            return dist[end_state];
        }
    }
};
