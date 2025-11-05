#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

struct Guess {
    string guess, result;
};

int main() {
    int n, w;
    cin >> n >> w;
    vector<Guess> guesses(n);
    for (int i = 0; i < n; ++i) {
        cin >> guesses[i].guess >> guesses[i].result;
    }
    vector<string> ordered_words(w);
    unordered_set<string> words;
    for (int i = 0; i < w; ++i) {
        cin >> ordered_words[i];
        words.insert(ordered_words[i]);
    }

    for (Guess g : guesses) {
        unordered_set<string> new_words;
        for (string word : words) {
            string result(5, '-');
            map<char, set<int>> guess_freqs, ans_freqs;
            for (int i = 0; i < 5; ++i) {
                if (g.guess[i] == word[i]) {
                    result[i] = 'G';
                } else {
                    guess_freqs[g.guess[i]].insert(i);
                    ans_freqs[word[i]].insert(i);
                }
            }
            for (const pair<char, set<int>> &entry : guess_freqs) {
                if (ans_freqs.find(entry.first) == ans_freqs.end()) {
                    // for (int i : entry.second) {
                    //     result[i] = '-';
                    // }
                } else {
                    int numY = min(entry.second.size(), ans_freqs[entry.first].size());
                    for (int i : entry.second) {
                        result[i] = 'Y';
                        --numY;
                        if (!numY) break;
                    }
                }
            }

            if (result == g.result) {
                new_words.insert(word);
            }
        }
        words = std::move(new_words);
    }

    for (int i = 0; i < w; ++i) {
        if (words.find(ordered_words[i]) != words.end()) {
            cout << ordered_words[i] << "\n";
        }
    }
}