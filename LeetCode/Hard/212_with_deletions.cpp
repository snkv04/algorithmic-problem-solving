struct TrieNode {
    std::array<TrieNode*, 26> children;
    int end;

    TrieNode() : children{}, end(0) {}
};

struct PrefixTree {
    TrieNode root;

    PrefixTree() : root() {}

    void insert(const std::string &str) {
        TrieNode *curr = &root;
        for (int i = 0; i < str.size(); ++i) {
            int letter_as_int = str[i] - 'a';
            if (curr->children[letter_as_int] == nullptr) {
                curr->children[letter_as_int] = new TrieNode();
            }
            curr = curr->children[letter_as_int];
        }
        curr->end += 1;
    }

    bool _remove(int index, TrieNode *curr, const std::string &str) {
        if (index == str.size() - 1) {  // reached the last letter
            // if the last letter isn't marked with end > 0, then the
            // word doesn't exist in the trie
            if (curr->end == 0) {
                throw std::logic_error("Word doesn't exist in trie");
            }

            // unmarks the node as the end of a word
            curr->end -= 1;

            // if there are other copies of the same word in the trie,
            // then return false (meaning we shouldn't delete any nodes
            // higher on the path from the root)
            if (curr->end) {
                return false;
            }

            // since this word is now no longer part of the trie, we check
            // if any other words use this word as a prefix; if so, then we
            // delete nothing higher on the path from the path, but if not,
            // then we indicate that we can set this node as null from the
            // perspective of the parent node
            // note: this means that the root is never set to nullptr, even
            // if there was an empty string previously inserted (which corresponds
            // to the root) and it was now deleted
            for (int i = 0; i < 26; ++i) {
                if (curr->children[i] != nullptr) {
                    return false;
                }
            }
            return true;
        }

        // not on last letter
        int next_letter = str[index + 1] - 'a';

        if (curr->children[next_letter] == nullptr) {
            // if the next letter is not in the trie, then the word isn't in the trie
            throw std::logic_error("Word doesn't exist in trie");
        } else {
            // if we don't want to delete the next letter from the trie, we don't
            // want to delete anything higher on the path from the root to the
            // current node, and so this cascades up
            if (!_remove(index + 1, curr->children[next_letter], str)) {
                return false;
            }

            // delete the next letter from the trie
            curr->children[next_letter] = nullptr;

            // now, we just check if the current node is needed for any other words
            // (i.e., if it's a prefix of any); if it is, then we don't want to delete
            // anything further, and if it isn't, then we tell the node above to delete
            // this current node
            for (int i = 0; i < 26; ++i) {
                if (curr->children[i] != nullptr) {
                    return false;
                }
            }
            return true;
        }
    }

    void remove(const std::string &str) {
        _remove(-1, &root, str);
    }
};

class Solution {
private:
    unordered_set<string> words_found;
    vector<int> di = {0, 0, 1, -1},
                dj = {1, -1, 0, 0};
    PrefixTree trie;

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

            bool can_remove = true;
            for (int i = 0; i < 26; ++i) {
                if (curr_node->children[i] != nullptr) {
                    can_remove = false;
                    break;
                }
            }

            if (can_remove) {
                trie.remove(path);
                return;
            } else {
                curr_node->end = false;
            }
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
