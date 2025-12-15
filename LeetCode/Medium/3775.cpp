class Solution {
    set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

    int count_vowels(const string &word) {
        int count = 0;
        for (int i = 0; i < word.size(); ++i) {
            if (vowels.find(word[i]) != vowels.end()) {
                ++count;
            }
        }
        return count;
    }

public:
    string reverseWords(string s) {
        stringstream stream(s);
        vector<string> words;
        string word;
        while (stream >> word) {
            words.push_back(word);
        }

        int count = count_vowels(words[0]);

        stringstream result;
        result << words[0];
        for (int i = 1; i < words.size(); ++i) {
            result << ' ';
            if (count_vowels(words[i]) != count) {
                result << words[i];
            } else {
                reverse(words[i].begin(), words[i].end());
                result << words[i];
            }
        }
        return result.str();
    }
};
