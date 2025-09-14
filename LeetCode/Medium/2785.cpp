class Solution {
public:
    string sortVowels(string s) {
        int n = s.size();
        auto cmp = [](const char &a, const char &b) {
            return a > b;
        };
        priority_queue<char, vector<char>, decltype(cmp)> pq(cmp);
        unordered_set<char> vowels = {
            'a', 'e', 'i', 'o', 'u',
            'A', 'E', 'I', 'O', 'U'
        };

        for (int i = 0; i < n; ++i) {
            if (vowels.find(s[i]) != vowels.end()) {
                pq.push(s[i]);
                s[i] = ' ';
            }
        }

        for (int i = 0; i < n; ++i) {
            if (s[i] == ' ') {
                char popping = pq.top();
                pq.pop();
                s[i] = popping;
            }
        }
        return s;
    }
};
