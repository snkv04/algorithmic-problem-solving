#include <bits/stdc++.h>

struct TrieNode {
    std::array<TrieNode*, 26> children;
    int end;

    TrieNode() : children{}, end(0) {}
};

struct PrefixTree {
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

    int search(const std::string &str) {
        TrieNode *curr = &root;
        for (int i = 0; i < str.size(); ++i) {
            int letter_as_int = str[i] - 'a';
            if (curr->children[letter_as_int] == nullptr) {
                return 0;
            }
            curr = curr->children[letter_as_int];
        }
        return curr->end;
    }

    bool check_prefix(const std::string &str) {
        TrieNode *curr = &root;
        for (int i = 0; i < str.size(); ++i) {
            int letter_as_int = str[i] - 'a';
            if (curr->children[letter_as_int] == nullptr) {
                return false;
            }
            curr = curr->children[letter_as_int];
        }
        return true;
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

    void _print_trie(int num_tabs, char curr_letter, TrieNode *curr_node, std::stringstream &stream) {
        for (int i = 0; i < num_tabs; ++i) {
            stream << ' ';
        }
        stream << "('" << curr_letter << "', " << curr_node->end << ")\n";
        for (int i = 0; i < 26; ++i) {
            if (curr_node->children[i] != nullptr) {
                _print_trie(num_tabs + 2, static_cast<char>('a' + i), curr_node->children[i], stream);
            }
        }
    }

    std::string print_trie() {
        std::stringstream stream;
        _print_trie(0, '.', &root, stream);
        return stream.str();
    }

private:
    TrieNode root;
};
