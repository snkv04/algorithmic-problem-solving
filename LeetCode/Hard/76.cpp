class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> t_as_map;
        for (char c : t) t_as_map[c] += 1;

        int i = 0, j = 0, ansi = -1e9, ansj = 1e9;
        unordered_map<char, int> window_as_map;
        unordered_set<char> window_fine;
        int n = s.size();
        while (j < n) {
            while (j < n && window_fine.size() != t_as_map.size()) {
                char c = s[j++];
                window_as_map[c] += 1;
                if (
                    t_as_map.find(c) != t_as_map.end() && 
                    window_as_map[c] >= t_as_map[c]
                ) {
                    window_fine.insert(c);
                }
            }
            if (window_fine.size() != t_as_map.size()) break;

            while (i < j) {
                char c = s[i++];
                window_as_map[c] -= 1;
                if (
                    t_as_map.find(c) != t_as_map.end() &&
                    window_as_map[c] < t_as_map[c]
                ) {
                    if (j - i + 1 < ansj - ansi) {
                        ansj = j;
                        ansi = i - 1;
                    }
                    window_fine.erase(c);
                    break;
                }
            }
        }

        if (ansi == -1e9) {
            return "";
        } else {
            return s.substr(ansi, ansj - ansi);
        }
    }
};
