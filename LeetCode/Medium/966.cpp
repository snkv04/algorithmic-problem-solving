class Solution {
private:
    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

    char to_lowercase(char c) {
        int as_int = c;
        if (as_int >= 65 && as_int <= 90) {
            return static_cast<char>('a' + as_int - 65);
        } else {
            return c;
        }
    }

    string to_lowercase(string &s) {
        string result(s.size(), ' ');
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            result[i] = to_lowercase(c);
        }
        return result;
    }

    string to_no_vowels(string &s) {
        string result(s.size(), ' ');
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (vowels.find(c) == vowels.end()) {
                result[i] = c;
            } else {
                result[i] = '*';
            }
        }
        return result;
    }

public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        unordered_set<string> all_words;
        unordered_map<string, string> no_caps, vowel_blind;
        for (string &word : wordlist) {
            all_words.insert(word);

            string as_lowercase = to_lowercase(word);
            if (no_caps.find(as_lowercase) == no_caps.end()) {
                no_caps[as_lowercase] = word;
            }
            
            string no_vowels = to_no_vowels(as_lowercase);
            if (vowel_blind.find(no_vowels) == vowel_blind.end()) {
                vowel_blind[no_vowels] = word;
            }
        }

        vector<string> answer;
        for (string &q : queries) {
            if (all_words.find(q) != all_words.end()) {
                answer.push_back(q);
                continue;
            }

            string as_lowercase = to_lowercase(q);
            if (no_caps.find(as_lowercase) != no_caps.end()) {
                answer.push_back(no_caps[as_lowercase]);
                continue;
            }
            
            string no_vowels = to_no_vowels(as_lowercase);
            if (vowel_blind.find(no_vowels) != vowel_blind.end()) {
                answer.push_back(vowel_blind[no_vowels]);
                continue;
            }
            
            answer.push_back("");
        }
        return answer;
    }
};
