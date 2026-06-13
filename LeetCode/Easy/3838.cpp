#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        stringstream ss;
        for (string word : words) {
            int weight = 0;
            for (int i = 0; i < word.size(); ++i) {
                weight += weights[word[i] - 'a'];
            }
            ss << (char) ('z' - (weight % 26));
        }
        return ss.str();
    }
};
