struct TrieNode {
    char c;
    bool end;
    array<TrieNode*, 26> children;

    TrieNode() : c(' '), end(false), children{nullptr} {}

    TrieNode(char c) : c(c), end(false), children({nullptr}) {}
};

struct Trie {
    TrieNode root;

    void insert(string s) {
        TrieNode *curr = &root;
        for (char c : s) {
            int as_num = (int) (c - 'a');
            if (curr->children[as_num] == nullptr) {
                curr->children[as_num] = new TrieNode(c);
            }
            curr = curr->children[as_num];
        }
        curr->end = true;
    }

    void remove(string s) {
        vector<TrieNode*> node_path;
        node_path.push_back(&root);
        for (char c : s) {
            node_path.push_back(node_path.back()->children[(int) (c-'a')]);
        }
        
        node_path.back()->end = false;
        while (node_path.size() > 1) {
            if (node_path.back()->end) break;

            bool children_exist = false;
            for (int i = 0; i < 26; ++i) {
                if (node_path.back()->children[i] != nullptr) {
                    children_exist = true;
                    break;
                }
            }

            if (!children_exist) {
                char letter = node_path.back()->c;
                node_path.pop_back();
                node_path.back()->children[(int) (letter-'a')] = nullptr;
            }
        }
    }
};

class Solution {
private:
    unordered_set<string> words_found;
    vector<int> di = {0, 0, 1, -1},
                dj = {1, -1, 0, 0};
    Trie trie;

    void recurse(
        int i,
        int j,
        vector<vector<char>> &board,
        TrieNode *curr_node,
        string path,
        vector<vector<bool>> &visited
    ) {
        if (curr_node->end) {
            words_found.insert(path);
            
            // trying to remove the finished words causes a TLE

            // bool can_remove = true;
            // for (int i = 0; i < 26; ++i) {
            //     if (curr_node->children[i] != nullptr) {
            //         can_remove = false;
            //         break;
            //     }
            // }

            // if (can_remove) {
            //     trie.remove(path);
            //     return;
            // } else {
            //     curr_node->end = false;
            // }
        }

        visited[i][j] = true;
        for (int k = 0; k < 4; ++k) {
            int newi = i + di[k], newj = j + dj[k];
            if (
                newi >= 0
                && newi < board.size()
                && newj >= 0
                && newj < board[0].size()
            ) {
                char letter = board[newi][newj];
                int letter_as_num = (int) (letter - 'a');
                if (
                    !visited[newi][newj]
                    && curr_node->children[letter_as_num] != nullptr
                ) {
                    recurse(
                        newi,
                        newj,
                        board,
                        curr_node->children[letter_as_num],
                        path + letter,
                        visited
                    );
                }
            }
        }
        visited[i][j] = false;
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        for (string word : words) {
            trie.insert(word);
        }

        words_found = unordered_set<string>();
        int rows = board.size(), cols = board[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                char letter = board[i][j];
                int letter_as_num = (int) (letter - 'a');
                if (trie.root.children[letter_as_num] != nullptr) {
                    recurse(
                        i,
                        j,
                        board,
                        trie.root.children[letter_as_num],
                        string() + letter,
                        visited
                    );
                }
            }
        }

        vector<string> result;
        for (string word : words_found) result.push_back(word);
        return result;
    }
};
