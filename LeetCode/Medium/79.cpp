class Solution {
private:
    vector<vector<char>> board;

    bool dfs(int i, int j, string word, int idx) {
        if (idx == word.size()) {
            return true;
        }
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) {
            return false;
        }
        if (board[i][j] != word[idx]) {
            return false;
        }

        // Visit the current cell
        char current_cell = board[i][j];
        board[i][j] = '\0';

        // Check adjacent cells
        vector<pair<int, int>> delta = {
            make_pair(0, 1),
            make_pair(0, -1),
            make_pair(1, 0),
            make_pair(-1, 0)
        };
        bool found = false;
        for (pair<int, int> &p : delta) {
            int new_i = i + p.first;
            int new_j = j + p.second;
            if (dfs(new_i, new_j, word, idx+1)) {
                found = true;
                break;
            }
        }

        // Unvisit the current cell
        board[i][j] = current_cell;
        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        /*
        - brute-force through all starting cells
        - for each starting cell:
            - look through all 4 directions, keeping track of the current letter of the word
            - if the cell matches the current letter, then keep going
            - else, don't visit that cell
        - how to avoid revisiting cells? keep a visited matrix, meaning that each cell gets mapped to a bool
        - when visiting cells, mark it as true, and when backtracking, then unmark it as true
        */

        int m = board.size(), n = board[0].size();
        this->board = board;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(i, j, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};
