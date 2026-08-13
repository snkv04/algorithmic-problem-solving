#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        s.insert(s.begin(), ' ');
        s.push_back(' ');
        int k = queryIndices.size();
        for (int i = 0; i < k; ++i) {
            queryIndices[i] += 1;
        }

        map<int, int> segments;
        multiset<int> lengths;
        int last = -1;
        for (int i = 0; i < s.size(); ++i) {
            if (i == s.size() - 1 || s[i] != s[i + 1]) {
                segments[i] = last + 1;
                lengths.insert(i - last);
                last = i;
            }
        }

        vector<int> result(k);
        auto update = [&](int idx, char ch) {
            if (ch == s[idx]) return;

            auto p = segments.lower_bound(idx);
            int r = p->first, l = p->second;
            if (r > idx && l < idx) {
                segments.erase(r);
                lengths.erase(lengths.find(r - l + 1));

                segments[idx - 1] = l;
                lengths.insert(idx - l);

                segments[r] = idx + 1;
                lengths.insert(r - idx);

                s[idx] = ch;
                segments[idx] = idx;
                lengths.insert(1);
            } else if (r > idx) {
                segments.erase(r);
                lengths.erase(lengths.find(r - l + 1));

                segments[r] = idx + 1;
                lengths.insert(r - l);

                s[idx] = ch;
                if (s[idx] == s[idx - 1]) {
                    l = segments[idx - 1];
                    segments.erase(idx - 1);
                    lengths.erase(lengths.find(idx - l));
                }
                segments[idx] = l;
                lengths.insert(idx - l + 1);
            } else if (l < idx) {
                segments.erase(idx);
                lengths.erase(lengths.find(idx - l + 1));

                segments[idx - 1] = l;
                lengths.insert(idx - l);

                s[idx] = ch;
                if (s[idx] == s[idx + 1]) {
                    r = segments.lower_bound(idx + 1)->first;
                    segments.erase(r);
                    lengths.erase(lengths.find(r - idx));
                }
                segments[r] = idx;
                lengths.insert(r - idx + 1);
            } else {
                segments.erase(idx);
                lengths.erase(lengths.find(1));

                s[idx] = ch;
                if (s[idx] == s[idx + 1]) {
                    r = segments.lower_bound(idx + 1)->first;
                    segments.erase(r);
                    lengths.erase(lengths.find(r - idx));
                }
                if (s[idx] == s[idx - 1]) {
                    l = segments[idx - 1];
                    segments.erase(idx - 1);
                    lengths.erase(lengths.find(idx - l));
                }
                segments[r] = l;
                lengths.insert(r - l + 1);
            }
        };
        for (int i = 0; i < k; ++i) {
            update(queryIndices[i], queryCharacters[i]);
            result[i] = *lengths.rbegin();
        }
        return result;
    }
};
