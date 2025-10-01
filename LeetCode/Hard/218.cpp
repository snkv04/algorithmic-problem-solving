class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        map<int, int> curr_height_freqs;
        map<int, unordered_map<int, pair<int, int>>> starts_stops;
        for (const vector<int> &b : buildings) {
            int left = b[0], right = b[1], height = b[2];
            starts_stops[left][height].first += 1;
            starts_stops[right][height].second += 1;
        }
        
        vector<vector<int>> ans;
        for (
            const pair<int, unordered_map<int, pair<int, int>>> entry :
            starts_stops
        ) {
            int x = entry.first;
            for (const pair<int, pair<int, int>> entry2 : entry.second) {
                int height = entry2.first;
                int increase = entry2.second.first;
                int decrease = entry2.second.second;
                curr_height_freqs[height] += increase;
                curr_height_freqs[height] -= decrease;
                if (curr_height_freqs[height] == 0) {
                    curr_height_freqs.erase(height);
                }
            }

            int max_height = curr_height_freqs.empty()
                ? 0
                : curr_height_freqs.rbegin()->first;
            if (ans.empty() || ans.back()[1] != max_height) {
                ans.push_back(vector<int>({x, max_height}));
            }
        }
        return ans;
    }
};
